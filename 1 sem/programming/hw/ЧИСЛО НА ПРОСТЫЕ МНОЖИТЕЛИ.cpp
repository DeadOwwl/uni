#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	setlocale(0, "");
	int a, d, ch = 0, ost;
	cout << "¬ведите число: ";
	cin >> a;
	cout << "=";
	d = 1;
	while (d <= a) {
		ost = a % d;
		if (ost == 0) ch++;
		d++;
	}
	if (ch == 2) cout << a;
	else {
		d = 2;
		while (a > 1) {
			if (a % d == 0) {
				cout << "*" << d;
				a /= d;
			}
			else d++;
		}
	}
	return 0;
}
