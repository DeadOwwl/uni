import java.io.*;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class roadsBuilding implements Runnable{
    public static void main(String[]args) {
        new Thread(null, new roadsBuilding(), "", 64 * 1024 * 1024).start();
    }

    void dfs(int v, boolean[] visited, ArrayList<ArrayList<Integer>> graph) {
        visited[v] = true;
        for (int u: graph.get(v)){
            if (!visited[u])
                dfs(u, visited, graph);
        }
    }

    int componentsCounting(int n, int q, ArrayList<ArrayList<Integer>> graph) {
        boolean[] visited = new boolean[n];
        for (int i = 0; i < n; i++)
            visited[i] = false;
        int count = 0;
        for (int v = 0; v < n; v++){
            if (!visited[v]){
                dfs(v, visited, graph);
                count++;
            }
        }
        return count;
    }

    @Override
    public void run() {
        try {
            BufferedReader in = new BufferedReader(new FileReader("input.txt"));
            BufferedWriter out = new BufferedWriter(new FileWriter("output.txt"));
            int nCondition, qCondition;
            StringTokenizer st = new StringTokenizer(in.readLine());
            nCondition = Integer.parseInt(st.nextToken());
            qCondition = Integer.parseInt(st.nextToken());
            ArrayList<ArrayList<Integer>> graphCondition = new ArrayList<>();
            for(int i = 0; i < nCondition; i++)
                graphCondition.add(new ArrayList<Integer>());
            ArrayList<Integer> components = new ArrayList<>(qCondition);
            for (int i = 0; i < nCondition; i++) {
                int a, b;
                st = new StringTokenizer(in.readLine());
                a = Integer.parseInt(st.nextToken());
                b = Integer.parseInt(st.nextToken());
                graphCondition.get(a - 1).add(b - 1);
                graphCondition.get(b - 1).add(a - 1);
                components.add(i, componentsCounting(nCondition, qCondition, graphCondition));
            }
            for (int i = 0; i < qCondition; i++) {
                if (i == qCondition - 1)
                    out.write(components.get(i).toString());
                else
                    out.write(components.get(i).toString() + '\n');
            }
            out.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
