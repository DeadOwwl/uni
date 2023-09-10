import java.io.*;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class Dominoes {

    static int fin = 0, mt = 0;

    static boolean timeFinding(int n, ArrayList<ArrayList<Integer>> dominoes){
        LinkedList<Integer> bfsQueue = new LinkedList<>();
        int[] time = new int[n];
        boolean possible = false;
        int maxTime = -1;
        int finalStartVertex = -1;
        int lMaxTime;
        int checkedVertexes;
        int checkingCurrentVertex;
        boolean[] visited = new boolean[n];
        for(int k = 0; k < n; k++){
            lMaxTime = 0;
            for (int q = 0; q < n; q++)
                visited[q] = q == k;
            time[k] = 0;
            bfsQueue.add(0, k);
            checkedVertexes = 1;
            while (bfsQueue.size() != 0){
                checkingCurrentVertex = bfsQueue.get(bfsQueue.size() - 1);
                bfsQueue.remove(bfsQueue.size() - 1);
                for (int adjacentVertex: dominoes.get(checkingCurrentVertex)){
                    if (!visited[adjacentVertex]){
                        bfsQueue.add(0, adjacentVertex);
                        checkedVertexes++;
                        visited[adjacentVertex] = true;
                        time[adjacentVertex] = time[checkingCurrentVertex] + 1;
                        lMaxTime = Math.max(time[adjacentVertex], lMaxTime);
                    }
                }
            }
            if (checkedVertexes == n){
                possible = true;
                if (lMaxTime >= maxTime){
                    maxTime = lMaxTime;
                    finalStartVertex = k;
                }
            }
        }
        if (possible) {
            fin = finalStartVertex + 1;
            mt = maxTime;
        }
        return possible;
    }

    public static void main(String[]args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("in.txt"));
        int nCondition = Integer.parseInt(in.readLine());
        ArrayList<ArrayList<Integer>> dominoesCondition = new ArrayList<>();
        StringTokenizer st;
        int mCondition;
        ArrayList<Integer> listCondition = new ArrayList<>();
        for (int i = 0; i < nCondition; i++) {
            st = new StringTokenizer(in.readLine());
            mCondition = Integer.parseInt(st.nextToken());
            for (int j = 0; j < mCondition; j++)
                listCondition.add(Integer.parseInt(st.nextToken()) - 1);
            dominoesCondition.add(new ArrayList<>(listCondition));
            listCondition.clear();
        }
        in.close();
        boolean flag = timeFinding(nCondition, dominoesCondition);

        PrintWriter out = new PrintWriter("out.txt");
        if (flag)
            out.write((Integer.toString(mt) + '\n' + (fin)));
        else
            out.write("impossible");
        out.close();
    }
}