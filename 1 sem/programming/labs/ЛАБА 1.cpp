#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	setlocale(0, "");
	double sum, a, E, x, z;
	int n;
	cout << "������� x �� -1 �� 1: \n";
	cin >> x;
	cout << "������� E (��������): \n";
	cin >> E;
	sum = 1;
	n = 1;
	a = 0.5;
	while (fabs(a) > E) {
		n++;
		z = 1;
		if (n == 2) z = 2;
		a = (-a)*z*x*(n+1)/(n-1);
		sum += a;
	}
	cout << "��������� ����� �������: " << sum << "\n";
	cout << "��������� ��������: " << pow((1 + x), -3);
	return 0;
}