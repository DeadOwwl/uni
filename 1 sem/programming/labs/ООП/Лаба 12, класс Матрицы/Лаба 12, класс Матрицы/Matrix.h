#pragma once
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

#ifndef __Matrix_defined__
#define __Matrix_defined__

struct BadSize {};
struct ZeroDivide {};

class Matrix {
	int m, n;
	double** p; //Указатель на 2-мерный массив
public:
	//Конструктор по умолчанию
	Matrix();
	//Конструктор с параметрами
	Matrix(int , int );
	//Конструктор копирования
	Matrix(const Matrix& n);
	//Деструктор
	~Matrix();
	void SetM(int s) { m = s; }
	void SetN(int c) { n = c; }
	int GetM()const { return m; }
	int GetN()const { return n; }
	void SetAll(int, int, double);
	double GetAll(int, int) const;
	//Оператор присваивания
	Matrix& operator=(const Matrix& n);
	//Сoставные операторы присваивания
	Matrix& operator += (const Matrix& M);
	Matrix& operator -=(const Matrix& M);
	Matrix& operator *=(const Matrix& M);
	Matrix& operator *=(const double& d);
	Matrix& operator /= (const double& d);
	//Бинарные операции между матрицами
	Matrix operator+(const Matrix& M) const;
	Matrix operator-(const Matrix& M) const;
	Matrix operator*(const Matrix& M) const;
	//Бинарные операции между матрицей и числом
	Matrix operator*(const double& Num) const;// Матрица на число
	friend Matrix operator*(const double& Num, const Matrix&);// Число на матрицу
	Matrix operator/(const double& Num)const;//Матрица на число
	//Сравнение матриц
	bool operator ==(const Matrix& M)const;
	bool operator !=(const Matrix& M)const;
	//Ввод и вывод матрицы
	friend istream& operator>>(istream& cin, Matrix& M);
	friend ostream& operator<<(ostream& cout, const Matrix& M);
};
#endif