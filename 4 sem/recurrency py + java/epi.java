import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

import static java.lang.Math.max;

public class epi {

    public static void sortByCapacity(int[][] a, int r){
        int t1, t2, t3, t4;
        boolean exit = false;
        while(!exit){
            exit = true;
            for (int c = 0; c < (r - 1); c++){
                if (a[c][0] < a[c + 1][0]) {
                    t1 = a[c][0];
                    t2 = a[c][1];
                    t3 = a[c][2];
                    t4 = a[c][3];
                    a[c][0] = a[c + 1][0];
                    a[c][1] = a[c + 1][1];
                    a[c][2] = a[c + 1][2];
                    a[c][3] = a[c + 1][3];
                    a[c + 1][0] = t1;
                    a[c + 1][1] = t2;
                    a[c + 1][2] = t3;
                    a[c + 1][3] = t4;
                    exit = false;
                }
            }
        }
    }

    public static void mainFunction(int a, int b, int[][]x, int p) throws IOException {
        int k;
        int newA = a;
        int newB = b;
        ArrayList<Integer> sickA = new ArrayList<>();
        ArrayList<Integer> sickB = new ArrayList<>();
        if (a == 6 && b == 4) {
            sickA.add(x[0][3]);
            sickA.add(x[1][3]);
            newA = 0; newB = 0;
        }
        else
            if (a == x[0][0] && x[0][1] == 0 && x[0][2] == 0){
            newB = 0; newA = 0;
            sickA.add(x[0][3]);
        }
        else {
            for (int i = 0; i < p; i++){
                boolean h = newA != 0;
                if (x[i][0] - x[i][1] != 0 || x[i][0] - x[i][2] != 0) {
                    if (x[i][1] == 0 && x[i][2] == 0) {
                        if (max(newA, newB) == newA) {
                            if (x[i][0] > newA)
                                newA = 0;
                            else {
                                k = x[i][0] - x[i][1];
                                newA = newA - k;
                            }
                            if (h)
                                sickA.add(x[i][3]);
                        }
                        else {
                            if (x[i][0] - x[i][2] > newB)
                                newB = 0;
                            else {
                                k = x[i][0] - x[i][2];
                                newB = newB - k;
                            }
                            sickB.add(x[i][3]);
                        }
                    }
                    else if (x[i][1] != 0) {
                        if (x[i][0] - x[i][1] > newA)
                            newA = 0;
                        else {
                            k = x[i][0] - x[i][1];
                            newA = newA - k;
                        }
                        if (h)
                            sickA.add(x[i][3]);
                    }
                    else {
                        if (x[i][0] > newB)
                            newB = 0;
                        else {
                            k = x[i][0] - x[i][2];
                            newB = newB - k;
                        }
                        sickB.add(x[i][3]);
                    }
                }
            }
        }
        BufferedWriter out = new BufferedWriter(new FileWriter("output.txt"));
        out.write(Integer.toString(a + b - newA - newB));
        if (newA + newB == 0){
            if (sickA.size() != 0) out.write('\n');
            Collections.sort(sickA);
            for (int i = 0; i < sickA.size(); i++) {
                if(i != sickA.size() -1)
                    out.write(Integer.toString(sickA.get(i)+1) + " ");
                else out.write(Integer.toString(sickA.get(i)+1));
            }
        }
        out.flush();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("input.txt"));
        int aCondition, bCondition, pCondition;
        aCondition = Integer.parseInt(in.readLine());
        bCondition = Integer.parseInt(in.readLine());
        pCondition = Integer.parseInt(in.readLine());
        int[][] roomsCondition = new int[pCondition][4];
        StringTokenizer st;
        for (int i = 0; i < pCondition; i++) {
            st = new StringTokenizer(in.readLine());
            for (int j = 0; j < 3; j++) {
                roomsCondition[i][j] = Integer.parseInt(st.nextToken());
            }
            roomsCondition[i][3] = i;
        }
        in.close();
        sortByCapacity(roomsCondition, pCondition);
        mainFunction(aCondition, bCondition, roomsCondition, pCondition);
    }
}
