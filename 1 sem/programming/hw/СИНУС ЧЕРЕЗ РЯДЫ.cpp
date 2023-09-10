#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	setlocale(0, "");
	double n = 1, x, a, s = 0, E;
	cout << "Введите значение угла в радианах:\n";
	cin >> x;
	a = x; 
	cout << "Введите значение E (E<<0):\n";
	cin >> E;
	while (abs(a) > E) {
		s += a;
		n++;
		a = ((-a) * pow(x, 2)) / (2 * n - 2) / (2 * n - 1);
	}
	cout << "Вычисленное значение sin(x):\n" << s << "\n" << "Значение sin(x) из таблицы C++:\n" << sin(x);
	return 0;
}