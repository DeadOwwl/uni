import java.util.*;


public class broken_line {
    static class loman implements Comparable<loman>{
        int line;
        double length;
        ArrayList<Double> xCoord;
        ArrayList<Double> yCoord;

        public loman(ArrayList<Double>x, ArrayList<Double> y, int l) {
            line=l;
            xCoord=new ArrayList<Double>();
            yCoord=new ArrayList<Double>();
            xCoord.addAll(x);
            yCoord.addAll(y);
            length=countLength(xCoord, yCoord);
        }

        private double countLength(ArrayList<Double> x, ArrayList<Double> y) {
            // TODO Auto-generated method stub
            double sum;
            double sqr;
            double l=0;
            for (int i=0;i<x.size()-1; i++) {
                sum=0;
                sum += ((y.get(i) - y.get(i + 1)) * (y.get(i) - y.get(i + 1)) + (x.get(i) - x.get(i + 1)) * (x.get(i) - x.get(i + 1)));
                sqr= Math.sqrt(sum);
                l+=sqr;
            }
            return l;
        }

        @Override
        public int compareTo(loman l) {
            // TODO Auto-generated method stub
            return Double.compare(l.length, length);
        }

        public String toString() {
            String str="";
            str+="#"+line+" ";
            for (int i=0; i<xCoord.size(); i++)
                str+="("+xCoord.get(i)+":"+yCoord.get(i)+") ";
            str+="length = "+length;
            return str;
        }
    }

    public static ArrayList<loman> lomanList=new ArrayList<loman>();

    public static void main(String[] args) {
        // TODO Auto-generated method stub
        ArrayList<String> text=new ArrayList<String>();
        Scanner in=new Scanner(System.in);
        System.out.println("Enter coordinates or press Ctrl+Z to exit");
        while(in.hasNextLine())
            text.add(in.nextLine());
        in.close();
        System.out.println("entering stopped");
        for (int i=0; i<text.size(); i++)
            processLine(text.get(i), i);
        Collections.sort(lomanList);
        System.out.println("Soted list of loman");
        if (lomanList.isEmpty())
            System.out.println("No loman");
        for (loman l:lomanList)
            System.out.println(l);
    }

    private static void processLine(String string, int i) {
        // TODO Auto-generated method stub
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


