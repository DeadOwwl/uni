#include <iostream>
#include <cmath>
using namespace std;
double integral_trapecija (double a, double b, double e, double (*function)(double)){
	int z;
	if (a==b) return 0.0;
	else {
		if (a > b) {
			double temp;
			temp = a;
			a = b;
			b = temp;
			z = -1;
		}
		else {
			z = 1;
		}
	}
	double s0 = 0, s1 = 0;
	int n = 1;
	s1 = (b - a) * 0.5 * (function(a) + function(b));
	do {
		n *= 2;
		s0 = s1;
		s1 =  0;
		double ps = (b - a) / n;
		for (int i = 0; i < n; i++) {
			s1 += function(a + ps * i);
		}
		s1 = ps * (s1 + ((function(a) + function(b)) / 2));
	} while (fabs(s1 - s0) > e);
	return s1 * z;
}
double parabola(double x) {
	return x * x;
}
double sin(double x) {
	return sin(x)*sin(x);
}
int main()
{
	setlocale(LC_ALL, "RUS");
	double E;
	cout << "¬ведите точность вычислений (меньше 1, больше 0): ";
	cin >> E;
	double sum=0;
	sum = integral_trapecija(1.0, 5.0, E, parabola) + integral_trapecija(0.0, 1.5, E, sin) + integral_trapecija(0.5, 3.1415, E, cos);
	cout << sum;
	return 0;
}