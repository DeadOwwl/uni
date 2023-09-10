package testTaskGutos;

import java.util.*;

class Word {
	protected String word;
	protected int line;
	
	protected Word(String w, int l){
		//assert (word != null);
		this.word = w;
		this.line = l;
	}
	
	public String toSrting(){
		return new String(word + "(" + line + ")");
	}

	static boolean isSigned(String word){
		return (word.charAt(0) == '-' || word.charAt(0) == '+');
	}

	static boolean isOctal(String word){
		final String forOctal = "01234567";
		String w = isSigned(word) ? word.substring(1) : word;
		if (w.charAt(0) != '0')
			return false;
		for (int i = 1; i < w.length(); i++)
			if (forOctal.indexOf(w.charAt(i)) == -1)
				return false;
		return  true;
	}
}

class Int extends Word implements Comparable<Int>{
	int value;
	
	public Int(String w, int l, int v){
		super(w, l);
		value = v;
	}

	
	public int compareTo(Int o) {
		return (new Integer(o.value)).compareTo(new Integer(value));
	}

	static Int parseDec(String w, int l){
		try {
			int x = Integer.parseInt(w);
			return new Int(w, l, x);
		}
		catch (Exception e){
		}
		return null;
	}
	
	static Int parseHex(String w, int l){
		String word = (w.charAt(0) == '0' && Character.toLowerCase(w.charAt(1)) == 'x') ?
				w.substring(2) : w;
		try {
			int x = Integer.parseInt(word, 16);
			return new Int(w, l, x);
		} catch (Exception e){
		}
		return null;
	}
}

class Doub extends Word implements Comparable<Doub> {
	double value;
	boolean exp;
	
	public Doub(String w, int l, double v){
		super(w, l);
		value = v;
		exp = (word.indexOf('e') >0 || word.indexOf('E') > 0);
	}
	
	public boolean isExp(){
		return exp;
	}

	public int compareTo(Doub o){
		return (new Double(value)).compareTo(new Double(o.value));
	}

	static Doub parse(String w, int l) {
		try {
			double x = Double.parseDouble(w);
			return new Doub(w, l, x);
		}
		catch (Exception e){
		}
		return null;
	}
}

class mWord extends Word implements Comparable<mWord>{
	public mWord(String w, int l){
		super(w, l);
	}

	public int compareTo(mWord o){
		return o.word.compareTo(this.word);
	}
}

public class TestTaskGutos {
	static List<Int> dI = new Vector<Int>();
	static List<Int> hI = new Vector<Int>();
	static List<Doub> dF = new Vector<Doub>();
	static List<Doub> dE = new Vector<Doub>();
	static List<mWord> wD = new Vector<mWord>();
	
	public static void main(String args[]){
		Scanner in = new Scanner(System.in);
		int line = 0;
		String std = " ";
		while (in.hasNextLine()){
			std = in.nextLine();
			procLine(std, line);
			line++;
			printRes();
		}
		in.close();

	}
	
	static void procLine(String s, int n) {
		StringTokenizer st = new StringTokenizer(s, " \t\n");
		while(st.hasMoreTokens()){
			String w = st.nextToken();
			if (Word.isOctal(w)){
				wD.add(new mWord(w, n));
				continue;
			}
			Object b = Int.parseDec(w, n);
			if (b != null){
				dI.add((Int)b);
				continue;
			}
			b = Int.parseHex(w, n);
			if (b != null){
				hI.add((Int)b);
				continue;
			}
			b = Doub.parse(w, n);
			if (b!= null){
				if (((Doub)b).isExp())
					dE.add((Doub)b);
				else
					dF.add((Doub)b);
				continue;
			}
			wD.add(new mWord(w, n));
		}
	}

	static void printRes(){
		System.out.println("Decimal integers: ");
		Collections.sort(dI);
		for (Int di : dI)
			System.out.print(di.toSrting() + " ");
		System.out.println();
		System.out.println("Hexadecimal integers: ");
		Collections.sort(hI);
		for (Int hi : hI)
			System.out.print(hi.toSrting() + " ");
		System.out.println();
		System.out.println("Doubles: ");
		Collections.sort(dF);
		for (Doub df : dF)
			System.out.print(df.toSrting() + " ");
		System.out.println();
		System.out.println("Double in exponential format: ");
		Collections.sort(dE);
		for (Doub de : dE)
			System.out.print(de.toSrting() + " ");
		System.out.println();
		System.out.println("Text: ");
		Collections.sort(wD);
		for (mWord wd : wD)
			System.out.print(wd.toSrting() + " ");
		System.out.println();
		
	}
}