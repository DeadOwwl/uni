import java.io.*;
import java.util.*;

public class dashaEx {

    public static void main(String[]args){
        try {
            BufferedReader in1 = new BufferedReader(new FileReader("input1.txt"));
            BufferedReader in2 = new BufferedReader(new FileReader("input2.txt"));
            BufferedWriter out1 = new BufferedWriter(new FileWriter("out1.txt"));
            BufferedWriter out2 = new BufferedWriter(new FileWriter("out2.txt"));
            BufferedWriter out3 = new BufferedWriter(new FileWriter("out3.txt"));
            BufferedWriter out4 = new BufferedWriter(new FileWriter("out4.txt"));
            String line;

            //1
            ArrayList<String> linesList = new ArrayList<>();
            ArrayList<Character> delimitsList = new ArrayList<>();
            String text = "";
            while ((line = in1.readLine()) != null) {
                text += line;
                linesList.add(line);
                for (int i = 0; i < line.length(); i++) {
                    char a = line.charAt(i);
                    if ((!Character.isLetter(a)) && (!Character.isDigit(a))) {
                        boolean delimitWas = false;
                        if (delimitsList.size() == 0)
                            delimitsList.add(line.charAt(i));
                        else {
                            for (Character character : delimitsList) {
                                if (character.equals(a)) {
                                    delimitWas = true;
                                    break;
                                }
                            }
                            if (!delimitWas)
                                delimitsList.add(line.charAt(i));
                        }
                    }
                    }
                }
                Collections.sort(delimitsList);
                for (int i = delimitsList.size() - 1; i >= 0; i--) {
                    out1.write(delimitsList.get(i) );
                    out1.write('\n');
                    out1.flush();
                }
            System.out.println("Task 1 completed...");

            //3
            ArrayList<String> wList = new ArrayList<>();
            ArrayList<String> wordsList = new ArrayList<>();
            String delimits = "";
            while ((line = in2.readLine()) != null)
                delimits += line;
            delimits += ' ';
            StringTokenizer st = new StringTokenizer(text, delimits);
            while(st.hasMoreElements()){
                String word = st.nextToken();
                wordsList.add(word);
                boolean flag = false;
                for(int i = 0; i < word.length(); i++){
                    for (int j = i + 1; j < word.length(); j++){
                        if (word.charAt(i) == word.charAt(j)) {
                            flag = true;
                            break;
                        }
                    }
                    if (flag)
                        break;
                }
                if (!flag)
                    wList.add(word);
            }
            for (String s : wList) {
                out3.write(s);
                out3.write('\n');
                out3.flush();
            }
            System.out.println("Task 3 completed...");

            //4
            ArrayList<String> reversedList = new ArrayList<>();
            ArrayList<String> reversedLinesList = new ArrayList<>();
            String f;
            wordsList.clear();
            for(String li:linesList) {
                StringBuilder sb = new StringBuilder(li);
                StringTokenizer str = new StringTokenizer(li, delimits);
                while(str.hasMoreElements()){
                    String word = str.nextToken();
                    wordsList.add(word);
                }
                for (String w : wordsList) {
                    String wRev = "";
                    for (int i = w.length() - 1; i >= 0; i --)
                        wRev += w.charAt(i);
                    reversedList.add(wRev);
                }
                for(int i = wordsList.size() - 1; i >= 0; i--){
                    String w = wordsList.get(i);
                    String rw = reversedList.get(i);
                    int begin = li.indexOf(wordsList.get(i));
                    int end = begin + wordsList.get(i).length() - 1;
                    sb.replace(begin,end + 1, rw);
                }
                f = sb.toString();
                reversedLinesList.add(f);
                wordsList.clear();
            }
            for (String r : reversedLinesList) {
                out4.write(r);
                out4.write('\n');
                out4.flush();
            }
            System.out.println("Task 4 completed...");

            } catch(IOException fileNotFoundException){
                fileNotFoundException.printStackTrace();
            }



    }
}
