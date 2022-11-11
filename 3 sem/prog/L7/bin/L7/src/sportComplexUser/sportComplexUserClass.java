package sportComplexUser;

import java.io.Serializable;
import java.util.Scanner;

@SuppressWarnings("serial")
public class sportComplexUserClass implements Serializable {
	String userFullName;
	String sectionCode;
	String occupationType;
	String trainerFullName;
	String dateAndTimeOfBeginning;
	String numOfMinutes;
	String ratePerMinute;
	
	public sportComplexUserClass() {}
	
    public static sportComplexUserClass read( Scanner fin ) {
    	sportComplexUserClass sportComplexUser = new sportComplexUserClass();
    	sportComplexUser.userFullName = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        sportComplexUser.sectionCode = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        sportComplexUser.occupationType = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        sportComplexUser.trainerFullName = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        sportComplexUser.dateAndTimeOfBeginning = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        sportComplexUser.numOfMinutes = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        sportComplexUser.ratePerMinute = fin.nextLine(); 
        return sportComplexUser;
    }

    public String toString() {
        return new String (
        	userFullName + "|" +
        	sectionCode + "|" +
        	occupationType + "|" +
        	trainerFullName + "|" +
        	dateAndTimeOfBeginning + "|" +
        	numOfMinutes + "|" +
        	ratePerMinute			
        );
    }
}