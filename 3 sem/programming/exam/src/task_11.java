/* Вариант 11
 со стандартного входного потока прочитать строки и преобразовать следующим образом:
 слова состоят только из букв, все остальное считать разделителями;
 найти все палиндромы, отсортировать в исходной строке;
 остальные слова меняться не должны, разделители должны оставаться
 на местах и количество пробелов оставаться прежним */
import java.util.*;

class Palindrome implements Comparable<Palindrome>{
    protected String value;
    protected int begin, end;

    public static boolean isPalindrome(String s){
        String reversed = "";
        for(int i = s.length() - 1; i >= 0; i--)
            reversed += s.charAt(i);
        return s.equals(reversed);
    }

    public Palindrome(String v, int b){
        value = v;
        begin = b;
        end = b + v.length() - 1;
    }

    public Palindrome(Palindrome p){
        value = p.value;
        begin = p.begin;
        end = p.end;
    }

    @Override
    public int compareTo(Palindrome p) {
        return value.compareTo(p.value);
    }
}

public class task_11 {
    static ArrayList<String> linesList = new ArrayList<String>();

    static String getDelimiters(String s){
        String delims = "";
        for(int i = 0; i < s.length(); i++)
            if (!Character.isLetter(s.charAt(i)))
                delims += s.charAt(i);
        return delims;
    }

    static void processingLine(String s){
        StringBuilder sortedLine = new StringBuilder(s);
        ArrayList<Palindrome> beforePalindromesList = new ArrayList<Palindrome>();
        ArrayList<Palindrome> afterPalindromesList = new ArrayList<Palindrome>();
        StringTokenizer tokenizedLine = new StringTokenizer(s, getDelimiters(s));
        int pos = 0;
        while(tokenizedLine.hasMoreElements()){
            String word = tokenizedLine.nextToken();
            pos = s.indexOf(word, pos);
            if (Palindrome.isPalindrome(word)){
                beforePalindromesList.add(new Palindrome(word, pos));
                afterPalindromesList.add(new Palindrome(word, pos));
            }
            pos += word.length();
        }
        afterPalindromesList.sort(null);
        for(int i = beforePalindromesList.size() - 1; i >= 0; i--)
            sortedLine.replace(beforePalindromesList.get(i).begin,
                    beforePalindromesList.get(i).end + 1,
                    afterPalindromesList.get(i).value);
        linesList.add(sortedLine.toString());
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
