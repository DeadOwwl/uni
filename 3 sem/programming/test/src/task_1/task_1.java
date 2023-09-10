package task_1;

import java.util.ArrayList;
import java.util.Scanner;

public class task_1 {
	//¬ариант 1.
	//»з стандартного входного потока прочитать текст
	//и в стандартный выходной поток вывести все цитаты.
	//÷итата Ч это текст между двойными кавычками
	
	static ArrayList<String> ql = new ArrayList<String>(); //quotes list
	
	static void procLine(String line){
		
		int begq = line.indexOf('"');
		int endq = line.indexOf('"',begq+1);
		
		while(endq != -1){
			
			ql.add(line.substring(begq+1, endq));
			line = line.substring(0, begq) + line.substring(endq+1, line.length());
			
			begq = line.indexOf('"',begq);
			endq = line.indexOf('"',begq+1);
		}
	}
	public static void main(String[] args){
		
		Scanner sc = new Scanner(System.in);
		
		System.out.println("Insert your text with quotes by line:");
		while(sc.hasNextLine()){
			procLine(sc.nextLine());
		}
		sc.close();
		
		System.out.println("All quotes: ");
		for(String s : ql){
			System.out.println(s);
		}
		System.out.println("----end----\n");
	}
}
