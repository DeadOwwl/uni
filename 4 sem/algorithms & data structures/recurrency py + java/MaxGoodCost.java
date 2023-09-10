import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

public class MaxGoodCost {

    static String check(long n, long m, ArrayList<Long> allCash) {
        long customerSum = 0;
        for (int i = 0; i < n; i++) customerSum += allCash.get(i);
        Collections.sort(allCash);
        long allSum = 0;
        for (int i = 0; i < n + m; i++) {
            if (allCash.get(i) > allSum + 1)
                break;
            allSum += allCash.get(i);
        }
        if (allSum >= customerSum)
            return "YES";
        return "NO\n" + (customerSum - allSum - 1);
    }

    public static void main(String[]args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("input.txt"));
        BufferedWriter out = new BufferedWriter(new FileWriter("output.txt"));
        long n, m;
        StringTokenizer st = new StringTokenizer(in.readLine());
        n = Long.parseLong(st.nextToken());
        m = Long.parseLong(st.nextToken());
        String answer;
        ArrayList<Long> allCash = new ArrayList<>();
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++)
            allCash.add(Long.parseLong(st.nextToken()));
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < m; i++)
            allCash.add(Long.parseLong(st.nextToken()));
        answer = check(n, m, allCash);
        out.write(answer);
        out.flush();
    }
}