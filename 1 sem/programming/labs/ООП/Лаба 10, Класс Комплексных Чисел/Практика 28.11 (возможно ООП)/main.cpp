#include "ComplexCh.h"
#include <iostream>
using namespace std;
int main() {
	setlocale(0, "");
	try {
		complex z1, z2, z3;
		cout << "������� ������ ����������� �����:" << endl;
		cin >> z1;
		cout << "������� ������ ����������� �����:" << endl;
		cin >> z2;
		cout << "z1=" << z1.get_a() << "+" << z1.get_b() << "i" << endl;
		cout << "z2=" << z2.get_a() << "+" << z2.get_b() << "i" << endl;
		z3 = z1 + z2;
		cout << "�� ����� ����� " << z3 << endl;
		z3 = z1 - z2;
		cout << "�� �������� ����� " << z3 << endl;
		z3 = z1 * z2;
		cout << "�� ������������ ����� " << z3 << endl;
		z3 = z1 / z2;
		cout << "�� ������� ����� " << z3 << endl;
		if (z1 == z2)
			cout << "�������� ����� �����" << endl;
		else
			cout << "��������� ����� �� �����" << endl;
	}
	catch (const char* e) {
		cout << e << endl;
	}
    return 0;
}