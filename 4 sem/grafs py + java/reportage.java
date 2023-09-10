import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

public class reportage {

    static ArrayList<Integer> indexInc = new ArrayList<>();//indexes
    static ArrayList<Integer> prevInc = new ArrayList<>();//prev
    static ArrayList<Integer> indexDec = new ArrayList<>();
    static ArrayList<Integer> prevDec = new ArrayList<>();

    public static int upper(ArrayList<Integer> arr,int key){
        int low = 0;
        int high = arr.size()-1;
        while(low < high){
            int mid = low + (high - low+1)/2;
            if(arr.get(mid) <= key){
                low = mid;
            }
            else{
                high = mid-1;
            }
        }
        return low;
    }

    static public void maxSubsequence(int n, ArrayList<Integer> al, ArrayList<Integer> indexes, ArrayList<Integer> prev){
        ArrayList<Integer> p = new ArrayList<>();
        ArrayList<Integer> d = new ArrayList<>();
        d.add(-2);
        ArrayList<Integer> a = new ArrayList<>();
        for (int i = 0; i <= n; i++){
            p.add(0);
            d.add(100001);
            indexes.add(1);
            prev.add(1);
        }
        int buf;
        for (int i = 0;i < n; i++){
            int j = upper(d, al.get(i)) - d.get(0);
            if (d.get(j - 1).equals(al.get(i)))
                indexes.set(i, j - 1);
            else
                indexes.set(i, j);
            if (d.get(j - 1) < al.get(i) && al.get(i) < d.get(j)){
                d.set(j, al.get(i));
                if (j == 1)
                    prev.set(i, -1);
                else
                    prev.set(i, p.get(j - 1));
                p.set(j, i);
            }
            else
                if (d.get(j - 1).equals(al.get(i))){
                    if (j == 2)
                        prev.set(i, -1);
                    else prev.set(i, p.get(j - 2));
                }
        }
    }

    static public void mainSolving(int n, ArrayList<Integer> heights) throws IOException {
        ArrayList<Integer> ans = new ArrayList<>();
        ArrayList<Integer> reversedHeights = heights;
        Collections.reverse(reversedHeights);
        maxSubsequence(n, heights, indexInc, prevInc);
        maxSubsequence(n, reversedHeights, indexDec, prevDec);
        indexInc.remove(indexInc.size() - 1);
        prevInc.remove(indexInc.size() - 1);
        indexDec.remove(indexInc.size() - 1);
        prevDec.remove(indexInc.size() - 1);
        int max = -1;
        int index = 0;
        for (int i = 0; i < n; i++){
            if (Math.min(indexInc.get(i) - 1, indexDec.get(i) - 1) > max){
                max = Math.min(indexInc.get(i) - 1, indexDec.get(i) - 1);
                index = i;
            }
        }
        int j = index;
        for (int i = 0; i < max; i++){
            ans.add(prevInc.get(j) + 1);
            j = prevInc.get(j);
        }
        Collections.reverse(ans);
        ans.add(index + 1);
        for (int i = 0; i < max; i++){
            ans.add(n - prevDec.get(j));
            j = n - prevDec.get(j) - 1;
        }

        BufferedWriter out = new BufferedWriter(new FileWriter("report.out"));
        out.write(Integer.toString(max) + '\n');
        for (Integer i:ans)
            out.write(i.toString() + ' ');
        out.close();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("report.in"));
        int nCondition = Integer.parseInt(in.readLine());
        ArrayList<Integer> heightsCondition = new ArrayList<>();
        String line = in.readLine();
        StringTokenizer st = new StringTokenizer(line);
        for(int i = 0; i < nCondition; i++)
            heightsCondition.add(Integer.parseInt(st.nextToken()));
        in.close();

        mainSolving(nCondition, heightsCondition);
    }
}
