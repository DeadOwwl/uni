//Вариант 10.
//Создать программу, которая читает текст из стандартного входного потока
//и печатает в выходной поток предложения исходного текста, в которых встречается фраза,
//указанная как обязательный параметр программы.

import java.util.*;

public class task_10 {

    static ArrayList<String> foundSentencesList = new ArrayList<String>();

    static void findArgs(String txt, String args){
        for (int i = 0; i < txt.length(); i++){
            if (txt.charAt(i) == '.' || txt.charAt(i) == '!' ||txt.charAt(i) == '?'){
                if((txt.substring(0, i + 1)).contains(args))
                    foundSentencesList.add(txt.substring(0, i + 1));
                txt = txt.substring(i + 1);
                i = 0;
            }
        }
    }

    public static void main(String[]args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter data: ");
        String l;
        String text = "";
        while(scan.hasNextLine() && !(l = scan.nextLine()).equals("")){
            text += l;
        }
        findArgs(text, args[0]);
        System.out.println("Sentences with required args: ");
        for (String str:foundSentencesList)
            System.out.println(str);
    }
}
