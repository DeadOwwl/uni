import java.io.*;
import java.util.*;

public class Dfs {
    static int[][] graph;
    static boolean[] used;
    static int counter = 1;
    static ArrayList <Integer> times;

    static void dfs(int v, int n){
        used[v] = true;
        times.set(v, counter++);
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
        times = new ArrayList<Integer>();
        for (int i = 0; i < nCondition; i++)
            times.add(0);
        Arrays.fill(used, false);
        for(int i = 0; i < nCondition; i++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            for (int j = 0; j < nCondition; j++) {
                graph[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        for (int i = 0; i < nCondition; i++)
            if (!used[i])
                dfs(i, nCondition);

        for (int i = 0; i < nCondition; i++)
            out.write(times.get(i).toString() + ' ');
        out.flush();
    }
}