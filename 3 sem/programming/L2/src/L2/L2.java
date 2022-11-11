package L2;
import java.util.Scanner;
public class L2 {
	
	public static void main( String[] args ) {
        Scanner in = new Scanner( System.in );
        int numVowels = 0, numConsonants = 0;
    	System.out.println("Введите строки: ");
        while ( in.hasNextLine() ) 
        {
            String s = in.nextLine();
            s = s.toLowerCase();
            for ( int i = 0; i < s.length(); i++ ) {
                char c = s.charAt( i );
                if (c == 'у' || c == 'е' || c == 'ы' || 
                		c == 'а' || c == 'о' || c == 'э' || 
                		c == 'я' || c == 'и' || c == 'ю' || c == 'ё')
                numVowels++;
                else
                	if (c == 'б' || c == 'в' || c == 'г' || c == 'д'
                			|| c == 'ж'|| c == 'з'|| c == 'й'|| c == 'к'
                			|| c == 'л'|| c == 'м'|| c == 'н'|| c == 'п'
                			|| c == 'р'|| c == 'с'|| c == 'т'|| c == 'ф'
                			|| c == 'х'|| c == 'ц'|| c == 'ч'|| c == 'ш'
                			|| c == 'щ'|| c == 'ъ'|| c == 'ь')
                		numConsonants++;
            }
            if (numVowels == 0 & numConsonants == 0)
            	System.out.println("Русские символы не обнаружены.");
            else
                System.out.println("Количество гласных во введенной строке: " + numVowels + "\nКоличество согласных во введенной строке: " + numConsonants);
            numVowels = 0;
            numConsonants = 0;
        }
        in.close();
    }
}
