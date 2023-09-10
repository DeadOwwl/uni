import java.io.Serializable;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;
import java.util.StringTokenizer;

@SuppressWarnings("serial")
public class UtilityBill implements Serializable {
    private int homeNumber;
    private int flatNumber;
    private String address;
    private String name;
    private String paymentDate;
    private double paymentAmount;
    private double finePercent;
    private int expirationDays;

    public UtilityBill() {
    }

    public UtilityBill(int homeNumber, int flatNumber, String address, String name, String paymentDate, double paymentAmount, double finePercent, int expirationDays) throws ParseException {
        this.homeNumber = homeNumber;
        this.flatNumber = flatNumber;
        this.address = address;
        this.name = name;
        SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy");
        Date docDate= sdf.parse(paymentDate);
        this.paymentDate=sdf.format(docDate);
        this.paymentAmount = paymentAmount;
        this.finePercent = finePercent;
        this.expirationDays = expirationDays;
    }

    public UtilityBill(String s) throws ParseException {
        StringTokenizer str=new StringTokenizer(s," ,");
        if(str.hasMoreTokens())
        {
            this.homeNumber=Integer.parseInt(str.nextToken());
            this.flatNumber=Integer.parseInt(str.nextToken());
            this.address=str.nextToken();
            this.name=str.nextToken();
            SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy");
            Date docDate= sdf.parse(str.nextToken());
            this.paymentDate=sdf.format(docDate);
            this.paymentAmount=Double.parseDouble(str.nextToken());
            this.finePercent=Double.parseDouble(str.nextToken());
            this.expirationDays=Integer.parseInt(str.nextToken());
        }
    }
    public int getHomeNumber() {
        return homeNumber;
    }

    public void setHomeNumber(int homeNumber) {
        this.homeNumber = homeNumber;
    }

    public int getFlatNumber() {
        return flatNumber;
    }

    public void setFlatNumber(int flatNumber) {
        this.flatNumber = flatNumber;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPaymentDate() {
        return paymentDate;
    }

    public void setPaymentDate(String paymentDate) {
        this.paymentDate = paymentDate;
    }

    public double getPaymentAmount() {
        return paymentAmount;
    }

    public void setPaymentAmount(double paymentAmount) {
        this.paymentAmount = paymentAmount;
    }

    public double getFinePercent() {
        return finePercent;
    }

    public void setFinePercent(double finePercent) {
        this.finePercent = finePercent;
    }

    public int getExpirationDays() {
        return expirationDays;
    }

    public void setExpirationDays(int expirationDays) {
        this.expirationDays = expirationDays;
    }

    public static UtilityBill read(Scanner fin) throws ParseException {
        UtilityBill ub = new UtilityBill();
        ub.setHomeNumber(Integer.parseInt(fin.nextLine()));
        if (!fin.hasNextLine()) return null;
        ub.setFlatNumber(Integer.parseInt(fin.nextLine()));
        if (!fin.hasNextLine()) return null;
        ub.setAddress(fin.nextLine());
        if (!fin.hasNextLine()) return null;
        ub.setName(fin.nextLine());
        if (!fin.hasNextLine()) return null;
        SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy");
        Date docDate= sdf.parse(fin.nextLine());
        ub.setPaymentDate(sdf.format(docDate));
        if (!fin.hasNextLine()) return null;
        ub.setPaymentAmount(Double.parseDouble(fin.nextLine()));
        if (!fin.hasNextLine()) return null;
        ub.setFinePercent(Double.parseDouble(fin.nextLine()));
        if (!fin.hasNextLine()) return null;
        ub.setExpirationDays(Integer.parseInt(fin.nextLine()));
        return ub;
    }

    public String toString() {
        return new String (
                "homeNumber:" + homeNumber + "|" +
                        "flatNumber:" + flatNumber + "|" +
                        "address:" + address + "|" +
                        "name:" + name + "|" +
                        "paymentDate:" + paymentDate + "|" +
                        "paymentAmount:" + paymentAmount + "|" +
                        "finePercent:" + finePercent + "|" +
                        "expirationDays:" + expirationDays + ";"
        );
    }
}


