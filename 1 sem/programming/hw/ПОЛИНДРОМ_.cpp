#include <iostream>
using namespace std;
int main()
{
	setlocale(0, "");
	int a, b, c;
	cin >> a;
	c=a;
	b = 0;
	do {
		b = a % 10 + 10*b;
		a = a / 10;
	} while (a != 0);
	if (c == b) cout << "����� - ���������\n";
	else cout << "����� �� ���������\n";
	return 0;
}