package loman;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class test {

	public static ArrayList<loman> lomanList=new ArrayList<loman>();
	
	public static void main(String[] args) {
		ArrayList<String> text=new ArrayList<String>();
		Scanner in=new Scanner(System.in);
		System.out.println("Enter coordinates or press Ctrl+Z to exit");
		String line = "";
		while(in.hasNextLine() && !(line = in.nextLine()).equals(""))
			text.add(line);
		in.close();
		System.out.println("entering stopped");
		for (int i=0; i<text.size(); i++)
			processLine(text.get(i), i);
		Collections.sort(lomanList);
		System.out.println("Sorted list of loman");
		if (lomanList.isEmpty())
			System.out.println("No loman");
		for (loman l:lomanList)
			System.out.println(l);
	}

	private static void processLine(String string, int i) {
		ArrayList<Double>x=new ArrayList<Double>();
		ArrayList<Double>y=new ArrayList<Double>();
		string= string.trim();
		boolean flag=true;
		int index1=0, index2=0, index3=0;
		while (string.length()!=0)
		{
			index1=string.indexOf('(');
			if (index1==-1) {
				flag=false;
				break;
			}
			index2=string.indexOf(')');
			if (index2==-1) {
				flag=false;
				break;
			}
			String coord=string.substring(index1+1, index2);
			index3=coord.indexOf(':');
			if (index3==-1) {
				flag=false;
				break;
			}
			try {
				String sX=coord.substring(0,index3);
				double cX=Double.parseDouble(sX);
				String sY=coord.substring(index3+1);
				double cY=Double.parseDouble(sY);
				x.add(cX);
				y.add(cY);
			}
			catch(Exception e){
				flag=false;
				break;
			}
			string=string.substring(index2+1);
		}
		if (flag==true)
			lomanList.add(new loman(x,y,i));
		}
		
	}


