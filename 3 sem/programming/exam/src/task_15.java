//Вариант 15
// найти длинные числа, отсортировать и вывести с номерами строк, в которых они встречались

import java.util.*;

public class task_15 {
    static ArrayList<LongDigital> ldList = new ArrayList<LongDigital>();

    static class LongDigital implements Comparable<LongDigital>{
        int digitalValue;
        int line;

        public LongDigital(int dv, int l){
            digitalValue = dv;
            line = l;
        }

        public static boolean isLong(String s){
            if (s.charAt(s.length() - 1) == 'l' || s.charAt(s.length() - 1) == 'L'){
                for(int i = 0; i < s.length() - 1; i++)
                    if (!Character.isDigit(s.charAt(i)))
                        return false;
                return true;
            };
            return false;
        }
        @Override
        public int compareTo(LongDigital o) {
            return Integer.compare(digitalValue, o.digitalValue);
        }
    }

    static void processLine(String s, int n){
        StringTokenizer st = new StringTokenizer(s);
        while (st.hasMoreElements()){
            String word = st.nextToken();
            if (LongDigital.isLong(word)) {
                String cutWord = word.substring(0, word.length() - 1);
                ldList.add(new LongDigital(Integer.parseInt(cutWord), n));
            }
        }
    }

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter data: ");
        String l;
        int n = 0;
        while(scan.hasNextLine() && !(l = scan.nextLine()).equals("")) {
            processLine(l, n);
            n++;
        }
        Collections.sort(ldList);
        System.out.println("Long numbers: ");
        for(LongDigital dw : ldList)
            System.out.println("Number: " + dw.digitalValue +
                    ", Line: " + dw.line);
    }
}
