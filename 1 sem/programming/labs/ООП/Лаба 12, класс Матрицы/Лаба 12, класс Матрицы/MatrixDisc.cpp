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

// Get ��� �������� �������
double Matrix::GetAll(int i, int j) const {
	if ((i >= m) || (j >= n) || (i < 0) || (j < 0)) throw MatrExc("������! ��������� ������� ������� �� ������� �������.");
	return p[i][j];
}

// Set ��� �������� �������
void Matrix::SetAll(int i, int j, double num) {
	if ((i >= m) || (j >= n) || (i < 0) || (j < 0)) throw MatrExc("������! ��������� ������� ������� �� ������� �������.");
	p[i][j] = num;
}

//����������� ��� ����������
Matrix::Matrix() {
	m = 1, n = 1;
	p = new double* [m];
	for (int i(0); i<m; i++) p[i] = new double[n];
	p[0][0] = 1;
}

// ����������� � �����������
Matrix::Matrix(int ma, int na) {
	if (ma <= 0 || na <= 0) throw MatrExc("������! ��������� ������� ������ ���� ����� 0.");
	m = ma, n = na;
	p = new double* [m];
	for (int i(0); i < m; i++) p[i] = new double[n];
	for (int i(0); i < m; i++) {
		for (int j(0); j < n; j++) p[i][j] = 0;
	}
}

// ����������� ����������� 
Matrix::Matrix(const Matrix& matr) {
	m = matr.m, n = matr.n;
	p = new double* [m];
	for (int i(0); i < m; i++) p[i] = new double[n];
	for (int i(0); i < m; i++) {
		for (int j(0); j < n; j++) p[i][j] = matr.p[i][j];
	}
}

// ����������
Matrix::~Matrix() {
	for (int i(0); i < m; i++) delete[] p[i];
	delete[] p;
	m = 0, n = 0;
}

// �������� ������������ 
Matrix& Matrix::operator=(const Matrix& matr) {
	if (this == &matr) return *this;
	for (int i(0); i < m; i++) delete[] p[i];
	delete[] p;
	m = matr.m, n = matr.n;
	p = new double* [m];
	for (int i(0); i < m; i++) p[i] = new double[n];
	for (int i(0); i < m; i++) {
		for (int j(0); j < n; j++) p[i][j] = matr.p[i][j];
	}
	return *this;
}

// ��������� ��������� ������������
Matrix& Matrix::operator += (const Matrix& matr) {
	if (m != matr.m || n != matr.n) throw MatrExc("������! ������ ������� �� ������������� ���������� (��������/��������� ������ ������ ������ ��������). ");
	for (int i = 0; i < n; i++) {
		for (int j(0); j < n; j++) p[i][j] += matr.p[i][j];
	}
	return *this;
}

Matrix& Matrix::operator -= (const Matrix& matr) {
	if (m != matr.m || n != matr.n) throw MatrExc("������! ������ ������� �� ������������� ���������� (��������/��������� ������ ������ ������ ��������). ");
	for (int i = 0; i < n; i++) {
		for (int j(0); j < n; j++) p[i][j] -= matr.p[i][j];
	}
	return *this;
}

Matrix& Matrix::operator *= (const Matrix& matr) {
	if (n != matr.m) throw MatrExc("������! ������ ������� �� ������������� ���������� (��������� ������, ������ ����� ���������� �������� ������ ����� ���������� ����� ������).  ");
	Matrix res(m, matr.n);
	for (int i = 0; i < n; i++) {            
		for (int j = 0; j < n; j++) {
			res.p[i][j] = 0;
			for (int t = 0; t < n; t++) {
				res.p[i][j] += p[i][t] * matr.p[t][j];
			}
		}
	}
	*this = res;
	return *this;
}

Matrix& Matrix::operator *=(const double& d) {
	for (int i(0); i < m; i++) {
		for (int j(0); j < n; j++) p[i][j] *= d;
	}
	return *this;
}

Matrix& Matrix::operator/=(const double& d) {
	if (d==0) throw MatrExc("������! ������� �� ����. ��������� - �������������. ");
	for (int i(0); i < m; i++) {
		for (int j(0); j < n; j++) p[i][j] /= d;
	}
	return *this;
}

// �������� �������� ����� ���������
Matrix Matrix::operator+(const Matrix& matr) const {
	Matrix a(*this);
	a += matr;
	return a;
}

Matrix Matrix::operator-(const Matrix& matr) const {
	Matrix a(*this);
	a -= matr;
	return a;
}

Matrix Matrix::operator*(const Matrix& matr) const {
	Matrix a(*this);
	a *= matr;
	return a;
}

// �������� �������� ����� �������� � ������
Matrix Matrix::operator*(const double& d) const {
	Matrix a(*this);
	for (int i(0); i < a.m; i++) {
		for (int j(0); j < a.n; j++) a.p[i][j] *= d;
	}
	return a;
}

Matrix operator*(const double& d, const Matrix& matr) {
	Matrix a(matr);
	for (int i(0); i < a.m; i++) {
		for (int j(0); j < a.n; j++) a.p[i][j] *= d;
	}
	return a;
}

Matrix Matrix::operator/(const double& d) const {
	if (d == 0) throw MatrExc("������! ������� �� ����. ��������� - �������������. ");
	Matrix a(*this);
	for (int i(0); i < a.m; i++) {
		for (int j(0); j < a.n; j++) a.p[i][j] /= d;
	}
	return a;
}

//��������� ������
bool Matrix::operator == (const Matrix& matr) const {
	if (m != matr.m || n != matr.n) return false;
	for (int i(0); i < m; i++) {
		for (int j(0); j < n; j++) {
			if (p[i][j] != matr.p[i][j]) return false;
		}
	}
	return true;
}

bool Matrix::operator != (const Matrix& matr) const {
	return !(*this == matr);
}

// ���� � ����� �������
istream& operator>>(istream& cin, Matrix& matr) {
	cout << "������� ������ �������: ";
	cin >> matr.m >> matr.n;
	matr.p = new double* [matr.m];
	for (int i(0); i < matr.m; i++) matr.p[i] = new double[matr.n];
	cout << "������� ������� �������� " << matr.m << "x" << matr.n << ": " << endl;
	for (int i(0); i < matr.m; i++) {
		for (int j(0); j < matr.n; j++) cin >> matr.p[i][j];
	}
	return cin;
}

ostream& operator<<(ostream& cout, const Matrix& matr) {
	if (matr.m == 0 || matr.n == 0) throw MatrExc("������! ���� �� ���������� ������� �������.");
	cout << endl;
	for (int i(0); i < matr.m; i++) {
		for (int j(0); j < matr.n; j++) cout << setw(8) << matr.p[i][j];
		cout << endl;
	}
	return cout;
}