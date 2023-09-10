//¬ариант 1.
//»з стандартного входного потока прочитать текст
//и в стандартный выходной поток вывести все цитаты.
//÷итата Ч это текст между двойными кавычками

import java.util.*;

public class task_1 {
    static ArrayList<String> quotesList = new ArrayList<>();

    static void processingLine(String s){
        int begin = s.indexOf('"');
        int end = s.indexOf('"', begin + 1);
        while(end != -1){
            quotesList.add(s.substring(begin + 1, end));
            s = s.substring(0, begin) + s.substring(end + 1, s.length());
            begin = s.indexOf('"');
            end = s.indexOf('"', begin + 1);
        }
    }

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Inter data to start: ");
        String l;
        while (scan.hasNextLine() && !(l = scan.nextLine()).equals(""))
            processingLine(l);
        scan.close();
        System.out.println("Quotes: ");
        for(String s : quotesList)
            System.out.println(s);
    }
}