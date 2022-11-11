import java.util.Random;
import java.util.Date;

public class IteratoinMethods
{
    //Размер матрицы
    public static int n = 10;
    //Точность
    public static double eps = Math.pow(10, -7);
    //Матрица размером 2 на 7 для хранения в ней значений параметра релаксации и соответствующее количество итераций для заданной точности
    public static double[][] WandK = {{0.2, 0.5, 0.8, 1, 1.3, 1.5, 1.8},
            {0, 0, 0, 0, 0, 0, 0}};
    public static int t = 0;
    //Метод для генерации А
    public static double[][] MatrixGenerationA() {
        double[][] A = new double[n][n];
        Random myRand = new Random((new Date()).getTime());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = (myRand.nextDouble() * (20) - 10);
            }
        }
        return A;
    }
    //Метод для генерации X
    public static double[] MatrixGenerationX() {
        double[] X = new double[n];
        Random myRand = new Random((new Date()).getTime());
        for (int i = 0; i < n; i++) {
            X[i] = (myRand.nextDouble() * (20) - 10);
        }
        return X;
    }
    //Печать матрицы
    public static void MatrixPrinting(double[][] M, int m, int p) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < p; j++) {
                System.out.printf("%7.2f", M[i][j]);
            }
            System.out.print("\n");
        }
    }
    //Получение F
    public static double[] MatrixGettingF(double[][] A, double[] X) {
        double[] F = new double[n];
        for (int i = 0; i < n; i++) {
            F[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                F[i] += A[i][j] * X[j];
            }
        }
        return F;
    }
    //Печать вектора
    public static void ArrayPrinting(double[] M, int m) {
        for (int i = 0; i < m; i++) {
            System.out.printf("%9.2f", M[i]);
        }
        System.out.print("\n");
    }
    //Нахождение максимум-нормы погрешности
    public static double MaxNormError(double[] X, double[] desX){
        double[]errorX = new double [n];
        for (int i = 0; i < n; i++) {
            errorX[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            errorX[i] = Math.abs(X[i] - desX[i]);
        }
        double maxNE = errorX[0];
        for (int i = 0; i < n; i++)
        {
            if (errorX[i] > maxNE)
                maxNE = errorX[i];
        }
        return maxNE;
    }
    //Метод простых итераций
    public static double[] SimpleIterationsMethod(double[][] A, double[] F){
        //Матрица А после умножения на себя же транспонированную
        double [][] _A_ = new double[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                _A_[i][j] = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    _A_[i][j] += A[k][i] * A[k][j];

        //Вектор F после умножения на транспонированную А
        double [] _F_ = new double[n];
        for (int j = 0; j < n; j++)
            _F_[j] = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                _F_[i] += A[j][i] * F[j];

        //Норма матрицы
        double nm = mNorm(_A_);

        //Единичная матрица
        double[][] E = new double[n][n];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                E[i][j] = 0;
            E[i][i] = 1;
        }
        //Вектор g и матрица В для приведения к каноническому виду
        double[] g = new double[n];
        double[][] B = new double[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                B[i][j] = -1 * _A_[i][j] / nm;
                B[i][j] += E[i][j];
            }
        }
        for (int i = 0; i < n; i++)
            g[i] = _F_[i] / nm;
        //Веткор начальных значений
        double[] x0 = new double[n];
        for (int i = 0; i < n; i++)
            x0[i] = g[i];
        //Вектор для последующих шагов вычисления
        double[] x1 = new double[n];
        for (int i = 0; i < n; i++)
        {
            double temp = 0;
            for (int j = 0; j < n; j++)
            {
                temp += B[i][j] * x0[j];
            }
            x1[i] = temp + g[i];
        }

        while (Math.abs(vNorm(x0, x1)) > eps)
        {
            for (int i = 0; i < n; i++)
                x0[i] = x1[i];
            for (int i = 0; i < n; i++)
            {
                double temp = 0;
                for (int j = 0; j < n; j++)
                {
                    temp += B[i][j] * x0[j];
                }
                x1[i] = temp + g[i];
            }
        }
        return x1;
    }
    //Векторная норма
    public static double vNorm(double[] a, double[] b){
        double max = 0;
        for (int i = 0; i < n; i++)
        {
            if (Math.abs(a[i] - b[i]) > max)
                max = Math.abs(a[i] - b[i]);
        }
        return max;
    }
    //Метод релаксации для k - количества итераций
    public static int RelaxMethodK(double w, double[][] A, double[] F){
        //Системы аналогичные методу простых итераций
        double [][] _A_ = new double[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                _A_[i][j] = 0;

        double [] _F_ = new double[n];
        for (int j = 0; j < n; j++)
            _F_[j] = 0;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    _A_[i][j] += A[k][i] * A[k][j];

        int k = 0;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                _F_[i] += A[j][i] * F[j];

        double[] g = new double[n];

        for (int i = 0; i < n; i++)
            g[i] = _F_[i] / _A_[i][i];

        double[] x0 = new double[n];
        double[] x1 = new double[n];

        for (int i = 0; i < n; i++)
            x1[i] = g[i];
        do {
            for (int i = 0; i < n; i++)
                x0[i] = x1[i];
            for (int i = 0; i < n; i++)
            {
                double temp = 0;
                for (int j = i + 1; j < n; j++)
                {
                    temp += _A_[i][j] * x0[j] / _A_[i][i];
                }
                x1[i] = -temp + (_F_[i] / _A_[i][i]);
                temp = 0;
                for (int j = 0; j < i; j++)
                    temp += _A_[i][j] * x1[j] / _A_[i][i];
                x1[i] -= temp;
                x1[i] *= w;
                x1[i] += (1 - w) * x0[i];
            }
            k++;
        } while (vNorm(x1, x0)  / w >= eps);
        WandK[1][t++] = k;
        return k;
    }
    //Метод релаксации
    public static double[] RelaxMethod(double w, double[][] A, double[] F){
        //Все аналогично мтеоду выше, однако этот возвращает решение
        double [][] _A_ = new double[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                _A_[i][j] = 0;

        double [] _F_ = new double[n];
        for (int j = 0; j < n; j++)
            _F_[j] = 0;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    _A_[i][j] += A[k][i] * A[k][j];

        double nm = mNorm(_A_);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                _F_[i] += A[j][i] * F[j];

        double[] g = new double[n];

        for (int i = 0; i < n; i++)
            g[i] = _F_[i] / _A_[i][i];

        double[] x0 = new double[n];
        double[] x1 = new double[n];

        for (int i = 0; i < n; i++)
            x1[i] = g[i];
        do {
            for (int i = 0; i < n; i++)
                x0[i] = x1[i];
            for (int i = 0; i < n; i++)
            {
                double temp = 0;
                for (int j = i + 1; j < n; j++)
                {
                    temp += _A_[i][j] * x0[j] / _A_[i][i];
                }
                x1[i] = -temp + (_F_[i] / _A_[i][i]);
                temp = 0;
                for (int j = 0; j < i; j++)
                    temp += _A_[i][j] * x1[j] / _A_[i][i];
                x1[i] -= temp;
                x1[i] *= w;
                x1[i] += (1 - w) * x0[i];
            }
        } while (vNorm(x1, x0)  / w >= eps);
        return x1;
    }
    //Матричная норма
    public static double mNorm(double[][] m){
        double max = 0;
        for (int i = 0; i < n; i++)
        {
            double temp = 0;
            for (int j = 0; j < n; j++)
                temp += Math.abs(m[i][j]);
            if (max < temp)
                max = temp;
        }
        return max;
    }
    //Сортировка
    public static double[][] sortingWandK(double[][] arr){
        for (int i = 0; i < 7; i++) {
            for (int j = i + 1; j < 7; j++){
                if (arr[1][i] > arr[1][j]){
                    double as = arr[0][i];
                    double bs = arr[1][i];
                    arr[0][i] = arr[0][j];
                    arr[1][i] = arr[1][j];
                    arr[0][j] = as;
                    arr[1][j] = bs;
                }
            }
        }
        return arr;
    }
    //Главная функция
    public static void main(String[] args) throws Exception {
        double[][] A = MatrixGenerationA();
        System.out.print("Исходная матрица: \n");
        MatrixPrinting(A, n, n);
        double[] X = MatrixGenerationX();
        double[] F = MatrixGettingF(A, X);
        System.out.println("Исходная правая часть:");
        ArrayPrinting(F, n);
        System.out.println("Исходное точное решение:");
        ArrayPrinting(X, n);
        System.out.println("Требуемая точность нахождения решения:\n" + 1e-5);
        double[] desX = SimpleIterationsMethod(A, F);
        System.out.println("Полученное точное решение методом простых итераций:");
        ArrayPrinting(desX, n);
        System.out.println("Максимум-норма погрешности метода простых итераций: \n" + MaxNormError(X, desX));
        System.out.println("Значения параметра релаксации w, количества итераций k + 1 для достижения заданной точности и максимум-норма погрещностей метода релаксаций:");
        for (int i = 0; i < 7; i++){
            System.out.println("w = " + WandK[0][i] + ", k + 1 = " + RelaxMethodK(WandK[0][i], A, F) + ", максимум-норма погрешности " + MaxNormError(X, RelaxMethod(WandK[0][i], A, F)));
        }
        WandK = sortingWandK(WandK);
        System.out.println("Полученное точное решение методом релаксаций для параметра w с минимальным количеством итераций w = " + WandK[0][0] + ":");
        desX = RelaxMethod(WandK[0][0], A, F);
        ArrayPrinting(desX, n);
        System.out.println("Максимум-норма погрешности метода релаксаций для параметра w с минимальным количеством итераций w = " + WandK[0][0] + ":\n" + MaxNormError(X, desX));
    }
}
