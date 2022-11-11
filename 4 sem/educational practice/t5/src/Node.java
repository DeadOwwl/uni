public class Node {

    private final String naming;
    private final String year;
    private final String sculptors;
    private final String address;

    Node(String n, String y, String s, String a) {
        this.naming = n;
        this.year = y;
        this.sculptors = s;
        this.address = a;
    }

    public String getNaming() {
        return this.naming;
    }

    public String getYear() {
        return this.year;
    }

    public String getSculptors() {
        return this.sculptors;
    }

    public String getAddress() {
        return this.address;
    }

}