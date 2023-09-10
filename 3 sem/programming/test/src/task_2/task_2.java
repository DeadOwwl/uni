package task_2;

import java.util.*;

public class task_2 {
	//¬ариант 2
	//ѕрограмма читает текст из стандартного входного потока, находит слова,
	//начинающиес€ с заглавной буквы и выводит в стандартный выходной поток
	//с новой строки

	static ArrayList<String> tl = new ArrayList<String>(); //list of lines
	
	static void procLine(String line)
	{
		StringTokenizer st = new StringTokenizer(line);
		int idx = 0;
		while(st.hasMoreElements())
		{
			String s = st.nextToken();
			if(Character.isUpperCase(s.charAt(idx)))
			{
				tl.add(s);
			}
		}
	}
	public static void main(String[] args){
		
		Scanner sc = new Scanner(System.in);
		
		System.out.println("Insert your text line by line:");
		String text = "";
		String str = "";
		while(sc.hasNextLine() && !(str = sc.nextLine()).equals("")){
			text = text + " " + str;
			procLine(text);
		}
		sc.close();

		System.out.println("---Full text---: ");
		for(String s : tl){
			System.out.println(s);
		}
		System.out.println("------end------\n");
	}
}
