/*Вариант 4
        Стандартный входной поток.
        Найти все вопросительные предложения и вывести каждый с новой строки.*/
import java.util.*;

public class task_4 {
    static ArrayList<String> questionsList = new ArrayList<String>();

    static void processingLine(String s){
        for (int i = 0; i < s.length(); i++){
            if (s.charAt(i) == '?'){
                String sentence = s.substring(0, i + 1);
                questionsList.add(sentence);
                s = s.substring(i + 1);
                i = 0;
            }
            else
                if (s.charAt(i) == '.' || s.charAt(i) == '!'){
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
        System.out.println("Questions: ");
        for(String str:questionsList)
            System.out.println(str);
    }
}
