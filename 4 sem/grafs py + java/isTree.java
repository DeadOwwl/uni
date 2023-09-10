import java.io.*;
import java.util.*;

public class isTree{

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
        BufferedReader in = new BufferedReader(new FileReader("input.txt"));
        BufferedWriter out = new BufferedWriter(new FileWriter("output.txt"));
        int nCondition = Integer.parseInt(in.readLine());
        graph = new int[nCondition][nCondition];
        used = new boolean[nCondition];
        Arrays.fill(used, false);
        int edgesNum = 0;
        for(int i = 0; i < nCondition; i++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            for (int j = 0; j < nCondition; j++) {
                graph[i][j] = Integer.parseInt(st.nextToken());
                edgesNum += graph[i][j];
            }
        }
        edgesNum /= 2;

        dfs(0, nCondition);
        if (edgesNum == nCondition - 1 && counter == nCondition)
            out.write("Yes");
        else
            out.write("No");
        out.flush();
    }
}