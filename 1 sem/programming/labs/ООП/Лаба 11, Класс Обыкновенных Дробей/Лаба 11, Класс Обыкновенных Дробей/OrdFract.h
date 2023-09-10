#ifndef __OrdFract_defined__
#define __OrdFract_defined__

#include <iostream>
#include <fstream>
#include <cmath> 
#include <cstdio>

using namespace std;

class OrdFract{
private: 
	int n, d;
	int SCF(int, int);
	void ToCanonical();
	static int next_ID;
	const int ID;
public:
	OrdFract(int N, int D);
	OrdFract() : n(0), d(1), ID(next_ID++) {};
	int GetN() const { return n; }
	int GetD() const { return d; }
	//ID
	int GetID() { return ID; };
	void SetN(int& N) { n = N; ToCanonical(); }
	void SetdD(int& D) { if (D == 0) throw "Знаменатель дроби не может быть равен 0."; d = D; ToCanonical(); }
	OrdFract operator -() const {return OrdFract(-n, d); } //Создаем отрицательую дробь
	OrdFract operator !() const { return OrdFract(d, n); } // Создаем обратную дрось
	OrdFract& operator ++(); // Префиксный +
	OrdFract operator ++(int); // Постфиксный +
	OrdFract& operator --(); // Префиксный -
	OrdFract operator --(int); // Постфиксный -
	OrdFract& operator =(const OrdFract&); // Присваивание
	OrdFract& operator += (const OrdFract&); // Присваивание дроби и дроби
	OrdFract& operator -= (const OrdFract&);
	OrdFract& operator *= (const OrdFract&);
	OrdFract& operator /= (const OrdFract&);
	OrdFract& operator += (const int&); // Присваивание дроби с числом
	OrdFract& operator -= (const int&);
	OrdFract& operator *= (const int&);
	OrdFract& operator /= (const int&);
	OrdFract operator +(const OrdFract&) const; //Сложение 
	OrdFract operator +(const int&) const;
	friend OrdFract operator +(const int&, const OrdFract&);
	OrdFract operator -(const OrdFract&) const; //Вычитание
	OrdFract operator -(const int&) const;
	friend OrdFract operator -(const int&, const OrdFract&);
	OrdFract operator *(const OrdFract&) const; //Умножение
	OrdFract operator *(const int&) const;
	friend OrdFract operator *(const int&, const OrdFract&);
	OrdFract operator /(const OrdFract&) const;//Деление
	OrdFract operator /(const int&) const;
	friend OrdFract operator /(const int&, const OrdFract&);
	bool operator ==(const OrdFract&) const; //Сравнение
	bool operator >(const OrdFract&) const;
	bool operator >=(const OrdFract&) const;
	bool operator <(const OrdFract&) const;
	bool operator <=(const OrdFract&) const;
	bool operator !=(const OrdFract&) const;
	friend istream& operator >>(istream&, OrdFract&);
	friend ostream& operator <<(ostream&, const OrdFract&);
	operator double() { return ((double)n / d); }
};

#endif