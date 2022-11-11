public class Test {

    public static double eps = 1e-6;
    public static double[][] B = {{1.342, 0.432, -0.599, 0.202, 0.603, -0.202},
                                  {0.432, 1.342, 0.256, -0.599, 0.204, 0.304},
                                  {-0.599, 0.256, 1.342, 0.532, 0.101, 0.506},
                                  {0.202, -0.599, 0.532, 1.342, 0.106, -0.311},
                                  {0.603, 0.204, 0.101, 0.106, 1.342, 0.102},
                                  {-0.202, 0.304, 0.506, -0.311, 0.102, 1.342}};
    public static int k = 9;
    public static double[] C = {0.05, 0.03, 0.02, 0.04, 0.06, 0.07};
    //Получение матрицы А
    public static double[][] getA (double[][] gB, int gK, double[] gC){
        double[][] gA = new double[gB.length][gB.length];
        for (int i = 0; i < gB.length; i++){
            System.arraycopy(gB[i], 0, gA[i], 0, gB[i].length);
            gA[i][i] = gB[i][i] + gK * gC[i];
        }
        return gA;
    }
    //Печать матрицы
    public static void matrixPrinting(double[][] M, int m, int p) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < p; j++) {
                System.out.printf("%7.3f", M[i][j]);
            }
            System.out.print("\n");
        }
        System.out.print("\n");
    }
    //Печать вектора
    public static void vectorPrinting(double[] M) {
        for (int i = 0; i < M.length; i++) {
            System.out.printf("(%f)\n", M[i]);
        }
    }
    //Получение вектора начальных значений
    public static double[] getY0 (int n){
        double y[] = new double[n];
        for (int i = 0; i < n; i++)
            y[i] = 1;
        return y;
    }
    //Умножение матрицы на вектор
    public static double[] multiplicationMatrixVector (double[][] A, double[] y){
        double[] y1 = new double[y.length];
        for (int i = 0; i < y1.length; i++){
            for (int j = 0; j < y1.length; j++)
                y1[i] += A[i][j] * y[j];
        }
        return y1;
    }
    //Умножение вектора на скаляр
    private static double[] multiplicationVectorScalar(double [] y, double n){
        double[] yN = new double[y.length];
        for (int i = 0; i < y.length; i++)
            yN[i] = y[i] * n;
        return yN;
    }
    //Вычисление невязки (вектора r1)
    private static double[] vectorR1 (double[][] A, double l, double[] x){
        double[] c = new double[x.length];
        double[] ax = multiplicationMatrixVector(A, x);
        double[] lx = multiplicationVectorScalar(x, l);
        for (int i = 0; i < x.length; i++)
            c[i] = ax[i] - lx[i];
        return c;
    }

    public static void main(String[] args){
        double[][] A = getA(B, k, C);
        System.out.println("Исходная матрица: ");
        matrixPrinting(A, A.length, A.length);

        System.out.println("ИСМ - итерационный степенной метод;\nМСП - метод скалярных произведений\n");

        double[] yIPM = getY0(A.length);
        double[] yDPM = getY0(A.length);
        System.out.println("Начальный вектор для ИСМ: ");
        vectorPrinting(yIPM);
        System.out.print("Начальный вектор для МСП: \n");
        vectorPrinting(yDPM);

        double maxEigenIPM = iterativePowerMethod.maxEigenValue(A, eps, yIPM);
        double maxEigenDPM = dotProductMethod.maxEigenValue(A, eps, yDPM);
        System.out.println("\nМаксимальное приближенное по модулю собственное значение по ИСМ: \n" + maxEigenIPM +
                "\nМаксимальное приближенное по модулю собственное значение по МСП: \n" + maxEigenDPM + "\n");

        double[] eigenvaluesIPM = iterativePowerMethod.vectorEigenValues(A, eps, yIPM);
        double[] eigenvaluesDPM = dotProductMethod.vectorEigenValues(A, eps, yDPM);
        System.out.println("Собственных вектор по ИСМ: ");
        vectorPrinting(eigenvaluesIPM);
        System.out.print("Собственных вектор по МСП: \n");
        vectorPrinting(eigenvaluesDPM);

        double[] r1IPM = vectorR1(A, maxEigenIPM, eigenvaluesIPM);
        double[] r1DMP = vectorR1(A, maxEigenDPM, eigenvaluesDPM);
        System.out.println("\nВектор r1 для ИСМ: ");
        vectorPrinting(r1IPM);
        System.out.print("Вектор r1 для МСП: \n");
        vectorPrinting(r1DMP);

        int iterationsIPM = iterativePowerMethod.iterationsNum(A, eps, yIPM);
        int iterationsDPM = dotProductMethod.iterationsNum(A, eps, yDPM);
        System.out.println("\nЧисло итераций для заданной точности по ИСМ: " + iterationsIPM +
                "\nЧисло итераций для заданной точности по по МСП: " + iterationsDPM);
    }
}