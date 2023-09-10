/* ¬ариант 13
 * заменить в строке 8 пробелов сто€щих подр€д на символ табул€ции */

import java.util.*;

public class task_13 {
    static ArrayList<String> linesList = new ArrayList<String>();

    static void processingLine(String s){
        StringBuilder sBldr = new StringBuilder(s);
        String spaces = "        ";
        int position = sBldr.indexOf(spaces, 0);
        while(position != -1){
            sBldr.replace(position, position + 8, "\t");
            position = sBldr.indexOf(spaces, position);
        }
        linesList.add(sBldr.toString());
    }

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter data: ");
        String l;
        while(scan.hasNextLine() && !(l = scan.nextLine()).equals(""))
            processingLine(l);
        System.out.println("Edited data: ");
        for(String str:linesList)
            System.out.println(str);
    }
}
