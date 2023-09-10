#include "Matrix.h"
#include "MatrExc.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>

using namespace std;

int main() {
	setlocale(0, "");\
	try {
		Matrix A, B, Y;
		cin >> A >> B;
		Y = (A + B) * (A - B) / 2;
		cout << "Результат: " << Y << endl;
		//M1Check = M1, M2Check = M2;
		////+=
		//M1Check += M2Check;
		//cout << "Составной оператор сложения на матрицу: " <<  M1Check;
		//M1Check = M1, M2Check = M2;
		////-=
		//M1Check -= M2Check;
		//cout << "Составной оператор вычитания на матрицу: " << M1Check;
		//M1Check = M1, M2Check = M2;
		////*=
		//M1Check *= M2Check;
		//cout << "Составной оператор умножения на матрицу: " << M1Check;
		//M1Check = M1, M2Check = M2;
		////*=
		//M1Check *= 3.5;
		//cout << "Составной оператор умножения на число: " << M1Check;
		//M1Check = M1, M2Check = M2;
		/////=
		//M1Check /= 3.5;
		//cout << "Составной оператор деления на число: " << M1Check;
		//M1Check = M1, M2Check = M2;
		//// +
		//cout << "Сумма матриц:" << M1Check + M2Check;
		//M1Check = M1, M2Check = M2;
		//// -
		//cout << "Разность матриц:" << M1Check - M2Check;
		//M1Check = M1, M2Check = M2;
		//// *
		//cout << "Произведение матриц:" << M1Check * M2Check;
		//M1Check = M1, M2Check = M2;
		//// *
		//cout << "Произведение матрицы на число:" << M1Check * 3.5;
		//M1Check = M1, M2Check = M2;
		//// *
		//cout << "Произведение числа на матрицу:" <<  3.5 * M1Check;
		//M1Check = M1, M2Check = M2;
		//// /
		//cout << "Частное матрицы на число" << M1Check / 3.5;
		//M1Check = M1, M2Check = M2;
		//// ==
		//if (M1 == M1Check) cout << "Матрицы 1 и 1 равны\n";
		//// !=
		//if (M1 != M2) cout <<"Матрицы 1 и 2 не равны\n";
	}
	catch (MatrExc& err) {
		cout << err.what() << endl;
	}
	return 0;
}