#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	setlocale(0, "");
	double a, b, c, x1, x2, D;
	cin >> a >> b >> c;
	if (a == 0)
		if (b == 0)
			if (c == 0)
				cout << "������ - ����� �����\n";
			else cout << "��� �������\n";
		else {
			x1 = x2 = -c / b;
			cout << "������ ��������� " << x1 << "\n";
		}
	else {
		D = pow(b, 2) - 4 * a * c;
		if (D >= 0) {
			if (D = 0) {
				x1 = x2 = (-b / 2) / a;
				cout << "������ ��������� " << x1 << "\n";
			}
			else {
				x1 = ((sqrt(D) - b) / 2) / a;
				x2 = ((-sqrt(D) - b) / 2) / a;
				cout << "����� ��������� " << x1 << x2 << "\n";
			}
		}
		else cout << "��� ������\n";
	}
	return 0;
}