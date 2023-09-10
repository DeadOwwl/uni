#include "ComplexCh.h"
#include <iostream>
using namespace std;
complex complex:: operator +(const complex& z1)const {
	complex z2;
	z2.a = a + z1.a;
	z2.b = b + z1.b;
	return z2;
}
complex complex:: operator+(const double& z1)const {
	complex z2;
	z2.a = z1 + a;
	z2.b = b;
	return z2;
}
complex complex:: operator-(const complex& z1)const {
	complex z2;
	z2.a = -1 * z1.a + a;
	z2.b = -1 * z1.b + b;
	return z2;
}
complex complex::operator-(const double& z1) const {
	complex z2;
	z2.a = -1 * z1 + a;
	z2.b = b;
	return z2;
}
complex complex:: operator*(const complex& z1) const {
	complex z2;
	z2.a = a * z1.a - b * z1.b;
	z2.b = a * z1.b + b * z1.a;
	return z2;
}
complex complex:: operator*(const double& z1) const {
	complex z2;
	z2.a = a * z1;
	z2.b = b * z1;
	return z2;
}
complex complex:: operator/(const double& z1) const {
	complex z2;
	if (z1 == 0)
		throw "Делитель равен 0";
	z2.a = a * 1.0 / z1;
	z2.b = b * 1.0 / z1;
	return z2;
}
complex complex:: operator/(const complex& z1) const {
	complex z2;
	if (z1.a == 0 && z1.b == 0)
		throw "Делитель равен 0";
	double d = z1.a * z1.a + z1.b * z1.b;
	z2.a = (a * z1.a + b * z1.b) / d;
	z2.b = (b * z1.a - a * z1.b) / d;
	return z2;
}
complex complex :: operator=(const complex& z1) {
	if (this == &z1)
		return *this;
	a = z1.a;
	b = z1.b;
	return *this;
}
complex complex:: operator=(const double& z1) {
	a = z1;
	b = 0;
	return *this;
}
bool complex :: operator==(const complex& z1) const {
	if ((a * a + b * b) == (z1.a * z1.a + z1.b * z1.b))
		return true;
	else
		return false;
}
bool complex:: operator==(const double& z1) const {
	if (a == z1 && b == 0)
		return true;
	else
		return false;
}
istream& operator>>(istream& s, complex& z1) {
	s >> z1.a >> z1.b;
	return s;
}
ostream& operator<<(ostream& s, complex& z1) {
	if (z1.b < 0)
		s << z1.a << z1.b << "i";
	else
		s << z1.a << "+" << z1.b << "i";
	return s;
}