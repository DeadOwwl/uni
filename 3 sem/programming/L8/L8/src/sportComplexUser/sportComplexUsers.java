package sportComplexUser;

import java.io.*;
import java.text.ParseException;
import java.util.*;

public class sportComplexUsers {
    public static void main(String[] args) {
        try {
            if ( args.length >= 1 ) {				
                if ( args[0].equals("-?") || args[0].equals("-h")) {
                    System.out.println( 
                        "Syntax:\n" +
                        "\t-a  [file [encoding]] - append data\n" +
                        "\t-az [file [encoding]] - append data, compress every record\n" +
                        "\t-d                    - clear all data\n" +
                        "\t-dk  {u|t|d} key      - clear data by key\n" +
                        "\t-p                    - print data unsorted\n" +
                        "\t-ps  {u|t|d}          - print data sorted by isbn/author/name\n" +
                        "\t-psr {u|t|d}          - print data reverse sorted by isbn/author/name\n" +
                        "\t-f   {u|t|d} key      - find record by key\n"+
                        "\t-fr  {u|t|d} key      - find records > key\n"+
                        "\t-fl  {u|t|d} key      - find records < key\n"+
                        "\t-?, -h                - command line syntax\n"
                    );
                }
                else if ( args[0].equals( "-a" )) {
                    appendFile( args, false );
                }
                else if ( args[0].equals( "-az" )) {
                    appendFile( args, true );
                }
                else if ( args[0].equals( "-p" )) {
                    printFile();
                }
                else if ( args[0].equals( "-ps" )) {
                    if ( printFile( args, false )== false ) {
                        System.exit(1);
                    }
                }
                else if ( args[0].equals( "-psr" )) {
                    if ( printFile( args, true )== false ) {
                        System.exit(1);
                    }
                }
                else if ( args[0].equals( "-d" )) {
                    if ( args.length != 1 ) {
                        System.err.println("Invalid number of arguments");
                        System.exit(1);;
                    }
                    deleteFile();
                }
                else if ( args[0].equals( "-dk" )) {
                    if ( deleteFile( args )== false ) {
                        System.exit(1);						
                    }
                }
                else if ( args[0].equals( "-f" )) {
                    if ( findByKey( args )== false ) {
                        System.exit(1);
                    }
                }
                else if ( args[0].equals( "-fr" )) {
                    if ( findByKey( args, new KeyCompReverse() )== false ) {
                        System.exit(1);
                    }
                }
                else if ( args[0].equals( "-fl" )) {
                    if ( findByKey( args, new KeyComp() )== false ) {
                        System.exit(1);
                    }
                }
                else {
                    System.err.println( "Option is not realised: " + args[0] );
                    System.exit(1);
                }
            }
            else {
                System.err.println( "SportComplexUser: Nothing to do! Enter -? for options" );
            }
        }
        catch ( Exception e ) {
            System.err.println( "Run/time error: " + e );
            System.exit(1);
        }
        System.err.println( "SportComplexUser finished..." );	
        System.exit(0);
    }

    static final String filename    = "SCU.dat";
    static final String filenameBak = "SCU.~dat";
    static final String idxname     = "SCU.idx";
    static final String idxnameBak  = "SCU.~idx";
	
    private static String encoding = "Cp866";
    private static PrintStream scuOut = System.out;
	
    static sportComplexUserClass readSCU( Scanner fin ) throws IOException, ParseException {	
        return sportComplexUserClass.read( fin, scuOut );
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
        new File(filename).renameTo( new File( filenameBak ));
        new File(idxname).renameTo( new File( idxnameBak ));
    }

