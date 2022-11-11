package sportComplexUser;

import java.io.*;
import java.util.*;

public class sportComplexUsers {

    static final String filename = "sportComplexUsers.dat";
	private static  Scanner fin = new Scanner( System.in );
	
    static void delete_file() {
        File f = new File( filename );
        f.delete();
        System.out.println( "Deleting finished" );	
    }
	
    static void append_file() throws FileNotFoundException, IOException {
    	sportComplexUserClass sc = null;
        System.out.println( "Enter sport complex user data: " );
        if ( fin.hasNextLine()) {
            sc = sportComplexUserClass.read(fin);
        }
        try ( RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
                Buffer.writeObject( raf, sc );
        }
        System.out.println( "Appending finished" );	
    }

    static void print_file() throws FileNotFoundException, IOException, ClassNotFoundException {
        try ( RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            long pos;
            while (( pos = raf.getFilePointer()) < raf.length() ) {
            	sportComplexUserClass sc = (sportComplexUserClass) Buffer.readObject( raf, pos );
                System.out.println( pos + ": " + sc );
            }
        }
        System.out.println( "Printing finished" );	
    }
	
    public static void main(String[] args) {
    	Scanner input = new Scanner( System.in );
        try {
        	System.out.println("Please, choose the number of action:\n1. Append bill to file.\n2. Print file.\n3. Delete file.\n0. Exit program_____________________________");
        	int userChoice = 1;
        	while (userChoice != 0) {
        		System.out.println("Your choice: ");
        		userChoice = input.nextInt();
            switch(userChoice) {
            case 1:
                    // Append file with new object from System.in
                    append_file();
                    break;
            case 2:
                    // Prints data file
                    print_file();
                    break;
            case 3:
                    // Delete data file
                    delete_file();
                    break;
            case 0:
            	    break;
           default: 
                    System.err.println( "Option is not realised: " + args[0] );
                    System.exit(1);
                    break;
            }
            }
        }
        catch ( Exception e ) {
            System.err.println( "Run/time error: " + e );
            System.exit(1);
        }
        System.out.println( "Sport complex users finished" );	
        input.close();
	System.exit(0);
    }

}
