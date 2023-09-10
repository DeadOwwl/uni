import java.io.*;
import java.util.*;

public class alinaEx {

    static class Word implements Comparable<Word>{
        String value;

        public Word(String s){
            value = s;
        }

        public int compareTo(Word o) {
            return Integer.compare(o.value.length(), value.length());
        }
    }

    public static void main(String[]args){

        try {
            BufferedReader in1 = new BufferedReader(new FileReader("input1.txt"));
            BufferedReader in2 = new BufferedReader(new FileReader("input2.txt"));
            BufferedReader in3 = new BufferedReader(new FileReader("input3.txt"));
            BufferedWriter out1 = new BufferedWriter(new FileWriter("output1.txt"));
            BufferedWriter out2 = new BufferedWriter(new FileWriter("output2.txt"));
            BufferedWriter out3 = new BufferedWriter(new FileWriter("output3.txt"));
            BufferedWriter out4 = new BufferedWriter(new FileWriter("output4.txt"));
            String line;

            ArrayList<Word> obWordsList = new ArrayList<>();
            ArrayList<String> pWordsList = new ArrayList<>();
            ArrayList<String> rWordsList = new ArrayList<>();

            ArrayList<String> firstFileWordsList = new ArrayList<>();
            ArrayList<String> secondFileWordsList = new ArrayList<>();

            String delimits = "";
            while ((line = in3.readLine()) != null)
                delimits += line;

            while ((line = in1.readLine()) != null) {
                StringTokenizer st = new StringTokenizer(line, delimits);
                while(st.hasMoreElements()){
                    String word = st.nextToken();
                    firstFileWordsList.add(word);
                    obWordsList.add(new Word(word));
                }
            }
            while ((line = in2.readLine()) != null) {
                StringTokenizer st = new StringTokenizer(line, delimits);
                while(st.hasMoreElements()){
                    String word = st.nextToken();
                    secondFileWordsList.add(word);
                    obWordsList.add(new Word(word));
                }
            }
            Collections.sort(obWordsList);
            for (Word value : obWordsList) {
                out1.write(value.value);
                out1.write('\n');
                out1.flush();
            }

            for(String firstWord:firstFileWordsList){
                for(String secondWord:secondFileWordsList){
                    if (firstWord.equals(secondWord)){
                        pWordsList.add(firstWord);
                        break;
                    }
                }
            }
            for (String value : pWordsList) {
                out2.write(value);
                out2.write('\n');
                out2.flush();
            }

            for(String firstWord:firstFileWordsList){
                boolean flag = false;
                for(String secondWord:secondFileWordsList){
                    if (firstWord.equals(secondWord)){
                        flag = true;
                        break;
                    }
                }
                if (!flag)
                    rWordsList.add(firstWord);
            }
            for (String value : rWordsList) {
                out3.write(value);
                out3.write('\n');
                out3.flush();
            }

        } catch(IOException fileNotFoundException){
            fileNotFoundException.printStackTrace();
        }
    }
}
