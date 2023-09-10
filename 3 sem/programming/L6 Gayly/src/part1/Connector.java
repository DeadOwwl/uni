package part1;

import java.io.*;
import java.util.ResourceBundle;

public class Connector {

    private final String filename;

    public Connector( String filename ) {
        this.filename = filename;
    }

    public void write( Patient[] MasPat) throws IOException {
        FileOutputStream fos = new FileOutputStream (filename);
        try ( ObjectOutputStream oos = new ObjectOutputStream( fos )) {
            oos.writeInt( MasPat.length );
            for (Patient patient : MasPat) {
                oos.writeObject(patient);
            }
            oos.flush();
        }
    }


    public Patient[] read(String filename) throws IOException {
        FileInputStream fis = new FileInputStream(filename);
        try (ObjectInputStream oin = new ObjectInputStream(fis)) {
            int length = oin.readInt();
            Patient[] result = new Patient[length];
            for (int i = 0; i < length; i++) {
                result[i] = (Patient) oin.readObject();
                result[i].resourceBundle = ResourceBundle.getBundle("Base");
            }
            return result;
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
        return null;
    }
}