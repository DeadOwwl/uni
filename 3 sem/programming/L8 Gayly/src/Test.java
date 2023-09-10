import java.io.*;
import java.util.*;

public class Test {
    public static void main(String[] args) {
        try {
            if ( args.length >= 1 ) {
                switch (args[0]) {
                    case "-?":
                    case "-h":
                        System.out.println(
                                "Syntax:\n" +
                                        "\t-a  [file [encoding]] - append data\n" +
                                        "\t-az [file [encoding]] - append data, compress every record\n" +
                                        "\t-d                    - clear all data\n" +
                                        "\t-dk  {hn|fn|name|date} key      - clear data by key\n" +
                                        "\t-p                    - print data unsorted\n" +
                                        "\t-ps  {hn|fn|name|date}          - print data sorted by house_number/flat_number/name/date\n" +
                                        "\t-psr {hn|fn|name|date}          - print data reverse sorted by house_number/flat_number/name/date\n" +
                                        "\t-f   {hn|fn|name|date} key      - find record by key\n" +
                                        "\t-fr  {hn|fn|name|date} key      - find records > key\n" +
                                        "\t-fl  {hn|fn|name|date} key      - find records < key\n" +
                                        "\t-?, -h                - command line syntax\n"
                        );
                        break;
                    case "-a":
                        // Append file with new object from System.in
                        // -a [file [encoding]]
                        appendFile(args, false);
                        break;
                    case "-az":
                        // Append file with compressed new object from System.in
                        // -az [file [encoding]]
                        appendFile(args, true);
                        break;
                    case "-p":
                        // Prints data file
                        printFile();
                        break;
                    case "-ps":
                        // Prints data file sorted by key
                        if (!printFile(args, false)) {
                            System.exit(1);
                        }
                        break;
                    case "-psr":
                        // Prints data file reverse-sorted by key
                        if (!printFile(args, true)) {
                            System.exit(1);
                        }
                        break;
                    case "-d":
                        // delete files
                        if (args.length != 1) {
                            System.err.println("Invalid number of arguments");
                            System.exit(1);
                            ;
                        }
                        deleteFile();
                        break;
                    case "-dk":
                        // Delete records by key
                        if (!deleteFile(args)) {
                            System.exit(1);
                        }
                        break;
                    case "-f":
                        // Find record(s) by key
                        if (!findByKey(args)) {
                            System.exit(1);
                        }
                        break;
                    case "-fr":
                        // Find record(s) by key large then key
                        if (!findByKey(args, new KeyCompReverse())) {
                            System.exit(1);
                        }
                        break;
                    case "-fl":
                        // Find record(s) by key less then key
                        if (!findByKey(args, new KeyComp())) {
                            System.exit(1);
                        }
                        break;
                    default:
                        System.err.println("Option is not realised: " + args[0]);
                        System.exit(1);
                }
            }
            else {
                System.err.println( "Bills: Nothing to do! Enter -? for options" );
            }
        }
        catch ( Exception e ) {
            System.err.println( "Run/time error: " + e );
            System.exit(1);
        }
        System.err.println( "Bills finished..." );
        System.exit(0);
    }

    static final String filename    = "Bills.dat";
    static final String filenameBak = "Bills.~dat";
    static final String idxname     = "Bills.idx";
    static final String idxnameBak  = "Bills.~idx";

    // input file encoding:
    private static String encoding = "Cp866";
    private static PrintStream billOut = System.out;

    static Bill readBill(Scanner fin ) throws IOException {
        return Bill.nextRead( fin, billOut )
                ? Bill.read( fin, billOut ) : null;
    }

    private static void deleteBackup() {
        new File( filenameBak ).delete();
        new File( idxnameBak ).delete();
    }

    static void deleteFile() {
        deleteBackup();
        new File( filename ).delete();
        new File( idxname ).delete();
    }

    private static void backup() {
        deleteBackup();
        new File( filename ).renameTo( new File( filenameBak ));
        new File( idxname ).renameTo( new File( idxnameBak ));
    }

    static boolean deleteFile( String[] args )
            throws ClassNotFoundException, IOException, KeyNotUniqueException {
        //-dk  {i|a|n} key      - clear data by key
        if ( args.length != 3 ) {
            System.err.println( "Invalid number of arguments" );
            return false;
        }
        long[] poss = null;
        try ( Index idx = Index.load( idxname )) {
            IndexBase pidx = indexByArg( args[1], idx );
            if ( pidx == null ) {
                return false;
            }
            if (!pidx.contains(args[2])) {
                System.err.println( "Key not found: " + args[2] );
                return false;
            }
            poss = pidx.get(args[2]);
        }
        backup();
        Arrays.sort( poss );
        try ( Index idx = Index.load( idxname );
              RandomAccessFile fileBak= new RandomAccessFile(filenameBak, "rw");
              RandomAccessFile file = new RandomAccessFile( filename, "rw")) {
            boolean[] wasZipped = new boolean[] {false};
            long pos;
            while (( pos = fileBak.getFilePointer()) < fileBak.length() ) {
                Bill bill = (Bill)
                        Buffer.readObject( fileBak, pos, wasZipped );
                if ( Arrays.binarySearch(poss, pos) < 0 ) { // if not found in deleted
                    long ptr = Buffer.writeObject( file, bill, wasZipped[0] );
                    idx.put( bill, ptr );
                }
            }
        }
        return true;
    }

