#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	setlocale(0, "");
	double a, x, y;
	cin >> a >> x >> y;
	if ((y < a) && (y >= 0) && (x <= abs(a))) ||
	   ((y <= 3 * a) && ((pow((y - a), 2) + pow(x, 2)) <= 4 * pow(a, 2)) cout << "Точка принадлежит грибу\n";
	else cout << "Точка не принадлежит грибу\n";	
	return 0;
}