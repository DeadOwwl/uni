package task_7;

import java.util.ArrayList;
import java.util.Scanner;
import java.util.StringTokenizer;

public class task_7 {
	/* Из входного потока прочитать слова.
	 * Те которые только из цифр преобразовать в 16-ю запись и вывести 1 слово/строку
	 */

	static ArrayList<String> hexs = new ArrayList<String>();
	
	static void processLine (String line) {
		
		StringTokenizer sttok = new StringTokenizer(line);
		while (sttok.hasMoreTokens()) {
			String word = sttok.nextToken();
			if ( word.matches("[0-9]+") ) {
				try {
					String hex = Integer.toHexString(Integer.parseInt(word));
					hexs.add(word + ": " + hex);
				}
				catch (Exception e) {
					hexs.add(word + " can't be converted.");
				}
			}
		}
	}
	
	public static void main(String[] args) {
		
		System.out.println("Enter text or Ctrl+Z:");
		Scanner in = new Scanner(System.in);
		String line = " ";
		while (in.hasNextLine() && !(line = in.nextLine()).equals("")) {
			processLine(line);
		}
		in.close();
		System.out.println("Hexs:" + ((hexs.size() == 0)?" ...":""));
		for (String word: hexs)
			System.out.println(word);
		System.out.println("the end.");
		
	}

}
