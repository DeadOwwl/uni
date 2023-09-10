package task_9;


import java.util.ArrayList;
import java.util.Scanner;
import java.util.StringTokenizer;

/* ������� 9
 * �� ������������ �������� ������ ����������� ������.
 * � ������ ������ ���������� ����������� ����� � �������� �������.
 * ������� ���� ����� � ����������� �������� �����
 * ���-�� �������� ����� ������� ���������?????
 */
// ��� �� ������ �������, ������� ���������� �����((
class Word {
	String str;
	int begPos, endPos;
	public Word (String str, int begPos) {
		this.str = str;
		this.begPos = begPos;
		this.endPos = begPos + str.length() - 1;
	}
}

public class task_9 {

	static ArrayList<String> lines = new ArrayList<String>();
	
	static String getReverseLine (String line) {
		StringBuffer res = new StringBuffer(line);
		ArrayList<Word> list = new ArrayList<Word>();
		ArrayList<String> rList = new ArrayList<String>();
		StringTokenizer sttok = new StringTokenizer(line);
		int pos = 0;
		while (sttok.hasMoreElements()) {
			String token = sttok.nextToken();
			pos = line.indexOf(token, pos);
			list.add(new Word(token, pos));
			rList.add(token);
			pos += token.length();
		}
		for (int i = list.size() - 1; i >= 0; --i)
			res.replace(list.get(i).begPos, list.get(i).endPos + 1, rList.get(list.size() - 1 - i));
		return res.toString();
	}
	
	public static void main(String[] args) {
		
		System.out.println("������� �����, ��� ��������� ����������� Ctrl+Z:");
		Scanner in = new Scanner(System.in);
		String line = " ";
		while (in.hasNextLine() && !(line = in.nextLine()).equals("")) {
			lines.add(getReverseLine(line));
		}
		in.close();
		System.out.println("�����:");
		for (String item: lines)
			System.out.println(item);
		if ( lines.size() == 0 )
			System.err.println("������ ���...");
		System.out.println("��������� ��������� �������.");
		
	}

}