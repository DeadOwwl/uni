import java.io.*;

public class PolynomialCharacteristic2 {

    // like %
    public static String modulo(String polynomial, String mainPolynomial){
        StringBuilder resultBuilder = new StringBuilder();
        StringBuilder polynomialBuilder = new StringBuilder(polynomial);
        StringBuilder mainBuilder;

        if (mainPolynomial.length() <= polynomialBuilder.length()) {
            while (mainPolynomial.length() <= polynomialBuilder.length()) {
                mainBuilder = new StringBuilder(mainPolynomial);
                while (mainBuilder.length() != polynomialBuilder.length()) {
                    mainBuilder.reverse();
                    mainBuilder.append('0');
                    mainBuilder.reverse();
                }
                int coefficient;
                if (polynomialBuilder.charAt(polynomialBuilder.length() - 1) == '1' && mainBuilder.charAt(mainBuilder.length() - 1) == '1') {
                    resultBuilder.append('1');
                    coefficient = 1;
                } else {
                    resultBuilder.append('0');
                    coefficient = 0;
                }
                for (int i = 0; i < mainBuilder.length(); i++) {
                    int a = Character.getNumericValue(mainBuilder.charAt(i));
                    mainBuilder.replace(i, i + 1, Integer.toString((a * coefficient % 2)));
                }
                for (int i = 0; i < polynomialBuilder.length() - 1; i++) {
                    int difference = Math.abs(Character.getNumericValue(polynomialBuilder.charAt(i)) -
                            Character.getNumericValue(mainBuilder.charAt(i)));
                    polynomialBuilder.replace(i, i + 1, Integer.toString(difference));
                }
                polynomialBuilder.deleteCharAt(polynomialBuilder.length() - 1);
            }
            resultBuilder.reverse();
        } else resultBuilder.append(polynomial);

        while ((polynomialBuilder.lastIndexOf("0") == polynomialBuilder.length() - 1) &&
                (polynomialBuilder.length() != 1))
            polynomialBuilder.deleteCharAt(polynomialBuilder.length() - 1);
        return polynomialBuilder.toString();
    }

    // +
    public static String add(String firstPolynomial, String secondPolynomial){
        StringBuilder resultBuilder = new StringBuilder();
        int i = 0;
        while (i < firstPolynomial.length() && i < secondPolynomial.length()){
            int a = Character.getNumericValue(firstPolynomial.charAt(i));
            int b = Character.getNumericValue(secondPolynomial.charAt(i));
            resultBuilder.append((a + b) % 2);
            i++;
        }
        if(i > firstPolynomial.length()) resultBuilder.append(firstPolynomial.substring(i));
        else resultBuilder.append(secondPolynomial.substring(i));
        while ((resultBuilder.lastIndexOf("0") == resultBuilder.length() - 1) &&
                (resultBuilder.length() != 1))
            resultBuilder.deleteCharAt(resultBuilder.length() - 1);
        return resultBuilder.toString();
    }

    // *
    public static String multy(String firstPolynomial, String secondPolynomial){
        StringBuilder resultBuilder = new StringBuilder();
        for (int i = 0; i < firstPolynomial.length() + secondPolynomial.length() - 1; i++){
            int composition = 0;
            for(int j = 0; j < firstPolynomial.length(); j++)
                for(int k = 0; k < secondPolynomial.length(); k++)
                    if(j + k == i) {
                        int a = Character.getNumericValue(firstPolynomial.charAt(j));
                        int b = Character.getNumericValue(secondPolynomial.charAt(k));
                        composition += a * b;
                    }
            composition %= 2;
            resultBuilder.append(composition);
        }

        while ((resultBuilder.lastIndexOf("0") == resultBuilder.length() - 1)
                && (resultBuilder.length() != 1))
            resultBuilder.deleteCharAt(resultBuilder.length() - 1);
        return resultBuilder.toString();
    }

    // -_- /
    public static String division(String firstPolynomial, String secondPolynomial, String mainPolynomial){
        return multy(firstPolynomial, inverse(secondPolynomial, mainPolynomial));
    }

    // modulo inverse
    public static String inverse(String poly, String mainPolynomial){
        String tempResult;
        StringBuilder resultBuilder;
        String checker = modulo(poly, mainPolynomial);

        if(checker.length() == 1 && checker.charAt(0) == '0')
            throw new RuntimeException("Modulo inverse hasn't been found.");

        int k = 1;

        do{
            String binaryString = Integer.toBinaryString(k);
            StringBuilder x = new StringBuilder();
            int j = 0;
            for (int i = binaryString.length() - 1; i >= 0; i--){
                x.replace(j, j + 1, String.valueOf(binaryString.charAt(i)));
                j++;
            }
            resultBuilder = new StringBuilder(x);

            if(resultBuilder.length() > 21) throw new RuntimeException("Modulo inverse hasn't been found.");

            String multiplication_result = multy(resultBuilder.toString(), poly);
            tempResult = modulo(multiplication_result, mainPolynomial);
            ++k;
        } while (tempResult.length() != 1 || tempResult.charAt(0) != '1');

        while ((resultBuilder.lastIndexOf("0") == resultBuilder.length() - 1) &&
                (resultBuilder.length() != 1))
            resultBuilder.deleteCharAt(resultBuilder.length() - 1);
        return resultBuilder.toString();
    }

    // please
    public static void main(String[] args) throws IOException {
        BufferedReader inputReader = new BufferedReader(new FileReader("input.txt"));
        BufferedReader polynomialReader = new BufferedReader(new FileReader("polynom.txt"));

        String result;
        String polynomial = polynomialReader.readLine();
        String inputString = inputReader.readLine();

        if (inputString.contains("+"))
            result = add(inputString.substring(0, inputString.indexOf("+")),
                    inputString.substring(inputString.indexOf("+") + 1));
        else if (inputString.contains("*"))
            result = multy(inputString.substring(0, inputString.indexOf("*")),
                    inputString.substring(inputString.indexOf("*") + 1));
        else if (inputString.contains("/"))
            result = division(inputString.substring(0, inputString.indexOf("/")),
                    inputString.substring(inputString.indexOf("/") + 1), polynomial);
        else if (inputString.contains("^-1"))
            result = inverse(inputString.substring(0, inputString.indexOf("-")), polynomial);
        else if (inputString.contains("^")){
            int k = Integer.parseInt(inputString.substring(inputString.indexOf("^") + 1));
            String poly = inputString.substring(0, inputString.indexOf("^"));result = poly;
            while (k > 1){
                result = multy(result, poly);
                k--;
            }
        }
        else throw new RuntimeException("Unknown operation.");

        BufferedWriter out = new BufferedWriter(new FileWriter("output.txt"));
        out.write(modulo(result, polynomial));
        out.flush();
        out.close();
    }
}
