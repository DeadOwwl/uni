package task_3;

import java.util.ArrayList;
import java.util.Scanner;

public class task_3 {
	//¬ариант 3
	//—оздать программу, котоа€ читает текст из стандартного входного потока,
	//разбивает его на предложени€ и выводит их в стандартный поток по одному 
	//предложению в строке, перевод€ все слова ¬осклицательных предложений
	//в верхний регистр.
	
	static ArrayList<String> tl = new ArrayList<String>(); //list of lines
	
	static void procLine(String line){
		
		int idx = 0;
		while(idx<line.length()){
			
			if(line.charAt(idx) == '.' || line.charAt(idx) == '?'){
				
				tl.add(line.substring(0, idx+1));
				line = line.substring(idx+1);
				idx = 0;
			}else
				if(line.charAt(idx) == '!'){

					tl.add(line.substring(0, idx+1).toUpperCase());
					line = line.substring(idx+1);
					idx = 0;
				}
			idx++;
		}
	}
	
	public static void main(String[] args){
		
		Scanner sc = new Scanner(System.in);
		
		System.out.println("Insert your text line by line:");
		String text = "";
		while(sc.hasNextLine()){
			text = text +sc.nextLine();
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