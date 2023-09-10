import java.io.*;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class ExactSurrender {

    static String check(long s, long n, long m, ArrayList<Long> allCash){
        long customerSum = 0, sellerSum = 0;
        for (int i = 0; i < n; i++) customerSum += allCash.get(i);
        for (int i = (int) n; i < n + m; i++) sellerSum += allCash.get(i);
        if (customerSum < s) return "No";
        boolean[] changePossibility = new boolean[(int)(customerSum + sellerSum - s + 1)];
        changePossibility[0] = true;
        for (long i = 0; i < n + m; i++) {
            for (long j = customerSum + sellerSum - s - allCash.get((int) i); j >= 0; j--)
                changePossibility[(int) (j + allCash.get((int) i))] = changePossibility[(int) j];
            if (changePossibility[(int) (customerSum - s)])
                break;
        }
        if (changePossibility[(int) (customerSum - s)])
            return "Yes";
        return "No";
    }

    static String checkOne(long s, long n, long m, ArrayList<Long> allCash){
        long customerSum = 0;
        for (int i = 0; i < n; i++) customerSum += allCash.get(i);
        if (customerSum < s) return "No";
        boolean[] changePossibility = new boolean[(int)(customerSum - s + 1)];
        changePossibility[0] = true;
        for (long i = 0; i < n + m; i++) {
            for (long j = customerSum - s - allCash.get((int) i); j >= 0; j--)
                changePossibility[(int) (j + allCash.get((int) i))] = changePossibility[(int) j];
            if (changePossibility[(int) (customerSum - s)])
                break;
        }
        if (changePossibility[(int) (customerSum - s)])
            return "Yes";
        return "No";
    }

    public static void main(String[]args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("input.txt"));
        BufferedWriter out = new BufferedWriter(new FileWriter("output.txt"));
        long n, m, s;
        StringTokenizer st = new StringTokenizer(in.readLine());
        n = Long.parseLong(st.nextToken());
        m = Long.parseLong(st.nextToken());
        s = Long.parseLong(st.nextToken());
        String answer;
        ArrayList<Long> allCash = new ArrayList<>();
        if (n != 0 && m != 0 && s != 0) {
            st = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++)
                allCash.add(Long.parseLong(st.nextToken()));
            st = new StringTokenizer(in.readLine());
            for (int i = 0; i < m; i++)
                allCash.add(Long.parseLong(st.nextToken()));
            answer = check(s, n, m, allCash);
        }
        else {
            if (n == 0 && m != 0 && s != 0)
                answer = "No";
            else if (n != 0 && m == 0 && s != 0) {
                st = new StringTokenizer(in.readLine());
                ArrayList<Long> customerCash = new ArrayList<>();
                for (int i = 0; i < n; i++)
                    customerCash.add(Long.parseLong(st.nextToken()));
                answer = checkOne(s, n, m, customerCash);
            } else
                answer = "Yes";
        }
        out.write(answer);
        out.flush();
    }
}