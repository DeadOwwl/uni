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
	double** p; //��������� �� 2-������ ������
public:
	//����������� �� ���������
	Matrix();
	//����������� � �����������
	Matrix(int , int );
	//����������� �����������
	Matrix(const Matrix& n);
	//����������
	~Matrix();
	void SetM(int s) { m = s; }
	void SetN(int c) { n = c; }
	int GetM()const { return m; }
	int GetN()const { return n; }
	void SetAll(int, int, double);
	double GetAll(int, int) const;
	//�������� ������������
	Matrix& operator=(const Matrix& n);
	//�o������� ��������� ������������
	Matrix& operator += (const Matrix& M);
	Matrix& operator -=(const Matrix& M);
	Matrix& operator *=(const Matrix& M);
	Matrix& operator *=(const double& d);
	Matrix& operator /= (const double& d);
	//�������� �������� ����� ���������
	Matrix operator+(const Matrix& M) const;
	Matrix operator-(const Matrix& M) const;
	Matrix operator*(const Matrix& M) const;
	//�������� �������� ����� �������� � ������
	Matrix operator*(const double& Num) const;// ������� �� �����
	friend Matrix operator*(const double& Num, const Matrix&);// ����� �� �������
	Matrix operator/(const double& Num)const;//������� �� �����
	//��������� ������
	bool operator ==(const Matrix& M)const;
	bool operator !=(const Matrix& M)const;
	//���� � ����� �������
	friend istream& operator>>(istream& cin, Matrix& M);
	friend ostream& operator<<(ostream& cout, const Matrix& M);
};
#endif