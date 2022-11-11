import java.util.*;
import java.lang.*;

public class iterativePowerMethod {
    //Максимальное значение вектора
    private static double vectorNorm (double[] y0){
        double yNorm = Math.abs(y0[0]);
        for (int i = 1; i < y0.length;i++) {
            if (yNorm < Math.abs(y0[i])) {
                yNorm = Math.abs(y0[i]);
            }
        }
        return yNorm;
    }
    //Норма разности векторов
    private static double vectorsDifferenceNorm (double[] y1, double[] y2){
        double yNorm = Math.abs(y1[0] - y2[0]);
        for (int i = 1; i < y1.length;i++) {
            if (yNorm < Math.abs(y1[i] - y2[i]))
                yNorm = Math.abs(y1[i] - y2[i]);
        }
        return yNorm;
    }
    //Деление вектора на скаляр
    private static double[] divisionVectorScalar (double [] y, double n){
        double[] yN = new double[y.length];
        for (int i = 0; i < y.length; i++)
            yN[i] = y[i] / n;
        return yN;
    }
    //Умножение мтарицы на вектор
    private static double[] multiplicationMatrixVector (double[][] A, double[] y){
        double[] y1 = new double[y.length];
        for (int i = 0; i < y1.length; i++){
            for (int j = 0; j < y1.length; j++)
                y1[i] += A[i][j] * y[j];
        }
        return y1;
    }
    //Максимальное значение вектора
    private static double[] divisionVectors (double[] y1, double[] y2){
        double[] y = new double[y1.length];
        for (int i = 0; i < y1.length; i++)
            y[i] = y1[i] / y2[i];
        return y;
    }
    //Среднее значение координат векторов
    private static double averageEigenValue (double[] y){
        double sum = 0;
        for (int i = 0; i < y.length; i++)
            sum += y[i];
        return Math.abs(sum / y.length);
    }
    //Максимальное собственное значение матрицы
    public static double maxEigenValue(double[][] A, double eps, double[] y0){
        double[] lBefore = new double[y0.length]; //Вектор собственных значений на k-ой итерации
        double[] lAfter = new double[y0.length]; //Вектор собственных значений k+1 -ой итерации

        double[] yBefore = Arrays.copyOf(y0, y0.length); //Вектор значений на k-ой итерации
        double[] yNormBefore = divisionVectorScalar(yBefore, vectorNorm(yBefore)); //Вектор нормированных значений на k-ой итерации

        double[] yAfter; //Вектор значений на k+1 -ой итерации
        double delta = 1.0; //Условие выхода из цикла (норма разности векторов собственных значений на k-ой и k+1 -ой итерациях

        while (delta > eps) { //Пока не достигнута заданная точность
            yAfter = multiplicationMatrixVector(A, yNormBefore);

            lAfter = divisionVectors(yAfter, yNormBefore);

            double norm = vectorNorm(yAfter); //норма вектора значений на k+1 -ой итерации
            yNormBefore = divisionVectorScalar(yAfter, norm);

            delta = vectorsDifferenceNorm(lAfter, lBefore);

            lBefore = Arrays.copyOf(lAfter, lAfter.length);
        }

        return averageEigenValue(lAfter);
    }
    //Собственный вектор, соответствующий максимальному собственному значению
    //Смысл переменных такой же, как в методе выше, отличие в возвращаемом значении
    public static double[] vectorEigenValues(double[][] A, double eps, double[] y0){
        double[] lBefore = new double[y0.length];
        double[] lAfter = new double[y0.length];

        double[] yBefore = Arrays.copyOf(y0, y0.length);
        double[] yNormBefore = divisionVectorScalar(yBefore, vectorNorm(yBefore));

        double[] yAfter;
        double delta = 1.0;

        while (delta > eps) {
            yAfter = multiplicationMatrixVector(A, yNormBefore);

            lAfter = divisionVectors(yAfter, yNormBefore);

            double norm = vectorNorm(yAfter);
            yNormBefore = divisionVectorScalar(yAfter, norm);

            delta = vectorsDifferenceNorm(lAfter, lBefore);

            lBefore = Arrays.copyOf(lAfter, lAfter.length);
        }

        return yNormBefore;
    }
    //Количество итераций метода
    //Смысл переменных такой же, как в методе выше, отличие в возвращаемом значении
    public static int iterationsNum(double[][] A, double eps, double[] y0){
        double[] lBefore = new double[y0.length];
        double[] lAfter = new double[y0.length];

        double[] yBefore = Arrays.copyOf(y0, y0.length);
        double[] yNormBefore = divisionVectorScalar(yBefore, vectorNorm(yBefore));

        double[] yAfter;
        double delta = 1.0;

        int k = 0;

        while (delta > eps) {
            yAfter = multiplicationMatrixVector(A, yNormBefore);

            lAfter = divisionVectors(yAfter, yNormBefore);

            double norm = vectorNorm(yAfter);
            yNormBefore = divisionVectorScalar(yAfter, norm);

            delta = vectorsDifferenceNorm(lAfter, lBefore);

            lBefore = Arrays.copyOf(lAfter, lAfter.length);

            k++;
        }

        return k;
    }
}