package Model;

import java.io.*;

public class sportComplexUserClass implements Serializable {

    private static final long serialVersionUID = 1L;

    public String userFullName;
    public int sectionCode;
    public String occupationType;
    public String trainerFullName;
    public String dateAngTimeOfBeginning;
    int numOfMinutes;
    double ratePerMinute;

    public sportComplexUserClass(String uFN, int sC, String oT, String tFN, String dATOB, int nOM, double rPM) {
        userFullName = uFN;
        sectionCode = sC;
        occupationType = oT;
        trainerFullName = tFN;
        dateAngTimeOfBeginning = dATOB;
        numOfMinutes = nOM;
        ratePerMinute = rPM;
    }

    public static final String areaDel = "|";

    public String toString() {
        return areaDel + userFullName + areaDel +
                sectionCode + areaDel +
                occupationType + areaDel +
                trainerFullName + areaDel +
                dateAngTimeOfBeginning + areaDel +
                numOfMinutes + areaDel +
                ratePerMinute + areaDel;
    }
}
