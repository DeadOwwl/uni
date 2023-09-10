/* ������� 12
 * ���������� ������������ �������� ������ ����������� � ��������, ���������� ������ �������� ����� ��������� �������:
 * ������ ������� ������ ������� �� ����, ����������� ����� ��� ����������� ���������.
 * ����������� � ��� �����, ��������� ������ �� ���� ���, ����� ��� ���� ����������� �� ����������� ����� �� ����.
 * ��� ���� ������ ����� ������ ���������� �� �����, ���������� �������� ������ ���������� ����� ��, ��� � � �������� ������.
 */


import java.util.*;

class DigitalWord implements Comparable<DigitalWord>{
    String value;
    int begin, end, sum;

    public static boolean isDigitalWord(String s){
        for (int i = 0; i < s.length(); i++)
            if (!Character.isDigit(s.charAt(i)))
                return false;
        return true;
    }

    public DigitalWord(String s, int b){
        value = s;
        begin = b;
        end = b + s.length() - 1;
        sum = 0;
        for(int i = 0; i < s.length(); i++)
            sum += (s.charAt(i) - '0');
    }

    @Override
    public int compareTo(DigitalWord dw) {
        return Integer.compare(sum, dw.sum);
    }
}

public class task_12 {
    static ArrayList<String> linesList = new ArrayList<String>();

    static void processingLine (String line) {
        StringBuilder sBldr = new StringBuilder(line);
        ArrayList<DigitalWord> beforeDigitsList = new ArrayList<DigitalWord>();
        ArrayList<DigitalWord> afterDigitsList = new ArrayList<DigitalWord>();
        StringTokenizer sttok = new StringTokenizer(line, " \t");
        int pos = 0;
        while (sttok.hasMoreElements()) {
            String word = sttok.nextToken();
            pos = line.indexOf(word, pos);
            if ( DigitalWord.isDigitalWord(word) ) {
                DigitalWord dw = new DigitalWord(word, line.indexOf(word));
                beforeDigitsList.add(dw);
                afterDigitsList.add(dw);
            }
            pos += word.length();
        }
        Collections.sort(afterDigitsList);
        for (int i = afterDigitsList.size() - 1; i >= 0; --i)
            sBldr.replace(beforeDigitsList.get(i).begin,
                    beforeDigitsList.get(i).end + 1,
                    afterDigitsList.get(i).value);
        linesList.add(sBldr.toString());
    }

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter data: ");
        String l;
        while(scan.hasNextLine() && !(l = scan.nextLine()).equals(""))
            processingLine(l);
        scan.close();
        System.out.println("Edited data: ");
        for(String line:linesList)
            System.out.println(line);
    }
}
