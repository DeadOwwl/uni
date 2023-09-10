//Вариант 16 #1
// Вводится строка. Задача: посчитать выражение, состоящее из целых, действительных чисел.
//операции + - * /
//если выражение некорректно, то вывести "?"
//если всё ок, то вывести результат
//присутствие лишних пробелов допустимо в исходных данных...

//import java.util.*;
//
//public class task_16 {
//
//    static void Checking(char[] mas, String str) {
//        for (int i = 0; i < str.length(); i++) {
//            if ((mas[i] == '*' || mas[i] == '+' || mas[i] == '-' || mas[i] == '/') && (i == 0 || (i == str.length() - 1))) {
//                System.out.println("Некорректные данные");
//                System.exit(0);
//            } else {
//                if ((mas[i] != 0 && mas[i] == '0' &&  mas[i - 1] == '/')) {
//                    System.out.println("Деление на ноль");
//                    System.exit(0);
//                } else {
//                    if (i != 0 && (mas[i] == '*' || mas[i] == '+' || mas[i] == '-' || mas[i] == '/') && (mas[i - 1] == '*'
//                            || mas[i - 1] == '+' || mas[i - 1] == '-' || mas[i - 1] == '/')) {
//                        System.out.println("Некорректные данные");
//                        System.exit(0);
//                    }
//                    if (i != 0 && (mas[i] == '(' || mas[i] == ')') && (mas[i - 1] == ')'
//                            || mas[i - 1] == '(')) {
//                        System.out.println("Некорректные данные");
//                        System.exit(0);
//                    }
//                }
//            }
//        }
//    }
//
//    static boolean Proov(String str){
//        if(str.compareTo("+") == 0 || str.compareTo("-") == 0 || str.compareTo("*") == 0 || str.compareTo("/") == 0 || str.compareTo("(") == 0 || str.compareTo(")") == 0){
//            return false;
//        }
//        else{
//            return true;
//        }
//    }
//
//    static void Push (Stack st, String str){
//        st.push(str);
//    }
//
//    static double PopNumbers(Stack numbers){
//        String s = new String();
//        s = (String) numbers.pop();
//        double sum = Double.parseDouble(s);
//        return sum;
//    }
//
//    static String PopElements(Stack elements){
//        String x = (String)elements.pop();
//        return x;
//    }
//
//    static String Swt(double x1, double x2, String str){
//        double res = 0;
//
//        switch (str){
//            case("*"):
//                res = x1 * x2;
//                break;
//
//            case ("+"):
//                res = x1 + x2;
//                break;
//
//            case ("-"):
//                res = x2 - x1;
//                break;
//            case ("/"):
//                res = x2 / x1;
//                if(x1 == 0){
//                    System.out.println("Деление на ноль");
//                    System.exit(0);
//                }
//                break;
//        }
//
//        String s = String.valueOf(res);
//
//        return s;
//    }
//
//    static void Func(Stack numbers, Stack elements){
//        while(!elements.empty()){
//            double x1 = PopNumbers(numbers);
//            double x2 = PopNumbers(numbers);
//            String str = PopElements(elements);
//            String s = Swt(x1, x2, str);
//            Push(numbers, s);
//        }
//    }
//
//    static void Skb(Stack numbers, Stack elements, String tok){
//        String str = PopElements(elements);
//        do {
//            double x1 = PopNumbers(numbers);
//            double x2 = PopNumbers(numbers);
//            String s = Swt(x1, x2, str);
//            Push(numbers, s);
//            str = PopElements(elements);
//        }
//        while(str.compareTo("(") != 0);
//    }
//
//    public static void main(String[] args) {
//
//        Scanner in = new Scanner(System.in);
//        System.out.println("Введите выражение: ");
//        String str = in.nextLine();
//
//        StringTokenizer tokenizer = new StringTokenizer(str, "*/()+-", true);
//
//        Stack numbers = new Stack();
//        Stack elements = new Stack();
//        boolean exit = true;
//
//        char[] Line = str.toCharArray();
//        Checking(Line, str);
//
//        while(tokenizer.hasMoreTokens()){
//            String tok = tokenizer.nextToken();
//            boolean flag = Proov(tok);
//            if(flag){
//                Push(numbers, tok);
//            }
//            else{
//                if(tok.compareTo("*") == 0 || tok.compareTo("/") == 0 || tok.compareTo("(") == 0){
//                    if(tok.compareTo("(") == 0){
//                        exit = false;
//                    }
//                    Push(elements, tok);
//                }
//                else{
//                    if(elements.empty()){
//                        Push(elements, tok);
//                    }
//                    else{
//                        if((tok.compareTo("+") == 0 || tok.compareTo("-") == 0) && exit == true){
//                            Func(numbers, elements);
//                            Push(elements, tok);
//                        }
//                        else{
//                            if(tok.compareTo(")") == 0) {
//                                Skb(numbers, elements, tok);
//                                exit = true;
//                            }
//                            else{
//                                Push(elements, tok);
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        Func(numbers, elements);
//        System.out.println("Результат: " + PopNumbers(numbers));
//    }
//}

//вариант 16 #2
// * содержимое стандартного входного потока скопировать в выходной, преобразуя строки входного файла следующим образом:
// * каждая входная строка состоит из слов, разделенных одним или несколькими пробелами.
// * Переставить в ней слова, состоящие только из букв так, чтобы они были упорядочены по алфавиту.
// * При этом другие слова должны оставаться на месте, количество пробелов должно оставаться таким же, как и в исходной строке.

import java.util.*;

public class task_16{
    static ArrayList<String> linesList = new ArrayList<String>();

    static class Word implements Comparable<Word>{
        protected String value;
        protected int begin, end;

        public Word(String s, int b){
            value = s;
            begin = b;
            end = b + s.length() - 1;
        }

        public static boolean isWord(String s){
            for(int i = 0; i < s.length(); i++)
                if(!Character.isLetter(s.charAt(i)))
                    return false;
            return true;
        }


        @Override
        public int compareTo(Word o) {
            return value.compareTo(o.value);
        }
    }

    static void processLine(String s){
        StringBuilder sb = new StringBuilder(s);
        ArrayList<Word> wordsBefore = new ArrayList<Word>();
        ArrayList<Word> wordsAfter = new ArrayList<Word>();
        StringTokenizer st = new StringTokenizer(s);
        int position = 0;
        while(st.hasMoreElements()){
            String word = st.nextToken();
            position = s.indexOf(word, position);
            if (Word.isWord(word)) {
                wordsAfter.add(new Word(word, position));
                wordsBefore.add(new Word(word, position));
            }
        }
        Collections.sort(wordsAfter);
        for(int i = wordsAfter.size() - 1; i >= 0; i--)
            sb.replace(wordsBefore.get(i).begin, wordsBefore.get(i).end + 1, wordsAfter.get(i).value);
        linesList.add(sb.toString());
    }

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter data: ");
        String l;
        while(scan.hasNextLine() && !(l = scan.nextLine()).equals(""))
            processLine(l);
        System.out.println("Edited data: ");
        for(String line:linesList)
            System.out.println(line);
    }
}