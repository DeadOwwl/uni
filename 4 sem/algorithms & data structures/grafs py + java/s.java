import java.io.*;
import java.util.*;

public class s implements Runnable{

    static int[] vertexes_components;
    static ArrayList<Integer> order;
    static boolean[] used;
    static boolean[] used_transposed;

    public static void dfs(int v, boolean[] used_dfs, ArrayList<ArrayList<Integer>> graph_dfs, boolean is_transposed, int c) {
        if (used_dfs[v]) return;
        used_dfs[v] = true;
        if (is_transposed) vertexes_components[v] = c;
        for (int i = 0; i < graph_dfs.get(v).size(); i++) {
            int u = graph_dfs.get(v).get(i);
            if (!used_dfs[u]) dfs(u, used_dfs, graph_dfs, is_transposed, c);
        }
        if (!is_transposed) order.add(v);
    }


    public static ArrayList<Integer> defining(int n, ArrayList<ArrayList<Integer>> graph, ArrayList<ArrayList<Integer>> transposed_graph, ArrayList<Integer> terminals, int components) {
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 0; i < n; i++)
            if (!used[i]) dfs(i, used, graph, false, components);
        Collections.reverse(order);
        for (int i = 0; i < order.size(); i++) {
            int v = order.get(i);
            if (vertexes_components[i] == -1) {
                dfs(v, used_transposed, transposed_graph, true, components);
                components += 1;
            }
        }
        int max_vertex = vertexes_components[0];
        for (int vc : vertexes_components)
            max_vertex = Math.max(max_vertex, vc);
        int k_comp = max_vertex + 1;
        ArrayList<ArrayList<Integer>> component_array = new ArrayList<>(k_comp);
        for (int i = 0; i < k_comp; i++)
            component_array.add(new ArrayList<>());
        for (int i = 0; i < vertexes_components.length; i++)
            component_array.get(vertexes_components[i]).add(i);
        ArrayList<Integer> min_vertexes = new ArrayList<>();
        for (int i = 0; i < k_comp; i++) {
            int min_comp_vert = component_array.get(i).get(0);
            int min_comp_terminals = terminals.get(min_comp_vert);
            int our_vertex = min_comp_vert;
            for (int j = 0; j < component_array.get(i).size(); j++) {
                int st_term = component_array.get(i).get(j);
                if (min_comp_terminals > terminals.get(st_term)) {
                    our_vertex = st_term;
                    min_comp_terminals = terminals.get(st_term);
                }
            }
            min_vertexes.add(our_vertex);
        }
        order.clear();
        for (int i = 0; i < n; i++) used[i] = false;
        for (int v : min_vertexes) {
            if (!used[v]) {
                ans.add(v + 1);
                dfs(v, used, graph, false, 0);
            }
        }
        return ans;
    }

    public static void main(String[]args) {
        new Thread(null, new s(), "", 64 * 1024 * 1024).start();
    }

    public void run() {
        try {
            BufferedReader f = new BufferedReader(new FileReader("input.txt"));
            BufferedWriter w = new BufferedWriter(new FileWriter("output.txt"));
            int n_condition = Integer.parseInt(f.readLine());

            ArrayList<ArrayList<Integer>> graph_condition = new ArrayList<>(n_condition);
            ArrayList<ArrayList<Integer>> transposed_graph_condition = new ArrayList<>(n_condition);
            for (int i = 0; i < n_condition; i++) {
                graph_condition.add(new ArrayList<>());
                transposed_graph_condition.add(new ArrayList<>());
            }
            ArrayList<Integer> terminals_condition = new ArrayList<>();
            for (int i = 0; i < n_condition; i++)
                terminals_condition.add(Integer.parseInt(f.readLine()));
            StringTokenizer st;
            int u, v;
            do {
                st = new StringTokenizer(f.readLine());
                u = Integer.parseInt(st.nextToken());
                v = Integer.parseInt(st.nextToken());
                if (u == 0 && v == 0)
                    break;
                graph_condition.get(u - 1).add(v - 1);
                transposed_graph_condition.get(v - 1).add(u - 1);
            } while (true);

            used = new boolean[n_condition];
            used_transposed = new boolean[n_condition];
            Arrays.fill(used, false);
            Arrays.fill(used_transposed, false);
            vertexes_components = new int[n_condition];
            Arrays.fill(vertexes_components, -1);
            int components_condition = 0;
            order = new ArrayList<>(n_condition);
            ArrayList<Integer> answer = defining(n_condition, graph_condition,
                    transposed_graph_condition, terminals_condition, components_condition);
            w.write(Integer.toString(answer.size()) + '\n');
            for (int i = 0; i < answer.size(); i++) {
                w.write(Integer.toString(answer.get(i)));
                if (i != answer.size() - 1) w.write(' ');
            }
            w.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}