//¬ариант 25.
//
//прочитать все данные с входного потока, разделить на слова,
//выделить лексемы Java,представл€ющие собой дробные числа(float) со знаком.
//’ранить эти значени€ с номерами входных строк. ¬ывести, предварительно отсортировав
//в пор€дке убывани€ значений.
//—лова разделены пробелами. Ќайти знаковые литералы float и
//вывести в убывающей пор€дке с номером строки, в которой встречаютс€

import java.util.*;
import java.io.*;

public class task_25 {

    static ArrayList<floatNumber> fnList = new ArrayList<floatNumber>();

    static class floatNumber implements Comparable <floatNumber>{
        float value;
        int line;

        public floatNumber(String str, int n){
            value = Float.parseFloat(str.substring(0, str.length() - 1));
            line = n;
        }

        public static boolean isFloat(String s){
            if (s.charAt(s.length() - 1) == 'f' || s.charAt(s.length() - 1) == 'F') {
                try
                {
                    float num = Float.parseFloat(s.substring(0, s.length() - 1));
                    return true;
                }
                catch(Exception e){ return false;}
            }
            return false;
        }

        @Override
        public int compareTo(floatNumber o) {
            return Float.compare(o.value, value);
        }

        public String toString() { return "Number: " + value + ", line: " + line;}
    }

    static void processLine(String s, int n){
        StringTokenizer st = new StringTokenizer(s, " ");
        while(st.hasMoreElements()){
            String word = st.nextToken();
            if(floatNumber.isFloat(word))
                fnList.add(new floatNumber(word, n));
        }
    }

    public static void main(String[]args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter data: ");
        String l;
        int n = 0;
        while(scan.hasNextLine() && !(l = scan.nextLine()).equals("")) {
            processLine(l, n);
            n++;
        }
        Collections.sort(fnList);
        System.out.println("Float number after reversed sort: ");
        for(floatNumber fnum:fnList)
            System.out.println(fnum);
    }
}
