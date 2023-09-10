package task_13;

import java.util.ArrayList;
import java.util.Scanner;

/* ¬ариант 13
 * заменить в строке 8 пробелов сто€щих подр€д на символ табул€ции */

public class task_13 {

	static ArrayList<String> list = new ArrayList<String>();
	
	public static void main(String[] args) {
		
		System.out.println("start:");
		Scanner in = new Scanner(System.in);
		String line =  "";
		while (in.hasNextLine() && !(line = in.nextLine()).equals("")) {
			StringBuilder res = new StringBuilder(line);
			String spaces = "        ";
			int pos = res.indexOf(spaces);
			while ( pos != -1 ) {
				res.replace(pos, pos + 8, "\t");
				pos = res.indexOf(spaces);
			}
			list.add(res.toString());
		}
		in.close();
		System.out.println("Text:");
		if ( list.size() == 0 )
			System.out.println("...");
		for (String l: list)
			System.out.println(l);
	}

}