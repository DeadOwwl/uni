#include <iostream>
using namespace std;
int main()
{
	setlocale(0, "");
	double a, b, c, x, y, z;
	if ((a * b * c) <= (x * y * z)) cout << "Коробка поместится в посылку\n";
	else cout << "Коробка не поместится в посылку\n";
	return 0;
}