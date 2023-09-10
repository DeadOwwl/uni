import java.io.*;
import java.util.StringTokenizer;

public class turtle {
    static int turtleWays(long n, long k){
        int[][] arr = new int [(int)n + 1][(int)n + 1];
        int a = 0;
        for (int i = 0; i <= n; ++i) {
            arr[i][0] = 1;
            arr[i][i] = 1;
            for(int j = 1; j < i; ++j)
                arr[i][j] = (arr[i-1][j-1] % 1000000007 + arr[i-1][j] % 1000000007) % 1000000007;
            if (i == n)
                a = arr[(int)n][(int)k];
        }
        return a % 1000000007;
    }

    public static void main(String[]args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("input.txt"));;
        BufferedWriter out = new BufferedWriter(new FileWriter("output.txt"));
        long n, m;
        String line = in.readLine();
        StringTokenizer st = new StringTokenizer(line);
        n = Long.parseLong(st.nextToken());
        m = Long.parseLong(st.nextToken());
        long num = turtleWays((m + n - 2) % 1000000007, (m - 1) % 1000000007);
        out.write(Long.toString(num));
        out.flush();
    }
}