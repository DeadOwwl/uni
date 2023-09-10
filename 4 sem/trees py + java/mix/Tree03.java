import java.io.*;
import java.util.*;

public class Tree03 implements Runnable {
    Integer info;
    Tree03 left;
    Tree03 right;

    public Tree03() {
        this.info = null;
        this.left = null;
        this.right = null;
    }

    public static void main(String[] args) {
        new Thread(null, new Tree03(), "", 64 * 1024 * 1024).start();
    }

    public void run() {
        BufferedReader in = null;
        BufferedWriter out = null;
        int nodesNum = 0;
        try {
            in = new BufferedReader(new FileReader("bst.in"));
            out = new BufferedWriter(new FileWriter("bst.out"));
            nodesNum = Integer.parseInt(in.readLine());
        } catch (IOException e) {
            e.printStackTrace();
        }
        int[] nodes = new int[nodesNum];
        long[][] borders = new long[nodesNum][2];
        boolean flag = true;
        StringTokenizer st = null;
        try {
            assert in != null;
            st = new StringTokenizer(in.readLine());
        } catch (IOException e) {
            e.printStackTrace();
        }
        assert st != null;
        nodes[0] = Integer.parseInt(st.nextToken());
        borders[0][0] = Long.MIN_VALUE;
        borders[0][1] = Long.MAX_VALUE;
        for (int i = 1; i < nodesNum; i++) {
            try {
                st = new StringTokenizer(in.readLine());
            } catch (IOException e) {
                e.printStackTrace();
            }
            int parentNum;
            String c;
            while(st.hasMoreTokens()){
                nodes[i] = Integer.parseInt(st.nextToken());
                parentNum = Integer.parseInt(st.nextToken());
                c = st.nextToken();
                parentNum--;
                if (c.equals("L")) {
                    borders[i][0] = borders[parentNum][0];
                    borders[i][1] = nodes[parentNum];
                }
                if(c.equals("R")){
                    borders[i][0] = nodes[parentNum];
                    borders[i][1] = borders[parentNum][1];
                }
                if (c.equals("L")) {
                    if(nodes[i] < borders[i][0] || nodes[i] >= borders[i][1]){
                        flag = false; break;
                    }
                }
                if(c.equals("R")){
                    if(nodes[i] < borders[i][0] || nodes[i] >= borders[i][1]){
                        flag = false; break;
                    }
                }
            }
            if(!flag)
                break;
        }
        String answer;
        if (!flag) answer = "NO";
        else answer = "YES";
        try {
            assert out != null;
            out.write(answer);
            out.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}