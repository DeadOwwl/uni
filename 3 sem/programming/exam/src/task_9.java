//¬ариант 9.
//»з стандартного входного потока считываютс€ строки.
//¬ каждой строке необходимо переставить слова в обратном пор€дке.
//¬ывести весь текст в стандартный выходной поток
//в тексте в каждом предложении вывести слова в обратном пор€дке

import java.util.*;

class Word{
    String value;
    int begin;
    int end;
    public Word(String s, int b){
        value = s;
        begin = b;
        end = b + s.length() - 1;
    }
}

public class task_9 {
    static ArrayList<String> linesList = new ArrayList<String>();

    public static String processLine(String s){
        StringBuilder sBld = new StringBuilder(s);
        ArrayList<Word> wordsList = new ArrayList<Word>();
        ArrayList<String> stringList = new ArrayList<String>();
        StringTokenizer sTknz = new StringTokenizer(s);
        int position = 0;
        while(sTknz.hasMoreElements()){
            String w = sTknz.nextToken();
            stringList.add(w);
            position = s.indexOf(w);
            wordsList.add(new Word(w, position));
        }
        for(int i = wordsList.size() - 1; i >= 0; i--)
            sBld.replace(wordsList.get(i).begin, wordsList.get(i).end + 1, stringList.get(wordsList.size() - 1 - i));
        return sBld.toString();
    }

    public static void main(String[]args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter data: ");
        String l;
        while(scan.hasNextLine() && !(l = scan.nextLine()).equals(""))
            linesList.add(processLine(l));
        System.out.println("Reversed lines: ");
        for(String str:linesList)
            System.out.println(str);
    }
}
