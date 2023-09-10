import java.io.*;

public class necklace {

    static long combination(long n, long k){
        long[][] arr = new long [(int)n + 1][(int)(n + 1)];
        long a = 0;
        for (int i = 0; i <= n; ++i) {
            arr[i][0] = 1;
            arr[i][i] = 1;
            for(int j = 1; j < i; ++j) {
                if (j % 10 == 0)
                    System.gc();
                arr[i][j] = (arr[i - 1][j - 1] + arr[i - 1][j]) % 1000000007;
            }
            if (i == n)
                a = arr[(int)n][(int)k] % 1000000007;
        }
        return a;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("input.txt"));;
        BufferedWriter out = new BufferedWriter(new FileWriter("output.txt"));
        int n, k;

    }
}
