#include <iostream>
#include <cmath>
using namespace std;

long long int fact(int n) {
	long long int result = 1;

	if (n == 0) return 1;
	for (int i = 1; i <= n; i++) {
		result *= i;
	}
	return result;
}

int main()
{
	setlocale(0, "");
	double num = 0, x, E, result = 0;
	cout << "������� �������� ���� (� ��������):\n";
	cin >> x;
	cout << "������� �������� � (�>>0):\n";
	cin >> E;


	while (true) {
		if (abs(pow(-1, num / 2 + 1) * pow(x, num) / fact(num)) > E) {
			result += pow(-1, num / 2) * pow(x, num) / fact(num);
			num += 2;
		}
		else {
			break;
		}
	}

	cout << "����������� �������� cos(x):\n" << result << "\n" << "�������� cos(x) �� ���������� C++:" << cos(x);
	return 0;
}