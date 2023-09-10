
import java.util.*;

public class row {

    static class Sequence implements Comparable<Sequence> {
        int line;
        double M=0;
        double D=0;
        double S=0;
        double C=0;
        ArrayList<Double> arr;
        ArrayList<String> arrStr;
        public Sequence(ArrayList<Double> a,ArrayList<String> s , int l) {
            arr = new ArrayList<Double>();
            arrStr=new ArrayList<String>();
            arr.addAll(a);
            for (int i=0; i<a.size(); i++)
                arrStr.add(s.get(i));
            line=l;
            if (arr.size()!=0) {
                for (Double aDouble : arr) M += aDouble;
                M/=arr.size();
            }
            if (arr.size()>1) {
                for (Double aDouble : arr) D += ((aDouble - M) * (aDouble - M));
                D/=(arr.size()-1);
            }
            S=Math.sqrt(D);
            if (M!=0)
                C=(S/M)*100;
        }
        @Override
        public int compareTo(Sequence o) {
            // TODO Auto-generated method stub
            return Double.compare(C, o.C);
        }

        public String toString() {
            String str="#"+line+ " M="+ M+" D="+D+" C="+C+" Sequence: ";
            for (String s : arrStr) str += s + " ";
            return str;
        }

    }

    static ArrayList<Double> arrList=new ArrayList<Double>();
    static ArrayList<String> strList=new ArrayList<String>();
    static ArrayList<Sequence> seqList=new ArrayList<Sequence>();
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int ln = 0;
        System.out.println("Input strings");
        while(in.hasNextLine()) {
            String s = in.nextLine();
            if(s.equals(""))
                break;
            arrList.clear();
            strList.clear();
            if (ProcLine(s))
                seqList.add(new Sequence(arrList,strList, ln));
            ln++;
        }
        Collections.sort(seqList);
        for (Sequence s:seqList)
            System.out.println(s);
        in.close();
    }


    static boolean ProcLine(String str)
    {
        StringTokenizer st = new StringTokenizer(str,"\r\n ");
        while(st.hasMoreTokens()) {
            String token = st.nextToken();
            int num = 0;
            double dnum=0;
            try {
                if(token.charAt(0) == '0' &&  Character.toLowerCase(token.charAt(1))=='x')
                    num = Integer.parseInt(token.substring(2), 16);
                else throw new Exception();
            }
            catch (Exception e) {
                try {
                    if(token.charAt(0) != '0') throw new Exception();
                    num = Integer.parseInt(token.substring(1), 8);
                }
                catch (Exception e1) {
                    try {
                        num = Integer.parseInt(token);
                    }
                    catch (Exception e2) {
                        try {
                            dnum = Double.parseDouble(token);
                        }
                        catch (Exception e3) {
                            return false;
                        }
                        arrList.add(dnum);
                        strList.add(token);
                        continue;
                    }
                }
            }
            arrList.add((double)num);
            strList.add(token);
        }
        return true;
    }
}


