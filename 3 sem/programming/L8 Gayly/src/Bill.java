import java.io.*;
import java.util.*;

public class Bill implements Serializable {
    private static final long serialVersionUID = 1L;
    String houseNumber;
    static final String P_houseNumber = "House number";
    String flatNumber;
    static final String P_flatNumber = "Flat number";
    String name;
    static final String P_name = "Name";
    String address;
    static final String P_address = "Address";
    String date;
    static final String P_date = "Bill date";
    String billSum;
    static final String P_billSum = "Bill sum";
    String percent;
    static final String P_percent = "Percent";
    String deadline;
    static final String P_deadline = "Deadline";

    static Boolean validDate(String str) {
        StringTokenizer st = new StringTokenizer(str, ":. ");
        if (st.countTokens() != 3) {
            return false;
        }
        GregorianCalendar date = new GregorianCalendar();
        date.setLenient(false);
        int day = Integer.parseInt(st.nextToken());
        int month = Integer.parseInt(st.nextToken());
        int year = Integer.parseInt(st.nextToken());
        date.set(year, month, day);
        date.getTime();
        return true;
    }

    public static Boolean nextRead(Scanner fin, PrintStream out) {
        return nextRead(P_houseNumber, fin, out);
    }

    static Boolean nextRead(final String prompt, Scanner fin, PrintStream out) {
        out.print(prompt);
        out.print(": ");
        return fin.hasNextLine();
    }

    public static Bill read(Scanner fin, PrintStream out) throws IOException {
        Bill bill = new Bill();
        bill.houseNumber = fin.nextLine();

        if (!nextRead(P_flatNumber, fin, out)) return null;
        bill.flatNumber = fin.nextLine();
        if (!nextRead(P_name, fin, out)) return null;
        bill.name = fin.nextLine();
        if (!nextRead(P_address, fin, out)) return null;
        bill.address = fin.nextLine();
        if (!nextRead(P_date, fin, out)) return null;
        bill.date = fin.nextLine();

        if (!Bill.validDate(bill.date))
            throw new IOException("Invalid date value");

        if (!nextRead(P_billSum, fin, out)) return null;
        bill.billSum = fin.nextLine();
        if (!nextRead(P_percent, fin, out)) return null;
        bill.percent = fin.nextLine();
        if (!nextRead(P_deadline, fin, out)) return null;
        bill.deadline = fin.nextLine();

        return bill;
    }

    public Bill() {}

    public static final String areaDel = " | ";

    public String toString() {
        return  date + areaDel +
                name + areaDel +
                address + areaDel +
                houseNumber + areaDel +
                flatNumber + areaDel +
                billSum + areaDel +
                percent + areaDel +
                deadline;
    }
}