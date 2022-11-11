package sportComplexUser;

import java.io.*;
import java.util.*;
import java.text.*;

public class sportComplexUserClass implements Serializable {
    // class release version:
    private static final long serialVersionUID = 1L;
    // areas with prompts:
    String userFullName; 			
    static final String P_userFullName = "Full Name";
    String sectionCode;				
    static final String P_sectionCode = "Section Code";
    String occupationType;				
    static final String P_occupationType = "Occupation";
    String trainerFullName;				
    static final String P_trainerFullName = "Trainer";
    String dateAngTimeOfBeginning;			
    static final String P_dateOfBeginning = "Date & time";
    int numOfMinutes;			
    static final String P_numOfMinutes = "Duration";
    double ratePerMinute;				
    static final String P_ratePerMinute = "Rate"; 
	
    public static Boolean nextRead( Scanner fin, PrintStream out ) {
        return nextRead( P_userFullName, fin, out );
    }
    
    static Boolean nextRead( final String prompt, Scanner fin, PrintStream out ) {
        out.print( prompt );
        out.print( ": " );
        return fin.hasNextLine();
    }

    public static sportComplexUserClass read( Scanner fin, PrintStream out ) throws IOException, ParseException{
        String str;
        sportComplexUserClass sportComplexUser = new sportComplexUserClass();
        
        if ( ! nextRead( P_userFullName, fin, out ))  
        	return null;
        sportComplexUser.userFullName = fin.nextLine();
        
        if ( ! nextRead( P_sectionCode, fin, out ))            
        	return null;
        sportComplexUser.sectionCode = fin.nextLine();
        
        if ( ! nextRead( P_occupationType, fin, out ))           
        	return null;
        sportComplexUser.occupationType = fin.nextLine();
        
        if ( ! nextRead( P_trainerFullName, fin, out ))  
        	return null;
        sportComplexUser.trainerFullName = fin.nextLine();
        
        if ( ! nextRead( P_dateOfBeginning, fin, out ))      
        	return null;
        str = fin.nextLine();
        SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy,HH:mm");
        Date docDate= sdf.parse(str);
		String formattedDate = sdf.format(docDate);
        sportComplexUser.dateAngTimeOfBeginning = formattedDate;
        
        if ( ! nextRead( P_numOfMinutes, fin, out ))       
        	return null;
        str = fin.nextLine();
        sportComplexUser.numOfMinutes = Integer.parseInt(str);
        
        if ( ! nextRead( P_ratePerMinute, fin, out ))           
        	return null;
        str = fin.nextLine();
        sportComplexUser.ratePerMinute = Double.parseDouble(str);
        
        return sportComplexUser;
    }
		
    public sportComplexUserClass() {
    }
	
    public static final String areaDel = "\n";

    public String toString() {
        return 
        	userFullName + areaDel +
            sectionCode + areaDel +
            occupationType + areaDel +
            trainerFullName + areaDel +
            dateAngTimeOfBeginning + areaDel +
            numOfMinutes + areaDel +
            ratePerMinute			
	;
    }
}
