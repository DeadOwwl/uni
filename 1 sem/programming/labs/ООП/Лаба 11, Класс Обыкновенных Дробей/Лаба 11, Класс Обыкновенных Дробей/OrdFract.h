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
	void SetdD(int& D) { if (D == 0) throw "����������� ����� �� ����� ���� ����� 0."; d = D; ToCanonical(); }
	OrdFract operator -() const {return OrdFract(-n, d); } //������� ������������ �����
	OrdFract operator !() const { return OrdFract(d, n); } // ������� �������� �����
	OrdFract& operator ++(); // ���������� +
	OrdFract operator ++(int); // ����������� +
	OrdFract& operator --(); // ���������� -
	OrdFract operator --(int); // ����������� -
	OrdFract& operator =(const OrdFract&); // ������������
	OrdFract& operator += (const OrdFract&); // ������������ ����� � �����
	OrdFract& operator -= (const OrdFract&);
	OrdFract& operator *= (const OrdFract&);
	OrdFract& operator /= (const OrdFract&);
	OrdFract& operator += (const int&); // ������������ ����� � ������
	OrdFract& operator -= (const int&);
	OrdFract& operator *= (const int&);
	OrdFract& operator /= (const int&);
	OrdFract operator +(const OrdFract&) const; //�������� 
	OrdFract operator +(const int&) const;
	friend OrdFract operator +(const int&, const OrdFract&);
	OrdFract operator -(const OrdFract&) const; //���������
	OrdFract operator -(const int&) const;
	friend OrdFract operator -(const int&, const OrdFract&);
	OrdFract operator *(const OrdFract&) const; //���������
	OrdFract operator *(const int&) const;
	friend OrdFract operator *(const int&, const OrdFract&);
	OrdFract operator /(const OrdFract&) const;//�������
	OrdFract operator /(const int&) const;
	friend OrdFract operator /(const int&, const OrdFract&);
	bool operator ==(const OrdFract&) const; //���������
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