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

int OrdFract::next_ID = 1;                       //ID_функции
//int OrdFract::GetID() const { return ID; }

OrdFract::OrdFract(int N, int D): ID(next_ID++) {
	if (D < 0) throw FractExc("Знак должен храниться в числителе, знаменатель положителен.");
	if (D == 0) throw FractExc ("Знаменатель дроби не может быть равен 0.");
	n = N;
	d = D;
	ToCanonical();
}

OrdFract& OrdFract::operator ++ () {            //префиксный +
	n += d;
	//ToCanonical();
	return *this;
}


OrdFract OrdFract::operator ++ (int) {        //постфиксный +
	OrdFract t(*this);
	n += d;
	//ToCanonical();
	return t;
}


OrdFract& OrdFract::operator--() {              //префиксный -
	n -= d;
	//ToCanonical();
	return *this;
}


OrdFract OrdFract::operator--(int) {          //постфиксный -
	OrdFract b(*this);
	n -= d;
	//ToCanonical();
	return b;
}


OrdFract& OrdFract::operator = (const OrdFract& a) {    //Присваивание
	if (this != &a) {
		n = a.GetN();
		d = a.GetD();
	}
	return *this;
}


OrdFract& OrdFract::operator+=(const OrdFract& a) {     //сложение с дробью и присваивание
	n = n * a.d + d * a.n;
	d = d * a.d;
	ToCanonical();
	return *this;
}

OrdFract& OrdFract::operator-=(const OrdFract& a) {     //вычитание дроби и присваивание
	n = n * a.d - d * a.n;
	d = d * a.d;
	ToCanonical ();
	return *this;
}

OrdFract& OrdFract::operator*=(const OrdFract& a) {     //умножение на дробь и присваивание
	n = n * a.n;
	d = d * a.d;
	ToCanonical();
	return *this;
}

OrdFract& OrdFract::operator/=(const OrdFract& a) {     //деление на дробь и присваивание
	if (a.n == 0) throw FractExc("Деление на 0.");
	n = n * a.d;
	d = d * a.n;
	ToCanonical();
	return *this;
}

OrdFract& OrdFract::operator+=(const int &a) {                 //сложение с числом и присваивание
	n += a * d;
	return *this;
}

OrdFract& OrdFract::operator-=(const int &a) {                //вычитание числа и присваивание
	n -= a * d;
	return *this;
}

OrdFract& OrdFract::operator*=(const int& a) {                 //умножение на число и присваивание
	n *= a;
	ToCanonical();
	return *this;
}

OrdFract& OrdFract::operator/=(const int& a) {                 //деление на число и присваивание
	d *= a;
	ToCanonical();
	return *this;
}
 

OrdFract OrdFract::operator+(const OrdFract& a) const {         // дробь с дробью
	OrdFract b(*this);
	b += a;
	return b;
}

OrdFract OrdFract::operator+(const int &a) const {                     // дробь с числом
	OrdFract b(*this);
	b.n += a * d;
	return b;
}

OrdFract operator+(const int& a, const OrdFract& b) {                  // число с дробью
	OrdFract t(b);
	t +=  a;
	return t;
}

OrdFract OrdFract::operator-(const OrdFract& a) const {         // дробь минус дробь
	OrdFract b(*this);
	b -= a;
	return b;
}

OrdFract OrdFract::operator-(const int& a) const {                     // дробь минус число
	OrdFract b(*this);
	b.n -= a * b.d;
	return b;
}

OrdFract operator-(const int& a, const OrdFract& t) {                  // число минус дробь
	OrdFract b(a * t.d, t.d);
	b = b - t;
	return b;
}

OrdFract OrdFract::operator*(const OrdFract& a) const {         // дробь на дробь
	OrdFract b(*this);
	b *= a;
	return b;
}

OrdFract OrdFract::operator*(const int& a) const {                     // дробь на число
	OrdFract t(*this);
	t.n *= a;
	t.ToCanonical();
	return t;
}

OrdFract operator*(const int& a, const OrdFract& t) {                  // число на дробь
	OrdFract b(t);
	b = b * a;
	return b;
}

OrdFract OrdFract::operator/(const OrdFract& a) const {         // деление дробь на дробь
	//if (a == 0/1) throw FractExc("Деление на ноль");
	OrdFract b(*this);
	b /= a;
	return b;
}

OrdFract OrdFract::operator/(const int& a) const {                     // деление дробь на число
	OrdFract b(*this);
	if (a == 0) throw FractExc("Деление на ноль");
	b.d *= a;
	b.ToCanonical();
	return b;
}

OrdFract operator/(const int& a, const OrdFract& t) {                  // деление число на дробь
	OrdFract b(a * t.d, t.n);
	b.ToCanonical();
	return b;
}


bool OrdFract::operator==(const OrdFract& a) const { //сравнение ==
	return ((n == a.n) && (d == a.d));
}                      

bool OrdFract::operator!=(const OrdFract& a) const { //сравнение !=
	return ((n != a.n) || (d != a.d));
}                      

bool OrdFract::operator>(const OrdFract& a) const {//сравнение >
	return ((double)n / d > (double)a.n / a.d);
}               

bool OrdFract::operator>=(const OrdFract& a) const {//сравнение >=
	return ((double)n / d >= (double)a.n / a.d);
}              

bool OrdFract::operator<(const OrdFract& a) const {//Сравнение <
	return ((double)n / d < (double)a.n / a.d);
}                

bool OrdFract::operator<=(const OrdFract& a) const {//Сравнение <=
	return ((double)n / d <= (double)a.n / a.d);
}               


istream& operator>>(istream& cin, OrdFract& a) {                //ввод
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

ostream& operator<<(ostream& cout, const OrdFract& a) {         //вывод
	cout << a.n;
	if (a.d != 1) cout << '/' << a.d;
	return cout;
}
