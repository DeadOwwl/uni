import java.util.*;

public class numbs8_10_16 {

    static class Word {
        protected String word;
        protected int line;
        protected Word (String word, int line) {
            assert(word!=null);
            this.word = word;
            this.line = line;
        }
        public String toString() {
            return new String(word + "(" + line + ")");
        }
        static boolean isSigned (String word) {
            return (word.charAt(0)=='-'||word.charAt(0)=='+');
        }
        static boolean isOctal(String word) {
            final String octals = "01234567";
            String w = isSigned(word)?word.substring(1):word;
            if(w.charAt(0)!='0') {
                return false;
            }
            for(int i = 1;i<w.length();i++)
                if(octals.indexOf(w.charAt(i))==-1) {
                    return false;
                }
            return true;
        }

    }

    static class MyInt extends Word implements Comparable<MyInt>{
        int val;
        public MyInt(String word, int line, int v) {
            super(word, line);
            val = v;
        }
        public int compareTo(MyInt p) {
            return Integer.compare(p.val, val);
        }
        static MyInt parseDec(String w, int ln) {
            try {
                int x = Integer.parseInt(w);
                return new MyInt(w, ln, x);
            }
            catch(Exception ignored) {}
            return null;
        }
        static MyInt parseHex(String w, int ln) {
            String word = (w.charAt(0)=='0'&& Character.toLowerCase(w.charAt(1))=='x')?w.substring(2):w;
            try {
                int x = Integer.parseInt(word, 16);
                return new MyInt(w,ln,x);
            }
            catch(Exception ignored) {} return null;
        }

        public void print() {
            System.out.print(word+"("+line+")"+ "   ");
        }
    }

    static class MyDbl extends Word implements Comparable<MyDbl>{
        double val;
        boolean exp;
        public MyDbl(String word, int line, double v) {
            super(word,line);
            val = v;
            exp = (word.indexOf('e')>0 || word.indexOf('E')>0);
        }
        public boolean isExp() {
            return exp;
        }
        public int compareTo(MyDbl p) {
            return Double.compare(val, p.val);
        }
        static MyDbl parse(String w, int ln) {
            try {
                double x = Double.parseDouble(w);
                return new MyDbl(w, ln, x);
            }
            catch(Exception ignored) {}
            return null;
        }

        public static boolean isFloat(String word) {
            return word.contains("f") || word.contains("F");
        }

        public void print() {
            System.out.print(word+"("+line+")"+ "   ");
        }

    }

    static class MyWord extends Word implements Comparable<MyWord>{
        public MyWord(String word, int line) {
            super(word, line);
        }
        public int compareTo(MyWord p) {
            return p.word.compareTo(this.word);
        }

        public void print() {
            System.out.print(word+"("+line+")"+ "   ");
        }
    }

    static List <MyInt> di = new Vector<MyInt>();
    static List <MyInt> hi = new Vector<MyInt>();
    static List <MyDbl> df = new Vector<MyDbl>();
    static List <MyDbl> de = new Vector<MyDbl>();
    static List <MyWord> wd = new Vector<MyWord>();

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int ln = 0;
        System.out.println("Input strings");
        while(in.hasNextLine()) {
            String s = in.nextLine();
            if(s.equals("")) break;
            procLine(s,ln);
            ln++;
        }
        di.sort(null);
        hi.sort(null);
        df.sort(null);
        de.sort(null);
        wd.sort(null);
        in.close();
        printRes();
    }
    private static void printRes() {
        // TODO Auto-generated method stub
        System.out.println("целые числа в десятичном виде:");
        for (MyInt anInt : di) anInt.print();
        System.out.println("\nцелые числа в шестнадцатиричном виде:");
        for (MyInt myInt : hi) myInt.print();
        System.out.println("\nдействительные числа с плавающей точкой:");
        for (MyDbl dbl : df) dbl.print();
        System.out.println("\nдействительные числа в экспоненциальной форме:");
        for (MyDbl myDbl : de) myDbl.print();
        System.out.println("\nтекст:");
        for (MyWord myWord : wd) myWord.print();
        System.out.println();

    }
    static void procLine(String s, int n) {
        StringTokenizer st = new StringTokenizer(s,"\r\n ");
        while(st.hasMoreTokens()) {
            String w = st.nextToken();
            if( Word.isOctal(w)) {
                wd.add(new MyWord(w,n));
                continue;
            }
            if (MyInt.parseDec(w, n)!=null)
            {
                di.add(new MyInt(w,n,Integer.parseInt(w)));
                continue;
            }
            if (MyInt.parseHex(w, n)!=null)
            {
                hi.add(new MyInt(w,n,Integer.parseInt(w.substring(2), 16)));
                continue;
            }
            if (MyDbl.parse(w, n)!=null) {
                if (w.contains("f") || w.contains("F")) {
                    wd.add(new MyWord(w,n));
                    continue;
                }
                MyDbl md=new MyDbl(w,n, Double.parseDouble(w));
                if (md.isExp())
                    de.add(md);
                else
                    df.add(md);
                continue;
            }
            wd.add(new MyWord(w,n));
        }
    }

}
