//Вариант 14.
//
//Ввести через стандартный поток текст,
//
//найти слово максимальной длины и вывести слово и сколько раз встречается

import java.util.*;

public class task_14 {

    static ArrayList<Word> wordsList = new ArrayList<Word>();

    static class Word implements Comparable<Word>{
        protected String value;
        protected int count;

        public Word(String v, int c){
            value = v;
            count = c;
        }

        @Override
        public int compareTo(Word o) {
            return Integer.compare(value.length(), o.value.length());
        }
    }

    static void processingLine(String s){
        StringTokenizer sTokenized = new StringTokenizer(s);
        while(sTokenized.hasMoreElements()){
            String word = sTokenized.nextToken();
            if(wordsList.size() == 0) {
                wordsList.add(new Word(word, 1));
                continue;
            }
            boolean flagUnique = true;
            for (Word wl : wordsList)
                flagUnique = !wl.value.equals(word);
            if (flagUnique)
                wordsList.add(new Word(word, 1));
            else {
                for (Word wl : wordsList)
                    if (wl.value.equals(word))
                        wl.count++;
            }
        }
    }

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter data: ");
        String l;
        while(scan.hasNextLine() && !(l = scan.nextLine()).equals(""))
            processingLine(l);
        Collections.sort(wordsList);
        System.out.println("The longest word: " + wordsList.get(wordsList.size() - 1).value +
                "\nFrequency: " + wordsList.get(wordsList.size() - 1).count);
    }
}
