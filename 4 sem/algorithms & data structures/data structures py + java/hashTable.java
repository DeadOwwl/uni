import java.io.*;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class hashTable {

    public static ArrayList<Integer> cellsChecking(int m, int c, int n, ArrayList<Integer> keys){
        ArrayList<Integer> hash = new ArrayList<>();
        for (int i = 0; i < m; i++)
            hash.add(-1);
        for (int iM = 0; iM < n; iM++){
            boolean isThere = false;
            for (int i = 0; i < m; i++)
                if (hash.get(i).equals(keys.get(iM))) {
                    isThere = true;
                    break;
                }
            if (!isThere){
                for (int i = 0; i < m; i++){
                    int address = (keys.get(iM) % m + c * i) % m;
                    if (hash.get(address) == -1){
                        hash.set(address, keys.get(iM));
                        break;
                    }
                }
            }
        }
        return hash;
    }

    public static void main(String[]args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("input.txt"));;
        BufferedWriter out = new BufferedWriter(new FileWriter("output.txt"));
        int mCondition, cCondition, nCondition;
        String line = in.readLine();
        StringTokenizer st = new StringTokenizer(line);
        mCondition = Integer.parseInt(st.nextToken());
        cCondition = Integer.parseInt(st.nextToken());
        nCondition = Integer.parseInt(st.nextToken());

        ArrayList<Integer> keysCondition = new ArrayList<>();
        for (int i = 0; i < nCondition; i++) {
            line = in.readLine();
            keysCondition.add(Integer.parseInt(line));
        }

        ArrayList<Integer> answer = cellsChecking(mCondition, cCondition, nCondition, keysCondition);
        for (int i = 0; i < mCondition; i++) {
            out.write(Integer.toString(answer.get(i)) + ' ');
            out.flush();
        }
    }
}
