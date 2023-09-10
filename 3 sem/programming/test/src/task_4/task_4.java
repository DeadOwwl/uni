package task_4;

import java.util.ArrayList;
import java.util.Scanner;

public class task_4 {
	//Вариант 4
	//Стандартный входной поток.
	//Найти все вопросительные предложения и вывести каждый с новой строки.

	static ArrayList<String> tl = new ArrayList<String>(); //list of lines
	static String tmpLine = new String();
	
	static void procLine(String line){
		
		int idx = 0;
		while(idx<line.length()){
			
			if(line.charAt(idx) == '.' || line.charAt(idx) == '!'){
				tmpLine = "";
				line = line.substring(idx+1);
				idx = 0;
			}else
				if(line.charAt(idx) == '?'){
					
					tmpLine += line.substring(0, idx+1);
					tl.add(tmpLine);
					tmpLine = "";
					
					line = line.substring(idx+1);
					idx = 0;
				}
			idx++;
		}
		if(line.indexOf('.') == -1 && line.indexOf('!') == -1 && line.indexOf('?') == -1){
			tmpLine += line;
		}
	}
	
	public static void main(String[] args){
		
		Scanner sc = new Scanner(System.in);
		
		System.out.println("Insert your text line by line:");

		tmpLine = "";
		while(sc.hasNextLine()){
			procLine(sc.nextLine());
		}
		if(!tmpLine.isEmpty())
			tl.add(tmpLine);
		sc.close();
		
		System.out.println("---Full text---: ");
		for(String s : tl){
			System.out.println(s);
		}
		System.out.println("------end------\n");
	}
}
