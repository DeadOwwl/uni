#include <iostream>
using namespace std;
int main()
{
	setlocale(0, "");
	int a, i, ost, d;
	cin >> a; 
	i = 1;
	d = 0;
	do {
		ost = a % i;
		if (ost == 0) d++;
		i++; 
	} while (i <= a);
	if (d == 2) cout << "��������� ����� - �������\n";
	else cout << "��������� ����� �� �������� �������\n";
	return 0;
}