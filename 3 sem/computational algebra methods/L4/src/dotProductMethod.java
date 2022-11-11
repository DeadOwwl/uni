import java.util.*;

public class dotProductMethod {
    //Максимальное значение в векторе
    private static double vectorNorm (double[] y0){
        double yNorm = Math.abs(y0[0]);
        for (int i = 0; i < y0.length;i++) {
            if (yNorm < Math.abs(y0[i])) {
                yNorm = Math.abs(y0[i]);
            }
        }
        return yNorm;
    }
    //Деление вектора на скаляр
    private static double[] divisionVectorScalar (double [] y, double n){
        double[] yN = new double[y.length];
        for (int i = 0; i < y.length; i++)
            yN[i] = y[i]/n;
        return yN;
    }
    //Умножение матрицы на вектор
    private static double[] multiplicationMatrixVector (double[][] A, double[] y){
        double[] y1 = new double[y.length];
        for (int i = 0; i < y1.length; i++){
            for (int j = 0; j < y1.length; j++)
                y1[i] += A[i][j] * y[j];
        }
        return y1;
    }
    //Скалярное произведение векторов
    private static double scalarMultiplicationVectors (double[] y1, double[] y2){
        double y = 0;
        for (int i = 0; i < y1.length; i++)
            y += y1[i] * y2[i];
        return y;
    }
    //Максимальное собственное значение
    public static double maxEigenValue(double[][] A, double eps, double[] y0){
        double lBefore = 0;
        double lAfter = 0;

        double[] yBefore = Arrays.copyOf(y0, y0.length);
        double[] yNormBefore = divisionVectorScalar(yBefore, vectorNorm(yBefore));

        double[] yAfter;
        double delta = 1.0;

        while (delta > eps) {
            yAfter = multiplicationMatrixVector(A, yNormBefore);

            lAfter = scalarMultiplicationVectors(yAfter, yNormBefore) / scalarMultiplicationVectors(yNormBefore, yNormBefore);

            double norm = vectorNorm(yAfter);
            yNormBefore = divisionVectorScalar(yAfter, norm);

            delta = Math.abs(lAfter - lBefore);

            lBefore = lAfter;
        }

        return Math.abs(lAfter);
    }
    //Собственный вектор, соответствующий максимальному собственному значению
    //Смысл переменных такой же, как в методе выше, отличие в возвращаемом значении
    public static double[] vectorEigenValues(double[][] A, double eps, double[] y0){
        double lBefore = 0;
        double lAfter = 0;

        double[] yBefore = Arrays.copyOf(y0, y0.length);
        double[] yNormBefore = divisionVectorScalar(yBefore, vectorNorm(yBefore));

        double[] yAfter;
        double delta = 1.0;

        while (delta > eps) {
            yAfter = multiplicationMatrixVector(A, yNormBefore);

            lAfter = scalarMultiplicationVectors(yAfter, yNormBefore) / scalarMultiplicationVectors(yNormBefore, yNormBefore);

            double norm = vectorNorm(yAfter);
            yNormBefore = divisionVectorScalar(yAfter, norm);

            delta = Math.abs(lAfter - lBefore);

            lBefore = lAfter;
        }

        return yNormBefore;
    }
    //Количество итераций метода
    //Смысл переменных такой же, как в методе выше, отличие в возвращаемом значении
    public static int iterationsNum(double[][] A, double eps, double[] y0){
        double lBefore = 0;
        double lAfter = 0;

        double[] yBefore = Arrays.copyOf(y0, y0.length);
        double[] yNormBefore = divisionVectorScalar(yBefore, vectorNorm(yBefore));

        double[] yAfter;
        double delta = 1.0;

        int k = 0;

        while (delta > eps) {
            yAfter = multiplicationMatrixVector(A, yNormBefore);

            lAfter = scalarMultiplicationVectors(yAfter, yNormBefore) / scalarMultiplicationVectors(yNormBefore, yNormBefore);

            double norm = vectorNorm(yAfter);
            yNormBefore = divisionVectorScalar(yAfter, norm);

            delta = Math.abs(lAfter - lBefore);

            lBefore = lAfter;

            k++;
        }

        return k;
    }
}