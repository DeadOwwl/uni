import java.util.*;


public class numbs_8 {

    public static void main(String[] args) {
        // TODO Auto-generated method stub

        Scanner in =new Scanner(System.in);

        ArrayList<Couple> I_8=new ArrayList <Couple>();
        int count=1;

        while(in.hasNext()){
            String b=in.nextLine();
            if(b.equals("exit"))
                break;
            StringTokenizer str = new StringTokenizer (b," ");
            while(str.hasMoreTokens())
            {
                String c=str.nextToken();
                if(c.startsWith("0"))
                {
                    try{
                        Integer.parseInt(c,8);
                        I_8.add( new Couple(count,Integer.parseInt(c,8)) );
                    }
                    catch(Exception e)
                    {
                        continue;
                    }
                }
            }
            count++;
        }

        Collections.sort(I_8, new Comparator <Couple> () {
            public int compare(Couple o1, Couple o2) {
                if(o1.int_8 < o2.int_8)
                    return 1;
                return  -1;
            }
        });



        for(Couple i:I_8)
        {
            System.out.println(i);
        }


    }

}
class Couple{
    int int_8;
    int number_str;

    public int getInt_8(){return int_8;}

    Couple(int a,int b){
        int_8=b;
        number_str=a;
    }


    public String toString(){return int_8+ "  "+number_str;}
}