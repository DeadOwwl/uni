#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	setlocale(0, "");
	double a, r;
	cin >> a >> r;
	if ((a * sqrt(2)) <= 2 * r) cout << " вадрат поместитс€ в окружность \n";
	else cout << " вадрат не поместитс€ в окружность \n";
	return 0;
}