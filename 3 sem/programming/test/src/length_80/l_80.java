package length_80;

import java.util.*;
public class l_80 {
    @SuppressWarnings("resource")
	public static void main(String[] args) {
        String text = "";
        Scanner in = new Scanner(System.in);
        Character[] signs = {'.', ',', '!', '?'};
        List<String> StrList = new ArrayList<String>();
        while (in.hasNextLine()) {
            String buffer = in.nextLine();
            if (buffer.equals("exit"))
                break;
            text += buffer;
        }
        StringTokenizer str = new StringTokenizer(text, " \t", true);
        while (str.hasMoreTokens()) {
            String tok = str.nextToken();
            if(tok.equals("\t"))
                StrList.add(" ");
            else
                StrList.add(tok);
        }
        int amount = StrList.size();
        for (int i = 0; i < amount; i++) {
            String ch = StrList.get(i);
            if (i != amount - 1 && i != 0)
                if (ch.equals(" ") && StrList.get(i + 1).equals(" ")) {
                    StrList.remove(i + 1);
                    amount--;
                    i--;
                }
        }
        for (int i = 0; i < amount; i++)
            if (StrList.get(i).equals(" ") && i!=amount-1) {
            boolean flag = false;
            for (int k = 0; k < signs.length; k++)
                if (StrList.get(i+1).charAt(0) == signs[k]) {
                    flag = true;
                }
            if (flag) {
                StrList.remove(i);
                amount--;
                i--;
            }
        }
        String buffer="";
        int text_size = StrList.size();
        for(int i = 0 ; i < text_size; i++){
            if((buffer.length()+StrList.get(i).length())<=80) {
                buffer += StrList.get(i);
                if(buffer.charAt(0)==' ')
                    buffer = buffer.substring(1);
                if(i==text_size-1)
                    System.out.println(buffer);
            }
            else
            {
                if(buffer.charAt(buffer.length()-1)==' ')
                    buffer = buffer.substring(0, buffer.length()-2);
                System.out.println(buffer);
                buffer="";
                buffer+=StrList.get(i);
            }

        }
    }
}