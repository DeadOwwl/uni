
/*������� 3.
        ������� ���������, ������ ������ ����� �� ������������ �������� ������,
        ��������� ��� �� ����������� � ������� �� � ����������� ����� �� ������
        ����������� � ������, �������� ��� ����� ��������������� �����������
        � ������� �������.*/

import java.util.*;

public class task_3 {
    static ArrayList<String> sentencesList = new ArrayList<String>();

    static void processingLine(String s){
        for(int i = 0; i < s.length(); i++){
            if (s.charAt(i) == '!'){
                String sentence = s.substring(0, i + 1);
                sentencesList.add(sentence.toUpperCase());
                s = s.substring(i + 1);
                i = 0;
            }
            else
                if (s.charAt(i) == '.' || s.charAt(i) == '?') {
                    String sentence = s.substring(0, i + 1);
                    sentencesList.add(sentence);
                    s = s.substring(i + 1);
                    i = 0;
                }
        }
    }

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);

        System.out.println("Inter data: ");
        String l;
        while(scan.hasNextLine() && !(l = scan.nextLine()).equals(""))
            processingLine(l);
        System.out.println("Divided sentences: ");
        for(String str:sentencesList)
            System.out.println(str);
    }
}
