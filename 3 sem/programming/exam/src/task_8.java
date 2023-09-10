//¬ариант 8.
//—лова разделены пробелами.
//¬се слова в строке которые состо€т только из букв отсортировать и сохран€ть количество пробелов

import java.util.*;

public class task_8 {
    static ArrayList<String> wordsList = new ArrayList<String>();

    public static boolean isWord(String s) {
        for (int i = 0; i < s.length(); i++)
            if(!Character.isLetter(s.charAt(i)))
                return false;
        return true;
    }

    public static void processingLine(String s){
        StringTokenizer st = new StringTokenizer(s);
        while(st.hasMoreElements()){
            String w = st.nextToken();
            if(isWord(w))
                wordsList.add(w);
        }
    }

    public static void main(String[]args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter data: ");
        String l;
        while(scan.hasNextLine() && !(l = scan.nextLine()).equals(""))
            processingLine(l);
        System.out.println("Words: ");
        for (String str:wordsList)
            System.out.println(str);
    }
}