	static boolean deleteFile( String[] args ) 
            throws ClassNotFoundException, IOException, KeyNotUniqueException {
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
            if ( pidx.contains(args[2])== false ) {
                System.err.println( "Key not found: " + args[2] );
                return false;				
            }
            Vector<Long> v = pidx.get(args[2]);
            long[] m = new long[v.size()];
            for (int i = 0; i < v.size(); i++){
            	m[i] = v.get(i);
            }
            poss = m;
            //poss = pidx.get(args[2]);
        }
        backup();
        Arrays.sort(poss);
        try (Index idx = Index.load(idxname); 
              RandomAccessFile fileBak= new RandomAccessFile(filenameBak, "rw");
              RandomAccessFile file = new RandomAccessFile( filename, "rw")) {
            boolean[] wasZipped = new boolean[] {false};
            long pos;
            while (( pos = fileBak.getFilePointer()) < fileBak.length() ) {
            	sportComplexUserClass scu = (sportComplexUserClass) 
                Buffer.readObject( fileBak, pos, wasZipped );
                if ( Arrays.binarySearch(poss, pos) < 0 ) { // if not found in deleted
                    long ptr = Buffer.writeObject( file, scu, wasZipped[0] );
                    idx.put( scu, ptr );
                }
             }
         }
         return true;
    }
	
    static void appendFile( String[] args, Boolean zipped ) throws FileNotFoundException, IOException, 
    ClassNotFoundException,KeyNotUniqueException, ParseException {
        if ( args.length >= 2 ) {
            FileInputStream stdin = new FileInputStream( args[1] );
            System.setIn(stdin);
            if (args.length == 3) {
                encoding = args[2];
            }
            // hide output:
            scuOut = new PrintStream("nul");
        }
        appendFile(zipped);
    }
	
    static void appendFile(Boolean zipped)throws FileNotFoundException, IOException, ClassNotFoundException, 
    KeyNotUniqueException, ParseException {
        Scanner fin = new Scanner( System.in, encoding );
        scuOut.println( "Enter book data: " );
        try ( Index idx = Index.load( idxname ); 
              RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            for(;;) {
            	sportComplexUserClass scu = readSCU( fin );
                if ( scu == null )
                    break;
                idx.test(scu);
                long pos = Buffer.writeObject( raf, scu, zipped );
                idx.put(scu, pos);
            }
        }
    }
	
    private static void printRecord( RandomAccessFile raf, long pos )throws ClassNotFoundException, IOException {
        boolean[] wasZipped = new boolean[] {false};
        sportComplexUserClass scu = (sportComplexUserClass) Buffer.readObject( raf, pos, wasZipped );
        if ( wasZipped[0] == true ) {
            System.out.print( " compressed" );
        }
        System.out.println( " record at position "+ pos + ": \n" + scu );	
    }
	
	private static void printRecord( RandomAccessFile raf, String key,IndexBase pidx ) 
			throws ClassNotFoundException, IOException {
        Vector<Long> v = pidx.get(key);
        long[] poss = new long[v.size()];
        for (int i = 0; i < v.size(); i++){
        	poss[i] = v.get(i);
        }
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
        if ( arg.equals("u")) {
            pidx = idx.userName;
        } 
        else if ( arg.equals("t")) {
            pidx = idx.trainerName;
        } 
        else if ( arg.equals("d")) {
            pidx = idx.date;
        } 
        else {
            System.err.println( "Invalid index specified: " + arg );
        }
        return pidx;
    }
	
    static boolean printFile( String[] args, boolean reverse )throws ClassNotFoundException, IOException {
        if ( args.length != 2 ) {
            System.err.println( "Invalid number of arguments" );
            return false;
        }
        try (Index idx = Index.load( idxname ); 
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
	
    static boolean findByKey( String[] args ) throws ClassNotFoundException, IOException {
        if ( args.length != 3 ) {
            System.err.println( "Invalid number of arguments" );
            return false;
        }
        try ( Index idx = Index.load( idxname ); 
              RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            IndexBase pidx = indexByArg( args[1], idx );
            if ( pidx.contains(args[2])== false ) {
                System.err.println( "Key not found: " + args[2] );
                return false;				
            }
            printRecord( raf, args[2], pidx );
        }
        return true;	
    }
	
    static boolean findByKey( String[] args, Comparator<String> comp )throws ClassNotFoundException, IOException {
        if ( args.length != 3 ) {
            System.err.println( "Invalid number of arguments" );
            return false;
        }
        try ( Index idx = Index.load( idxname ); 
              RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            IndexBase pidx = indexByArg( args[1], idx );
            if ( pidx.contains(args[2])== false ) {
                System.err.println( "Key not found: " + args[2] );
                return false;				
            }
            String[] keys = pidx.getKeys(comp);
            for ( int i = 0; i < keys.length; i++ ) {
                String key = keys[i];
                if ( key.equals( args[2] )) {
                    break;
                }
                printRecord( raf, key, pidx );
            }
        }
        return true;
    }
}