    static void appendFile( String[] args, Boolean zipped )
            throws FileNotFoundException, IOException, ClassNotFoundException,
            KeyNotUniqueException {
        if ( args.length >= 2 ) {
            FileInputStream stdin = new FileInputStream( args[1] );
            System.setIn( stdin );
            if (args.length == 3) {
                encoding = args[2];
            }
            // hide output:
            billOut = new PrintStream("nul");
        }
        appendFile( zipped );
    }

    static void appendFile( Boolean zipped )
            throws FileNotFoundException, IOException, ClassNotFoundException,
            KeyNotUniqueException {
        Scanner fin = new Scanner( System.in, encoding );
        billOut.println( "Enter bill data. " );
        try ( Index idx = Index.load( idxname );
              RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            for(;;) {
                Bill bill = readBill( fin );
                if ( bill == null )
                    break;
                idx.test( bill );
                long pos = Buffer.writeObject( raf, bill, zipped );
                idx.put( bill, pos );
            }
        }
    }

    private static void printRecord( RandomAccessFile raf, long pos )
            throws ClassNotFoundException, IOException {
        boolean[] wasZipped = new boolean[] {false};
        Bill bill = (Bill) Buffer.readObject( raf, pos, wasZipped );
        if (wasZipped[0]) {
            System.out.print( " compressed" );
        }
        System.out.println( " record at position "+ pos + ": \n" + bill );
    }

    private static void printRecord( RandomAccessFile raf, String key,
                                     IndexBase pidx ) throws ClassNotFoundException, IOException {
        long[] poss = pidx.get( key );
        for ( long pos : poss ) {
            System.out.print( "*** Key: " +  key + " points to" );
            printRecord( raf, pos );
        }
    }

    static void printFile()
            throws FileNotFoundException, IOException, ClassNotFoundException {
        long pos;
        int rec = 0;
        try ( RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            while (( pos = raf.getFilePointer()) < raf.length() ) {
                System.out.print( "#" + (++rec ));
                printRecord( raf, pos );
            }
            System.out.flush();
        }
    }

    private static IndexBase indexByArg( String arg, Index idx ) {
        IndexBase pidx = null;
        switch (arg) {
            case "date":
                pidx = idx.dates;
                break;
            case "name":
                pidx = idx.names;
                break;
            case "hn":
                pidx = idx.houseNumbers;
                break;
            case "fn":
                pidx = idx.flatNumbers;
                break;
            default:
                System.err.println("Invalid index specified: " + arg);
                break;
        }
        return pidx;
    }

    static boolean printFile( String[] args, boolean reverse )
            throws ClassNotFoundException, IOException {
        if ( args.length != 2 ) {
            System.err.println( "Invalid number of arguments" );
            return false;
        }
        try ( Index idx = Index.load( idxname );
              RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            IndexBase pidx = indexByArg( args[1], idx );
            if ( pidx == null ) {
                return false;
            }
            String[] keys =
                    pidx.getKeys( reverse ? new KeyCompReverse() : new KeyComp() );
            for ( String key : keys ) {
                printRecord( raf, key, pidx );
            }
        }
        return true;
    }

    static boolean findByKey( String[] args )
            throws ClassNotFoundException, IOException {
        if ( args.length != 3 ) {
            System.err.println( "Invalid number of arguments" );
            return false;
        }
        try ( Index idx = Index.load( idxname );
              RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            IndexBase pidx = indexByArg( args[1], idx );
            if (!pidx.contains(args[2])) {
                System.err.println( "Key not found: " + args[2] );
                return false;
            }
            printRecord( raf, args[2], pidx );
        }
        return true;
    }

    static boolean findByKey( String[] args, Comparator<String> comp )
            throws ClassNotFoundException, IOException {
        if ( args.length != 3 ) {
            System.err.println( "Invalid number of arguments" );
            return false;
        }
        try ( Index idx = Index.load( idxname );
              RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            IndexBase pidx = indexByArg( args[1], idx );
            if (!pidx.contains(args[2])) {
                System.err.println( "Key not found: " + args[2] );
                return false;
            }
            String[] keys = pidx.getKeys( comp );
            for (String key : keys) {
                if (key.equals(args[2])) {
                    break;
                }
                printRecord(raf, key, pidx);
            }
        }
        return true;
    }
}