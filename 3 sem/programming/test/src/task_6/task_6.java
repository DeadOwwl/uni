package task_6;

import java.util.*;

public class task_6 {
	
	public static boolean check(String userNameString) {
		for (int i = 0; i < userNameString.length(); i++)
			if (Character.isDigit(userNameString.charAt(i)) == false)
					return false;
			return true;
	}
	
	
	public static void main (String args[]) {
		System.out.println("Введите данные.");
		Scanner in = new Scanner(System.in);
		ArrayList<String> List = new ArrayList<String>(); 
		String str = " ";
		while (in.hasNextLine() &&  !(str = in.nextLine()).equals("")) {
			StringTokenizer strtok = new StringTokenizer(str);
			
			while (strtok.hasMoreTokens()) {
				String word = strtok.nextToken();
				if (check(word) == true) List.add(word);
			}	
		}
		if (List.isEmpty() == true) System.out.println("Нет слов, состоящих из цифр!");
		else {
		for (String i: List)
			System.out.println(i);
		}
		in.close();
		System.exit(0);	
	}
}