package L2;
import java.util.Scanner;
public class L2 {
	
	public static void main( String[] args ) {
        Scanner in = new Scanner( System.in );
        int numVowels = 0, numConsonants = 0;
    	System.out.println("������� ������: ");
        while ( in.hasNextLine() ) 
        {
            String s = in.nextLine();
            s = s.toLowerCase();
            for ( int i = 0; i < s.length(); i++ ) {
                char c = s.charAt( i );
                if (c == '�' || c == '�' || c == '�' || 
                		c == '�' || c == '�' || c == '�' || 
                		c == '�' || c == '�' || c == '�' || c == '�')
                numVowels++;
                else
                	if (c == '�' || c == '�' || c == '�' || c == '�'
                			|| c == '�'|| c == '�'|| c == '�'|| c == '�'
                			|| c == '�'|| c == '�'|| c == '�'|| c == '�'
                			|| c == '�'|| c == '�'|| c == '�'|| c == '�'
                			|| c == '�'|| c == '�'|| c == '�'|| c == '�'
                			|| c == '�'|| c == '�'|| c == '�')
                		numConsonants++;
            }
            if (numVowels == 0 & numConsonants == 0)
            	System.out.println("������� ������� �� ����������.");
            else
                System.out.println("���������� ������� �� ��������� ������: " + numVowels + "\n���������� ��������� �� ��������� ������: " + numConsonants);
            numVowels = 0;
            numConsonants = 0;
        }
        in.close();
    }
}
