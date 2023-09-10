#include <iostream>
using namespace std;
int main()
{
	setlocale(0, "");
	int n, n1 = 0, x = 2, xd = 1, xtd = 1, xt = 0, xc = 0;
	cout << "¬ведите число n: \n";
	cin >> n;
	cout << "ƒружественные числа: \n";
	while (n1 < n) {
		while (xd <= x / 2) {
			if (x % xd == 0) xt += xd;
			xd++;
		}
		while (xtd <= xt / 2) {
			if (xt % xtd == 0) xc += xtd;
			xtd++;
		}
		if (x == xc && x != xt) {
			cout << x << " и " << xt << "\n";
			n1++;
		}
		x++;
		xt = 0;
		xd = 1;
		xc = 0;
		xtd = 1;
	}
	return 0;
}