//Найти в тексте слова состоящие из цифр и вывести
import java.util.*;

public class task_6 {
    static ArrayList<String> stringDigitsList = new ArrayList<String>();

    public static boolean isDigit(String s){
        for (int i = 0; i < s.length(); i++)
            if (!Character.isDigit(s.charAt(i)))
                return false;
        return true;
    }

    public static void main(String[]args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter data: ");
        String l;
        while(scan.hasNextLine() && !(l = scan.nextLine()).equals("")){
            StringTokenizer st = new StringTokenizer(l);
            while(st.hasMoreElements()){
                String w = st.nextToken();
                if (isDigit(w))
                    stringDigitsList.add(w);
            }
        }
        System.out.println("Digits: ");
        for(String str:stringDigitsList)
            System.out.println(str);
    }
}
