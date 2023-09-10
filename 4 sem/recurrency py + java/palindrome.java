import javafx.util.Pair;

import java.io.*;

public class palindrome {

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("input.txt"));
        BufferedWriter out = new BufferedWriter(new FileWriter("output.txt"));
        String string = (in.readLine()).trim();

        int palindrome_length = 0;
        StringBuilder the_palindrome = new StringBuilder();
        int string_length = string.length();
        if (string_length == 1) {
            palindrome_length = 1;
            the_palindrome = new StringBuilder(string);
        }
        else if (string_length == 2) {
            if (string.charAt(0) == string.charAt(1)) {
                palindrome_length = 2;
                the_palindrome = new StringBuilder(string);
            }
            else {
                palindrome_length = 1;
                the_palindrome = new StringBuilder(Character.toString(string.charAt(0)));
            }
        }
        else {
            String reversed_string = (new StringBuffer(string)).reverse().toString();
            int[][] substring_length_matrix = new int[string_length + 1][string_length + 1];
            for (int i = 1; i < string_length + 1; i++) {
                for (int j = 1; j < string_length + 1; j++) {
                    if (string.charAt(i - 1) == reversed_string.charAt(j - 1))
                        substring_length_matrix[i][j] = substring_length_matrix[i - 1][j - 1] + 1;
                    else
                        substring_length_matrix[i][j] =
                                Math.max(substring_length_matrix[i - 1][j], substring_length_matrix[i][j - 1]);
                }
            }
            palindrome_length = substring_length_matrix[string_length][string_length];

            int i = string_length;
            int j = string_length;
            while (substring_length_matrix[i][j] > 0) {
                while (substring_length_matrix[i][j] == substring_length_matrix[i][j - 1]) {
                    j -= 1;
                }
                if (string.charAt(i - 1) == reversed_string.charAt(j - 1)) {
                    the_palindrome.append(string.charAt(i - 1));
                    j--;
                }
                i--;
            }
        }

        Pair<Integer, String> answers =
                new Pair<Integer, String>(palindrome_length,the_palindrome.toString());

        if (answers.getKey() != 0)
            out.write(Integer.toString(answers.getKey()) + '\n' + answers.getValue());
        else
            out.write(Integer.toString(answers.getKey()) + '\n');
        out.flush();
    }
}
