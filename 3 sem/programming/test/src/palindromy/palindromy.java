package palindromy;

import java.util.*;

/* ������� 11
 * �� ������������ �������� ������ ��������� ������ � ������������� ��������� �������:
 * ����� ������� ������ �� ����, ��� ��������� ������� �������������;
 * ����� ��� ����������, ������������� � �������� ������;
 * ��������� ����� �������� �� ������, ����������� ������ ���������� �� ������ � ���������� �������� ���������� �������
 */

class Palindrom implements Comparable<Palindrom> {
	String str;
	int oldBegPos, oldEndPos;
	public Palindrom (String str, int oldBegPos) {
		this.str = str;
		this.oldBegPos = oldBegPos;
		this.oldEndPos = oldBegPos + str.length() - 1;
	}
	public Palindrom (Palindrom p) {
		str = p.str;
		oldBegPos = p.oldBegPos;
		oldEndPos = p.oldEndPos;
	}
	public int compareTo (Palindrom p) {
		return str.compareTo(p.str);
	}
	public static boolean isPalindrom (String str) {
		String rev = "";
		for (int i = str.length() - 1; i >= 0; i--)
			rev = rev.concat("" + str.charAt(i));
		return rev.equals(str);		
	}
}

public class palindromy {

	static ArrayList<String> text = new ArrayList<String>();
	
	static String getDelim (String str) {
		String res = "";
		for (int i = 0; i < str.length(); ++i) {
			char ch = str.charAt(i);
			if ( !Character.isLetter(ch) )
				res = res.concat("" + ch);
		}
		return res;
	}
	
	static String processLine (String line) {
		StringBuilder res = new StringBuilder(line);
		ArrayList<Palindrom> list = new ArrayList<Palindrom>();
		ArrayList<Palindrom> sortlist = new ArrayList<Palindrom>();
		StringTokenizer sttok = new StringTokenizer(line, getDelim(line));
		int endPos = 0;
		while (sttok.hasMoreElements()) {
			String word = sttok.nextToken();
			endPos = line.indexOf(word, endPos);
			if ( Palindrom.isPalindrom(word) ) {
				Palindrom p = new Palindrom(word, endPos);
				list.add(p);
				sortlist.add(p);
			}
			endPos += word.length();
		}
		Collections.sort(sortlist);
		for (int i = sortlist.size() - 1; i >= 0; --i) {
			res.replace(list.get(i).oldBegPos, list.get(i).oldEndPos + 1, sortlist.get(i).str);
		}
		return res.toString();
	}
	
	public static void main(String[] args) {
		
		System.out.println("Enter text or Ctrl+Z:");
		Scanner in = new Scanner(System.in);
		String line = "";
		while (in.hasNextLine() && !(line = in.nextLine()).equals("")) {
			text.add(processLine(line));
		}
		in.close();
		System.out.println("\nText:");
		if ( text.size() == 0 )
			System.err.println("....");
		for (String l: text)
			System.out.println(l);
		System.out.println("The end.");
		
	}

}