package prioritet;

import java.util.Scanner;


public class prioritet {

	@SuppressWarnings("resource")
	public static void main(String[] args) {

		Scanner in=new Scanner(System.in);
		String result="";
		String s="";
		
		int p=0,m=0,u=0,d=0;
		String line = "";
		while(in.hasNext() && !(line = in.nextLine()).equals(""))
		{
			if((s = line).equalsIgnoreCase("EXIT"))
				break;
			char[] str = s.toCharArray();
			for(int i=0;i<str.length;i++)
			{
				if(1== ChekZnak(str[i]))
					u++;
				if(2== ChekZnak(str[i]))
					d++;
				if(3== ChekZnak(str[i]))
					p++;
				if(4== ChekZnak(str[i]))
					m++;
			}
			for(int i=0;i<str.length;i++)
			{
				if('-'== (str[i])||'+'== (str[i])||'*'== (str[i])||'/'== (str[i])){
				if(u!=0){
					str[i]='*';
					 u--;
					 continue;
				}
				if(d!=0){
					str[i]='/';
					 d--;
					 continue;
				}
				if(p!=0){
					str[i]='+';
					 p--;
					 continue;
				}
				if(m!=0){
					str[i]='-';
					 m--;
					 continue;
				}
				
				}
			}
			System.out.println(new String(str));
			
		}
		System.out.println(result);
	}
	
	private static int ChekZnak(char i)
	{
		if(i=='*')
			return 1;
		if(i=='/')
			return 2;
		if(i=='+')
			return 3;
		if(i=='-')
			return 4;
		return 0;
		
	}

}