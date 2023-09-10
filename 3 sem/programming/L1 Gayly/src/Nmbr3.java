public class Nmbr3 {
    public static void main(String[] args) {

        if (args.length != 2) {
            System.err.println("Invalid number of arguments");
            System.exit(1);
        }
        double x = Double.parseDouble(args[0]);

        if (x >= 1 || x < -1) {
            System.err.println("Invalid argument: " + x);
            System.exit(1);
        }
        int k = Integer.parseInt(args[1]);

        if (k <= 1) {
            System.err.println("Invalid argument: " + k);
            System.exit(1);
        }
        double Eps = Math.pow(10, -k);

        double result = 0;
        double step = x;
        double stepForConsole = x;
        int n = 1;

        while(Math.abs(step) >= Eps) {
            result += step;
            step = ((step * n) * x)/(n + 1);
            n++;
        }

        result = (-1) * result;
        System.out.println("Initial data: \n" + "x = " + stepForConsole + ", eps = " + Eps);
        System.out.println("Result by algorithm: " + result);
        System.out.println("Result by Math library: " + Math.log(1-x));
        System.exit(0);
    }
}