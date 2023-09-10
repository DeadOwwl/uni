//Вариант 18
// Из стандартного входного потока прочитать текст.
//Разделители - пробелы(один или несколько) и знак табуляции.
//В выходной поток:
//1) преобразовать строки таким образом, чтобы их длина не была больше 80, при этом нельзя "херачить слова"
//2) заменить \t на пробелы(без учёта позиционного табулирования)
//3) заменить несколько пробелов на один
//4) удалить пробелы:
//* в начале строки
//* в конце строки
//* перед знаками препинания


import java.util.*;

public class task_18 {

    static ArrayList<String> linesList = new ArrayList<String>();

    static String editLine(String s){
        StringTokenizer st = new StringTokenizer(s, " \t");
        StringBuilder ns = new StringBuilder();
        ArrayList<String> wordsList = new ArrayList<String>();
        while(st.hasMoreElements()) {
            String word = st.nextToken();
            wordsList.add(word);
        }
        for(int i = 0; i < wordsList.size() - 1; i++){
            if (wordsList.get(i + 1).equals("!") || wordsList.get(i + 1).equals("?") || wordsList.get(i + 1).equals(".") ||
                    wordsList.get(i + 1).equals(",") || wordsList.get(i + 1).equals(":") || wordsList.get(i + 1).equals(";"))
                ns.append(wordsList.get(i));
            else
                ns.append(wordsList.get(i)).append(' ');
        }
        ns.append(wordsList.get(wordsList.size() - 1));
        s = ns.toString();
        return s;
    }

    static void editText(String s){
        StringTokenizer st = new StringTokenizer(s);
        int position = 0;
        while(st.hasMoreElements()){
            String word = st.nextToken();
            position = s.indexOf(word, position);
            if (word.length() + position >= 80) {
                linesList.add(s.substring(0, position - 1));
                s = s.substring(position);
                position = 0;
            }
        }
        if (s.length() > 0)
            linesList.add(s);
    }

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter text: ");
        String l;
        StringBuilder text = new StringBuilder();
        while(scan.hasNextLine() && !(l = scan.nextLine()).equals(""))
            text.append(editLine(l)).append(' ');
        l = text.toString();
        l = l.substring(0, l.length() - 1);
        editText(l);
        System.out.println("Edited text: ");
        for(String line:linesList)
            System.out.println(line);
    }
}
