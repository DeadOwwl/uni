import java.io.*;

public class chip {
    static int module = 1000000007;

    public static int[] numberOfRoutes(int t, int[][]params) {
        int[] result = new int[t];
        for (int i = 0; i < t; i++) {
            int[] poss = new int[params[i][0]];
            poss[0] = 1;
            int sum = 1;
            for (int j = 1; j < params[i][0]; j++) {
                poss[j] = sum;
                sum = (poss[j] + sum) % module;
                if (j - params[i][1] >= 0) {
                    sum = (sum - poss[j - params[i][1]] + module) % module;
                }
            }
            result[i] = poss[params[i][0]-1];
        }
        return result;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("input.txt"));
        BufferedWriter out = new BufferedWriter(new FileWriter("output.txt"));
        int t = Integer.parseInt(in.readLine());
        int[][] parameters = new int[t][2];
        int[] answer;
        int i = 0;
        String line;
        String[] str;
        while ((line = in.readLine()) != null) {
            str = line.split(" ");
            parameters[i][0] = Integer.parseInt(str[0]);
            parameters[i][1] = Integer.parseInt(str[1]);
            i++;
        }
        answer = numberOfRoutes(t, parameters);
        for (int j : answer) out.write(Integer.toString(j) + '\n');
        out.close();
    }
}

//�������� ������� ������ �������, ����� �������, 10 ������, 2 ����, ����:
//��������� ��� ���������� ��������� ������������ �����, �������� ����� ����������� ����� ����, ��� ������������ ���� ����� ������������ �������� ���������, ��� ���� ����������� ������������ �������� ������ ���������� (<=k), ��� ����������� �� ���������� �����.
//������� � ������� numberOfRoutes, ������������ ����� ��� ������� ������ ����������.
//sum � ��������� ���������� �����, ����� ������� �� ����� ������ �� ��������� ������� �� ������� (� ����� �� i), ���������� �������� �� �������� � 1 (�� 1 ����������� ����������� ���� ������).