import java.io.*;
import java.util.*;

public class olympics{

    static int[][] graph;
    static boolean[] used;
    static int counter = 0;

    static void dfs(int v, int n){
        used[v] = true;
        counter++;
        for(int i = 0; i < n; i++)
            if (graph[v][i] == 1 && !used[i])
                dfs(i, n);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("input.in"));
        BufferedWriter out = new BufferedWriter(new FileWriter("output.out"));
        int nCondition = Integer.parseInt(in.readLine());
        graph = new int[nCondition][nCondition];
        used = new boolean[nCondition];
        Arrays.fill(used, false);
        for(int i = 0; i < nCondition; i++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            for (int j = 0; j < nCondition; j++) {
                graph[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        dfs(0, nCondition);
        if (counter == nCondition)
            out.write("YES");
        else
            out.write("NO");
        out.flush();
    }
}