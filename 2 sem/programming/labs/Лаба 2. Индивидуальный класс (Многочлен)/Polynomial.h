#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

#ifndef __Polynomial_defined__
#define __Polynomial_defined__

class Polynomial
{
private:
	int Deg;
	double* Coefficients;
public:
	Polynomial(); // Констурктор юез параметров
	~Polynomial(); // Деструктор
	Polynomial(const int& deg); // Конструктор с параметром (степенью)
	Polynomial(const Polynomial& M); // Конструктор копирования
	double ValueCalculating(const int& x) const; // Вычисление значения многочлена по переменной
	Polynomial FirstDerivative(); // Первая производная многочлена
	int GetDeg() { return Deg; } // Геттер для степени
	Polynomial& operator = (const Polynomial& P); // Присваивание
	double* GetCoefficients() { return Coefficients; } // Геттер для коэффицентов
	Polynomial operator + (const Polynomial& P) const; // Сложение многочленов
	Polynomial operator - (const Polynomial& P) const; // Вычитание многчоленов
	Polynomial operator * (const Polynomial& P) const; // Умножение многочленов
	friend istream& operator >> (istream& in, Polynomial& P); // Ввод многочлена
	friend ostream& operator << (ostream& in, const Polynomial& P); // Вывод многочлена
};
#endif 