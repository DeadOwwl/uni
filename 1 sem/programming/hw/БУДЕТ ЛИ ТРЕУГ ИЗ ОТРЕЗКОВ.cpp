#include <iostream>
#include <cmath>
using namespace std;

bool prov(double m, double  n, double k) {
	if ((m > fabs(n - k)) && (m < (n + k)) &&
		(n > fabs(m - k)) && (n < (m + k)) &&
		(k > fabs(n - m)) && (k < (n + m)))
		return true;
	else return false;
}

double pl(double k, double l, double t) {
	double s, p;
	p = (k + l + t) / 2;
	s = pow(p*(p-k)*(p-l)*(p-t), 0.5);
	return s;
}

int main()
{
	setlocale(LC_ALL, "rus");
	double a, b, c, d;
	cout << "Введите отрезки a, b, c, d: ";
	cin >> a >> b >> c >> d;

	switch (prov(a, b, c))
	{
	case 1:
		cout << "Можно построить треугольник из отрезков a, b, c;\nЕго площадь: ";
		cout << pl(a, b, c);
	case 0:
		break;
	}

	switch (prov(a, b, d))
	{
	case 1:
		cout << "Можно построить треугольник из отрезков a, b, d;\nЕго площадь: ";
		cout << pl(a, b, d);
	case 0:
		break;
	}

	switch (prov(d, b, c))
	{
	case 1:
		cout << "Можно построить треугольник из отрезков a, b, c;\nЕго площадь: ";
		cout << pl(d, b, c);
	case 0:
		break;
	}

	switch (prov(a, d, c))
	{
	case 1:
		cout << "Можно построить треугольник из отрезков a, d, c;\nЕго площадь: ";
		cout << pl(a, d, c);
	case 0:
		break;
	}
	return 0;
}
