#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	setlocale(0, "");
	int a, b, c, x, y, z;
	cin >> a >> b >> c >> x >> y >> z;
	if ((a<=x && b<=y && c<=z) ||
		(a <= x && b <= z && c <= y) || 
		(a <= y && b <= x && c <= z) || 
		(a <= y && b <= z && c <=x )|| (a <= z && b <= x && c <= y) || 
		(a <= z && b <= y && c <= x)) cout<<"Коробка поместится в посылку\n";
	else cout<<"Коробка не поместится в посылку\n";
	return 0;
}