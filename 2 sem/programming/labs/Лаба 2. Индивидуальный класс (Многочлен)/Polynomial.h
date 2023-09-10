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
	Polynomial(); // ����������� ��� ����������
	~Polynomial(); // ����������
	Polynomial(const int& deg); // ����������� � ���������� (��������)
	Polynomial(const Polynomial& M); // ����������� �����������
	double ValueCalculating(const int& x) const; // ���������� �������� ���������� �� ����������
	Polynomial FirstDerivative(); // ������ ����������� ����������
	int GetDeg() { return Deg; } // ������ ��� �������
	Polynomial& operator = (const Polynomial& P); // ������������
	double* GetCoefficients() { return Coefficients; } // ������ ��� ������������
	Polynomial operator + (const Polynomial& P) const; // �������� �����������
	Polynomial operator - (const Polynomial& P) const; // ��������� �����������
	Polynomial operator * (const Polynomial& P) const; // ��������� �����������
	friend istream& operator >> (istream& in, Polynomial& P); // ���� ����������
	friend ostream& operator << (ostream& in, const Polynomial& P); // ����� ����������
};
#endif 