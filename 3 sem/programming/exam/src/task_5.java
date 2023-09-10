
//Вариант 5
//найти длинные числа, отсортировать и вывести с номерами строк, в которых они встречались

import java.util.*;

public class task_5 {
    public static class Word {
        private int pos;
        private String word;

        protected Word(String _word,int _pos){
            pos = _pos;
            word = _word;
        }
        public String toString(){
            return new String(word+"("+pos+")");
        }
    }
    public static class WLongInt extends Word implements Comparable<WLongInt>,Comparator<Long>{
        protected long value;

        protected WLongInt(String _word,int _pos,long _value){
            super(_word,_pos);
            value = _value;
        }

        public int compareTo(WLongInt wli){
            return Long.compare(value, wli.value);
        }

        public int compare(Long arg0, Long arg1) {
            return (int)(arg0 - arg1);
        }

        public static WLongInt parseLong(String _word,int _pos){
            try{
                long _value;
                if(_word.charAt(_word.length()-1) == 'l' ||
                        _word.charAt(_word.length()-1) == 'L')
                    _value = Long.parseLong(_word.substring(0, _word.length()-1));
                else
                    _value = Long.parseLong(_word);
                return new WLongInt(_word,_pos,_value);
            }catch(Exception ignored){}
            return null;
        }
    }

    static void procLine(String line,int pos){
        StringTokenizer st = new StringTokenizer(line," \n\t");
        while(st.hasMoreTokens()){
            String word = new String(st.nextToken());
            WLongInt obj = WLongInt.parseLong(word,pos);
            if(obj != null){
                li.add(obj);
            }
        }
    }
    static List<WLongInt> li = new Vector<WLongInt>();

    public static void main(String[] args){

        Scanner sc = new Scanner(System.in);
        System.out.println("Insert your text line by line:");
        int n=0;
        while(sc.hasNextLine()){
            procLine(sc.nextLine(),n++);
        }
        sc.close();
        li.sort(null);
        System.out.println("---All long nums---: ");
        for(WLongInt i:li)
            System.out.print(i);
        System.out.println("---End---: ");
    }
}

