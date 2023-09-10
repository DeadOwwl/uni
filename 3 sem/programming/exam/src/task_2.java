//¬ариант 2
//ѕрограмма читает текст из стандартного входного потока, находит слова,
//начинающиес€ с заглавной буквы и выводит в стандартный выходной поток
//с новой строки

import java.util.*;

public class task_2 {
    static ArrayList<String> wordsList = new ArrayList<String>();

    static void processingLine(String s){
        StringTokenizer sTokenized = new StringTokenizer(s);
        while(sTokenized.hasMoreElements()) {
            String w = sTokenized.nextToken();
            if (Character.isUpperCase(w.charAt(0)))
                wordsList.add(w);
        }
    }

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Inter data: ");
        String l;
        while(scan.hasNextLine() && !(l = scan.nextLine()).equals(""))
            processingLine(l);
        scan.close();
        System.out.println("Words with 0-s upper case character: ");
        for(String str:wordsList)
            System.out.println(str);
    }
}
