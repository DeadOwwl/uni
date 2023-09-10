
import java.util.*;

public class proritet {
    public static void main(String[] args) {
        HashMap<String, Integer> myMap = new HashMap<String, Integer>();
        myMap.put("+", 0);
        myMap.put("*", 1);
        myMap.put("&", 2);
        myMap.put("^", 3);
        myMap.put("~", 4);
        myMap.put("%", 5);
        myMap.put("«", 6);
        myMap.put("/", 7);
        myMap.put("!", 8);
        myMap.put("»>", 9);
        ArrayList<String> myArray = new ArrayList<String>();
        String str = "23423 + 324 * 3244 & 42343 * 32423 ^ 6 ~ 12345 % 56 « 987 / 23 ! 1230 »> 88";
        Set<String> myArrayOfRazdeliteli = myMap.keySet();
        for (String i : myArrayOfRazdeliteli) {
            for (int j = 0; j < new StringTokenizer(str, i).countTokens() - 1; ++j) {
                myArray.add(i);
            }
        }
        for (int i = 0; i < myArray.size(); ++i) {
            for (int j = 0; j < myArray.size(); ++j) {
                if (myMap.get(myArray.get(i)) > myMap.get(myArray.get(j))) {
                    String buf = myArray.get(i);
                    myArray.set(i, myArray.get(j));
                    myArray.set(j, buf);
                }
            }
        }
        String str2 = "";
        StringTokenizer st = new StringTokenizer(str, "+*&^~%«/!»>");
        int j = 0;
        while (st.hasMoreTokens()) {
            String w = st.nextToken();
            str2 += w;
            if (myArray.size() > j) {
                str2 += myArray.get(j).toString();
                ++j;
            }
        }
        System.out.println(str2);
    }

}

//import java.util.Scanner;
//
//
//public class prioritet {
//
//	public static void main(String[] args) {
//		// TODO Auto-generated method stub
//
//		Scanner in=new Scanner(System.in);
//		String result="";
//		String s="";
//
//		int p=0,m=0,u=0,d=0;
//
//		while(in.hasNext())
//		{
//
//			if((s=in.nextLine()).equalsIgnoreCase("EXIT"))
//				break;
//			char[] str = s.toCharArray();
//			for(int i=0;i<str.length;i++)
//			{
//				if(1== ChekZnak(str[i]))
//					u++;
//				if(2== ChekZnak(str[i]))
//					d++;
//				if(3== ChekZnak(str[i]))
//					p++;
//				if(4== ChekZnak(str[i]))
//					m++;
//			}
//			for(int i=0;i<str.length;i++)
//			{
//				if('-'== (str[i])||'+'== (str[i])||'*'== (str[i])||'/'== (str[i])){
//				if(u!=0){
//					str[i]='*';
//					 u--;
//					 continue;
//				}
//				if(d!=0){
//					str[i]='/';
//					 d--;
//					 continue;
//				}
//				if(p!=0){
//					str[i]='+';
//					 p--;
//					 continue;
//				}
//				if(m!=0){
//					str[i]='-';
//					 m--;
//					 continue;
//				}
//
//				}
//			}
//			System.out.println(new String(str));
//
//		}
//		System.out.println(result);
//	}
//
//	private static int ChekZnak(char i)
//	{
//		if(i=='*')
//			return 1;
//		if(i=='/')
//			return 2;
//		if(i=='+')
//			return 3;
//		if(i=='-')
//			return 4;
//		return 0;
//
//	}
//
//}