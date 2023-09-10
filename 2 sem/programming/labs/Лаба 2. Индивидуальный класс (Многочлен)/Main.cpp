#include "Polynomial.h"

int main()
{
	setlocale(0, "");
	Polynomial F1, F2;
	cin >> F1 >> F2;
	cout << "f1(x)=" << F1 << "f2(x)=" << F2;
	Polynomial F3;
	F3 = F1 + F2;
	cout << "f1(x)+f2(x)=" << F3;
	F3 = F1 - F2;
	cout << "f1(x)-f2(x)=" << F3;
	F3 = F1 * F2;
	cout << "f1(x)*f2(x)=" << F3;
	cout << "f1'(x)=" << F1.FirstDerivative();
	cout << "f2'(x)=" << F2.FirstDerivative();
	cout << "f1(10)=" << F1.ValueCalculating(10) << endl;
	cout << "f(10)=" << F2.ValueCalculating(10) << endl;
	F1 = F2;
	cout << F1;
	return 0;
}