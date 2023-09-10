#include "ComplexCh.h"
#include <iostream>
using namespace std;
int main() {
	setlocale(0, "");
	try {
		complex z1, z2, z3;
		cout << "¬ведите первое комплексное число:" << endl;
		cin >> z1;
		cout << "¬ведите второе комплексное число:" << endl;
		cin >> z2;
		cout << "z1=" << z1.get_a() << "+" << z1.get_b() << "i" << endl;
		cout << "z2=" << z2.get_a() << "+" << z2.get_b() << "i" << endl;
		z3 = z1 + z2;
		cout << "»х сумма равна " << z3 << endl;
		z3 = z1 - z2;
		cout << "»х разность равна " << z3 << endl;
		z3 = z1 * z2;
		cout << "»х произведение равно " << z3 << endl;
		z3 = z1 / z2;
		cout << "»х частное равно " << z3 << endl;
		if (z1 == z2)
			cout << "¬веденые числа равны" << endl;
		else
			cout << "¬веденные числа не равны" << endl;
	}
	catch (const char* e) {
		cout << e << endl;
	}
    return 0;
}