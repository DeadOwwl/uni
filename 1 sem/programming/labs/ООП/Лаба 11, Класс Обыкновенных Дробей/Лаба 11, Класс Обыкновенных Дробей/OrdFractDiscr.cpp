#include "OrdFract.h"
#include "FractExc.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

int OrdFract::SCF(int a, int b) {
	if (b == 0) return a;
	else return SCF(b, a % b);
}

void OrdFract::ToCanonical() {
	int scf = SCF(abs(n), d);
	n /= scf;
	d /= scf;
}

int OrdFract::next_ID = 1;                       //ID_�������
//int OrdFract::GetID() const { return ID; }

OrdFract::OrdFract(int N, int D): ID(next_ID++) {
	if (D < 0) throw FractExc("���� ������ ��������� � ���������, ����������� �����������.");
	if (D == 0) throw FractExc ("����������� ����� �� ����� ���� ����� 0.");
	n = N;
	d = D;
	ToCanonical();
}

OrdFract& OrdFract::operator ++ () {            //���������� +
	n += d;
	//ToCanonical();
	return *this;
}


OrdFract OrdFract::operator ++ (int) {        //����������� +
	OrdFract t(*this);
	n += d;
	//ToCanonical();
	return t;
}


OrdFract& OrdFract::operator--() {              //���������� -
	n -= d;
	//ToCanonical();
	return *this;
}


OrdFract OrdFract::operator--(int) {          //����������� -
	OrdFract b(*this);
	n -= d;
	//ToCanonical();
	return b;
}


OrdFract& OrdFract::operator = (const OrdFract& a) {    //������������
	if (this != &a) {
		n = a.GetN();
		d = a.GetD();
	}
	return *this;
}


OrdFract& OrdFract::operator+=(const OrdFract& a) {     //�������� � ������ � ������������
	n = n * a.d + d * a.n;
	d = d * a.d;
	ToCanonical();
	return *this;
}

OrdFract& OrdFract::operator-=(const OrdFract& a) {     //��������� ����� � ������������
	n = n * a.d - d * a.n;
	d = d * a.d;
	ToCanonical ();
	return *this;
}

OrdFract& OrdFract::operator*=(const OrdFract& a) {     //��������� �� ����� � ������������
	n = n * a.n;
	d = d * a.d;
	ToCanonical();
	return *this;
}

OrdFract& OrdFract::operator/=(const OrdFract& a) {     //������� �� ����� � ������������
	if (a.n == 0) throw FractExc("������� �� 0.");
	n = n * a.d;
	d = d * a.n;
	ToCanonical();
	return *this;
}

OrdFract& OrdFract::operator+=(const int &a) {                 //�������� � ������ � ������������
	n += a * d;
	return *this;
}

OrdFract& OrdFract::operator-=(const int &a) {                //��������� ����� � ������������
	n -= a * d;
	return *this;
}

OrdFract& OrdFract::operator*=(const int& a) {                 //��������� �� ����� � ������������
	n *= a;
	ToCanonical();
	return *this;
}

OrdFract& OrdFract::operator/=(const int& a) {                 //������� �� ����� � ������������
	d *= a;
	ToCanonical();
	return *this;
}
 

OrdFract OrdFract::operator+(const OrdFract& a) const {         // ����� � ������
	OrdFract b(*this);
	b += a;
	return b;
}

OrdFract OrdFract::operator+(const int &a) const {                     // ����� � ������
	OrdFract b(*this);
	b.n += a * d;
	return b;
}

OrdFract operator+(const int& a, const OrdFract& b) {                  // ����� � ������
	OrdFract t(b);
	t +=  a;
	return t;
}

OrdFract OrdFract::operator-(const OrdFract& a) const {         // ����� ����� �����
	OrdFract b(*this);
	b -= a;
	return b;
}

OrdFract OrdFract::operator-(const int& a) const {                     // ����� ����� �����
	OrdFract b(*this);
	b.n -= a * b.d;
	return b;
}

OrdFract operator-(const int& a, const OrdFract& t) {                  // ����� ����� �����
	OrdFract b(a * t.d, t.d);
	b = b - t;
	return b;
}

OrdFract OrdFract::operator*(const OrdFract& a) const {         // ����� �� �����
	OrdFract b(*this);
	b *= a;
	return b;
}

OrdFract OrdFract::operator*(const int& a) const {                     // ����� �� �����
	OrdFract t(*this);
	t.n *= a;
	t.ToCanonical();
	return t;
}

OrdFract operator*(const int& a, const OrdFract& t) {                  // ����� �� �����
	OrdFract b(t);
	b = b * a;
	return b;
}

OrdFract OrdFract::operator/(const OrdFract& a) const {         // ������� ����� �� �����
	//if (a == 0/1) throw FractExc("������� �� ����");
	OrdFract b(*this);
	b /= a;
	return b;
}

OrdFract OrdFract::operator/(const int& a) const {                     // ������� ����� �� �����
	OrdFract b(*this);
	if (a == 0) throw FractExc("������� �� ����");
	b.d *= a;
	b.ToCanonical();
	return b;
}

OrdFract operator/(const int& a, const OrdFract& t) {                  // ������� ����� �� �����
	OrdFract b(a * t.d, t.n);
	b.ToCanonical();
	return b;
}


bool OrdFract::operator==(const OrdFract& a) const { //��������� ==
	return ((n == a.n) && (d == a.d));
}                      

bool OrdFract::operator!=(const OrdFract& a) const { //��������� !=
	return ((n != a.n) || (d != a.d));
}                      

bool OrdFract::operator>(const OrdFract& a) const {//��������� >
	return ((double)n / d > (double)a.n / a.d);
}               

bool OrdFract::operator>=(const OrdFract& a) const {//��������� >=
	return ((double)n / d >= (double)a.n / a.d);
}              

bool OrdFract::operator<(const OrdFract& a) const {//��������� <
	return ((double)n / d < (double)a.n / a.d);
}                

bool OrdFract::operator<=(const OrdFract& a) const {//��������� <=
	return ((double)n / d <= (double)a.n / a.d);
}               


istream& operator>>(istream& cin, OrdFract& a) {                //����
	char c;
	int n(0), d(1);
	cin >> n;
	a.n = n;
	c = getchar();
	if (c =='/')
		cin >> d;
	else cin.putback(c);
	a=OrdFract(n,d);
	return cin;
}

ostream& operator<<(ostream& cout, const OrdFract& a) {         //�����
	cout << a.n;
	if (a.d != 1) cout << '/' << a.d;
	return cout;
}
