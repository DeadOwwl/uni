package Model;

import java.io.*;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.zip.*;

class KeyComp implements Comparator<String>{
    public int compare(String o1, String o2) {
        SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy,HH:mm");
        try {
            Date d1= sdf.parse(o1);
            Date d2 = sdf.parse(o2);
            return d1.compareTo(d2);
        }
        catch(Exception ignored){
        }
        return o1.compareTo(o2);
    }

}

class KeyCompReverse implements Comparator<String> {
    public int compare(String o1, String o2) {
        SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy,HH:mm");
        try{
            Date d1= sdf.parse(o1);
            Date d2 = sdf.parse(o2);
            return d2.compareTo(d1);
        }
        catch(Exception ignored){
        }
        return o2.compareTo(o1);
    }
}

interface IndexBase {
    String[] getKeys( Comparator<String> comp );
    void put( String key, long value );
    boolean contains( String key );
    Vector<Long> get(String key);
}

class IndexOne2One implements Serializable, IndexBase {
    // Unique keys
    private static final long serialVersionUID = 1L;
    private final TreeMap<String,Long> map;

    public IndexOne2One() {
        map = new TreeMap<>();
    }

    public String[] getKeys( Comparator<String> comp ) {
        String[] result = map.keySet().toArray( new String[0] );
        Arrays.sort( result, comp );
        return result;
    }

    public void put( String key, long value ) {
        map.put(key, value);
    }

    public boolean contains( String key ) {
        return map.containsKey(key);
    }

    public Vector<Long> get(String key) {
        Long pos = map.get(key);
        Vector <Long> vector = new Vector <Long>();
        vector.add(pos);
        return vector;
    }
}

class IndexOne2N implements Serializable, IndexBase {
    // Not unique keys
    private static final long serialVersionUID = 1L;
    private final TreeMap<String,long[]> map;

    public IndexOne2N() {
        map = new TreeMap<>();
    }

    public String[] getKeys( Comparator<String> comp ) {
        String[] result = map.keySet().toArray( new String[0] );
        Arrays.sort( result, comp );
        return result;
    }

    public void put( String key, long value ) {
        long[] arr = map.get(key);
        arr = ( arr != null ) ? Index.InsertValue( arr, value ) : new long[] {value};
        map.put(key, arr);
    }

    public void put( String keys, String keyDel, long value ) {
        StringTokenizer st = new StringTokenizer( keys, keyDel );
        int num = st.countTokens();
        for ( int i= 0; i < num; i++ ) {
            String key = st.nextToken();
            key = key.trim();
            put( key, value );
        }
    }

    public boolean contains( String key ) {
        return map.containsKey(key);
    }

    public Vector<Long> get(String key) {
        Vector <Long> vector = new Vector <Long>();
        for (int i = 0; i < map.size(); i++) {
            vector.add(map.get(key)[i]);
        }
        return vector;
    }
}

class KeyNotUniqueException extends Exception {
    // class release version:
    private static final long serialVersionUID = 1L;

    public KeyNotUniqueException( String key ) {
        super("Key is not unique: " + key);
    }
}

public class Index implements Serializable, Closeable {
    // class release version:
    private static final long serialVersionUID = 1L;

    public static long[] InsertValue( long[] arr, long value ) {
        int length = ( arr == null ) ? 0 : arr.length;
        long [] result = new long[length + 1];
        System.arraycopy(arr, 0, result, 0, length);
        result[length] = value;
        return result;
    }

    IndexOne2One userName;
    IndexOne2N trainerName;
    IndexOne2N date;

    public void test( sportComplexUserClass scu ) throws KeyNotUniqueException {
        assert( scu != null );
        if ( userName.contains(scu.userFullName)) {
            throw new KeyNotUniqueException( scu.userFullName );
        }
    }

    public void put(sportComplexUserClass scu, long value ) throws KeyNotUniqueException {
        test(scu);
        userName.put(scu.userFullName, value);
        trainerName.put(scu.trainerFullName, value);
        date.put(scu.dateAngTimeOfBeginning, value);
    }

    public Index()  {
        userName   = new IndexOne2One();
        trainerName = new IndexOne2N();
        date 	= new IndexOne2N();
    }

    public static Index load(String name) throws IOException, ClassNotFoundException {
        Index obj;
        try {
            FileInputStream file = new FileInputStream( name );
            try( ZipInputStream zis = new ZipInputStream( file )) {
                ZipEntry zen = zis.getNextEntry();
                /*if (!zen.getName().equals(Buffer.zipEntryName)) {
                    throw new IOException("Invalid block format");
                }*/
                try ( ObjectInputStream ois = new ObjectInputStream( zis )) {
                    obj = (Index) ois.readObject();
                }
            }
        } catch ( FileNotFoundException e ) {
            obj = new Index();
        }
        if ( obj != null ) {
            obj.save( name );
        }
        return obj;
    }

    private transient String filename = null;

    public void save( String name ) {
        filename = name;
    }

    public void saveAs( String name ) throws IOException {
        FileOutputStream file = new FileOutputStream( name );
        try ( ZipOutputStream zos = new ZipOutputStream( file )) {
            zos.putNextEntry( new ZipEntry( /*Buffer.zipEntryName*/"z" ));
            zos.setLevel( ZipOutputStream.DEFLATED );
            try ( ObjectOutputStream oos = new ObjectOutputStream( zos )) {
                oos.writeObject( this );
                oos.flush();
                zos.closeEntry();
                zos.flush();
            }
        }
    }

    public void close() throws IOException {
        saveAs( filename );
    }
}