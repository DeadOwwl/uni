import java.util.*;

class Account implements Comparable<Account>, Iterable<String>, Iterator<String> {

    String fullName;
    int accountNumber;
    String accountCurrency;
    double annualPercentage;
    double accountSum;

    Account(String fN, int aN, String aC, double aP, double aS) {
        this.fullName = fN;
        this.accountNumber = aN;
        this.accountCurrency = aC;
        this.annualPercentage = aP;
        this.accountSum = aS;
    }

    public Account(String string) throws Exception {

        if (string == null)
            throw new Exception("Null pointer passed for initializing data");

        String[] dataAccount = string.split("\\s");

        if (dataAccount[0] != null && dataAccount[1] != null)
            this.fullName = dataAccount[0] + " " + dataAccount[1];
        else
            throw new Exception("Data error");

        if (Double.parseDouble(dataAccount[2]) > 0)
            this.accountNumber = Integer.parseInt(dataAccount[2]);
        else
            throw new Exception("Data error");

        if (dataAccount[3] != null && dataAccount[3].length() == 3)
            this.accountCurrency = dataAccount[3];
        else
            throw new Exception("Data error");

        if (Double.parseDouble(dataAccount[4]) > 0)
            this.annualPercentage = Double.parseDouble(dataAccount[4]);
        else
            throw new Exception("Data error");

        if (Double.parseDouble(dataAccount[5]) > 0)
            this.accountSum = Double.parseDouble(dataAccount[5]);
        else
            throw new Exception("Data error");
    }

    public static void swinthdrawAmount(Account a, double amount) throws Exception{
        if (a.accountSum - amount < 0)
            throw new Exception("Insufficient funds for the operation");
        a.accountSum -= amount;
    }

    public static boolean addAmount(Account a, double amount){
        a.accountSum += amount;
        return true;
    }

    public static boolean interestAccrual(Account a, double yearsPart){
        a.accountSum += a.accountSum * a.annualPercentage * yearsPart;
        return true;
    }



    public boolean hasNext () {
        return iter < 5;
    }

    public String next () {
        if (iter > 5)
            throw new IndexOutOfBoundsException("Outcome of borders.");
        switch (iter)
        {
            case 0:
                iter++;
                return fullName;
            case 1:
                iter++;
                return Integer.toString(accountNumber);
            case 2:
                iter++;
                return accountCurrency;
            case 3:
                iter++;
                return Double.toString(annualPercentage);
            case 4:
                iter++;
                return Double.toString(accountSum);
            default:
                return null;
        }
    }

    private static int s = 0;

    public int compareTo(Account a) {
        switch (s) {
            case 0:
                return Integer.compare(this.fullName.compareToIgnoreCase(a.fullName), 0);
            case 1:
                return Integer.compare(this.accountNumber, a.accountNumber);
            case 2:
                return Integer.compare(this.accountCurrency.compareToIgnoreCase(a.accountCurrency), 0);
            case 3:
                return Double.compare(this.annualPercentage, a.annualPercentage);
            default:
                return -1;
        }
    }

    public Iterator<String> iterator() {
        reset();
        return this;
    }

    int iter = 0;

    public void reset () {
        iter = 0;
    }

    public static Comparator<Account> getComparator(final int sortBy) {
        if ( sortBy >= 4 || sortBy < 0 ) {
            throw new IndexOutOfBoundsException();
        }
        return (a0, a1) -> {
            s = sortBy;
            return a0.compareTo(a1);
        };
    }

    public void remove () { }

    public String toString()
    {
        return ("User's Name: " + fullName +
                ";\nAccount number: " + accountNumber +
                ";\nCurrency: " + accountCurrency +
                ";\nAnnual Percentage: " + annualPercentage +
                ";\nAccount sum: " + accountSum + ";\n");
    }

    public static String[] formatStr =  {
            "%-15s",
            "%-15s",
            "%-10s",
            "%-20s",
            "%-15s",
    };

    public static String format() {
        return Account.format( Arrays.asList(Account.names ));
    }

    public static String format( Account it ) {
        return Account.format(((Iterable<String>) it ));
    }

    private static String format( Iterable<String> what ) {
        StringBuilder result = new StringBuilder();
        int idx = 0;
        for( Object str : what ) {
            result.append(String.format(formatStr[idx++], str));
        }
        return result.toString();
    }

    public static String getSortByName(int sortBy) {
        return Account.sortNames[sortBy];
    }

    public static final String[] sortNames =
            {
                    "User's Name",
                    "Account number",
                    "Currency",
                    "Annual Percentage",
            };

    public static final String[] names =
            {
                    "User's Name",
                    "Account number",
                    "Currency",
                    "Annual Percentage",
                    "Account sum",
            };
}