#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	setlocale(0, "");
	double a, r;
	cin >> a >> r;
	if ((a * sqrt(2)) <= 2 * r) cout << "������� ���������� � ���������� \n";
	else cout << "������� �� ���������� � ���������� \n";
	return 0;
}