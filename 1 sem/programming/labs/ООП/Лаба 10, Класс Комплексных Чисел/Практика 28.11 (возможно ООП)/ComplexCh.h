#include <cmath>
#include <string>
#include <iostream>
using namespace std;
#ifndef __Complex_defined__
#define __Complex_defined__
class complex {
	double a, b;
public:
	complex() : a(0), b(0) {};
	complex(double a1, double b1) { a = a1; b = b1; }
	double get_a() const { return a; }
	double get_b() const { return b; }
	void set_a(double& a1) { a = a1; }
	void set_b(double& b1) { b = b1; }
	complex operator +(const complex& z1)const;
	complex operator + (const double& z1)const;
	complex operator -(const complex& z1)const;
	complex operator -(const double& z1)const;
	complex operator * (const complex& z1)const;
	complex operator *(const double& z1)const;
	complex operator / (const complex& z1)const;
	complex operator / (const double& z1)const;
	complex operator = (const complex& z1);
	complex operator = (const double& z1);
	bool operator == (const complex& z1) const;
	bool operator == (const double& z1)const;
	friend istream& operator>>(istream& s, complex& z1);
	friend ostream& operator<<(ostream& s, complex& z2);
};
#endif 