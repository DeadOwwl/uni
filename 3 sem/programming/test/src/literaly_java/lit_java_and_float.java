package literaly_java;


import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;
import java.util.StringTokenizer;

/* Вариант 25
 * прочитать все данные с входного потока, разделить на слов,
 * выделить лексемы Java,представляющие собой дробные числа(float) со знаком.
 * Хранить эти значения с номерами входных строк. Вывести, предварительно отсортировав в порядке убывания значений.
 */

class MyFloat implements Comparable <MyFloat> {
	String str;
	int lineNumber;
	public MyFloat (String str, int lineNumber) {
		this.str = str;
		this.lineNumber = lineNumber;
	}
	public int compareTo (MyFloat mf) {
		double d1 = Double.parseDouble(str);
		double d2 = Double.parseDouble(mf.str);
		return (d1 > d2) ? -1 : (d1 == d2) ? 0 : 1;
	}
	public static boolean isFloat (String str) {
		if ( !("" + str.charAt(str.length() - 1)).matches("[fF]") )
			return false;
		try {
			Float.parseFloat(str);
			return true;
		}
		catch (Exception e) {
			return false;
		}
	}
	public String toString () {
		return str + " in " + lineNumber + " line.";
	}
}

public class lit_java_and_float {

	static ArrayList<MyFloat> floats = new ArrayList<MyFloat>();
	
	static void processLine (String line, int lineNumber) {
		StringTokenizer sttok = new StringTokenizer(line);
		while (sttok.hasMoreTokens()) {
			String word = sttok.nextToken();
			if ( MyFloat.isFloat(word) ) {
				floats.add(new MyFloat(word, lineNumber));
			}
		}
	}
	
	public static void main(String[] args) {
		
		System.out.println("Enter text or Ctrl+Z:");
		Scanner in = new Scanner(System.in);
		int lineNumber = 1;
		while (in.hasNextLine()) {
			String line = in.nextLine();
			processLine(line, lineNumber++);
		}
		in.close();
		System.out.println("floats:" + ((floats.size() == 0)?" ...":""));
		Collections.sort(floats);
		for (MyFloat fl: floats)
			System.out.println(fl);
		System.out.println("the end.");
		
	}

}