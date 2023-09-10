	/* Из входного потока прочитать слова.
     * Те которые только из цифр преобразовать в 16-ю запись и вывести 1 слово/строку
     */
import java.util.*;

public class task_7 {
    static ArrayList<String> hexList = new ArrayList<String>();

    public static boolean isDigit(String s){
        for (int i = 0; i < s.length(); i++)
            if (!Character.isDigit(s.charAt(i)))
                return false;
        return true;
    }

    public static void processingLine(String s){
        StringTokenizer st = new StringTokenizer(s);
        while(st.hasMoreElements()){
            String w = st.nextToken();
            String hex;
            if(isDigit(w)) {
                hex = Integer.toHexString(Integer.parseInt(w));
                hexList.add(hex);
            }
        }
    }

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Inter data: ");
        String l;
        while(scan.hasNextLine() && !(l = scan.nextLine()).equals(""))
            processingLine(l);
        System.out.println("Hexes: ");
        for(String h:hexList)
            System.out.println(h);
    }
}
