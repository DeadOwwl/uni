#include <iostream>
using namespace std;
int main()
{
	double a1, a2, b1, b2;
	cin >> a1 >> a2;
	cin >> b1 >> b2;
	if ((double)(a1 / a2) > (double)(b1 / b2)) cout << 1;
	if ((double)(a1 / a2) == (double)(b1 / b2)) cout << 0;
	if ((double)(a1 / a2) < (double)(b1 / b2)) cout << -1;
	return 0;
}