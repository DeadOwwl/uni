//¬ариант 17.
//считать с консоли размерность n матрицы.
//ћатрицу заполнить рандомными числами из диапазона от -n до n.
//“ранспонировать матрицу и вывести результат

import java.util.*;

public class task_17 {

    static void processMatrix(int n){
        int[][] A = new int[n][n];
        System.out.println("Generated matrix: ");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = (int) (Math.random() * (2 * n + 1)) - n;
                System.out.printf("%5d", A[i][j]);
            }
            System.out.println();
        }
        System.out.println("Transported generated matrix: ");
        int[][] B = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                B[i][j] = A[j][i];
                System.out.printf("%5d", B[i][j]);
            }
            System.out.println();
        }
    }

    public static void main(String[]args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter matrix size: ");
        int n = scan.nextInt();
        processMatrix(n);
    }
}
