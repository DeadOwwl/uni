#include "Matrix.h"
#include "MatrExc.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>

using namespace std;

int main() {
	setlocale(0, "");\
	try {
		Matrix A, B, Y;
		cin >> A >> B;
		Y = (A + B) * (A - B) / 2;
		cout << "���������: " << Y << endl;
		//M1Check = M1, M2Check = M2;
		////+=
		//M1Check += M2Check;
		//cout << "��������� �������� �������� �� �������: " <<  M1Check;
		//M1Check = M1, M2Check = M2;
		////-=
		//M1Check -= M2Check;
		//cout << "��������� �������� ��������� �� �������: " << M1Check;
		//M1Check = M1, M2Check = M2;
		////*=
		//M1Check *= M2Check;
		//cout << "��������� �������� ��������� �� �������: " << M1Check;
		//M1Check = M1, M2Check = M2;
		////*=
		//M1Check *= 3.5;
		//cout << "��������� �������� ��������� �� �����: " << M1Check;
		//M1Check = M1, M2Check = M2;
		/////=
		//M1Check /= 3.5;
		//cout << "��������� �������� ������� �� �����: " << M1Check;
		//M1Check = M1, M2Check = M2;
		//// +
		//cout << "����� ������:" << M1Check + M2Check;
		//M1Check = M1, M2Check = M2;
		//// -
		//cout << "�������� ������:" << M1Check - M2Check;
		//M1Check = M1, M2Check = M2;
		//// *
		//cout << "������������ ������:" << M1Check * M2Check;
		//M1Check = M1, M2Check = M2;
		//// *
		//cout << "������������ ������� �� �����:" << M1Check * 3.5;
		//M1Check = M1, M2Check = M2;
		//// *
		//cout << "������������ ����� �� �������:" <<  3.5 * M1Check;
		//M1Check = M1, M2Check = M2;
		//// /
		//cout << "������� ������� �� �����" << M1Check / 3.5;
		//M1Check = M1, M2Check = M2;
		//// ==
		//if (M1 == M1Check) cout << "������� 1 � 1 �����\n";
		//// !=
		//if (M1 != M2) cout <<"������� 1 � 2 �� �����\n";
	}
	catch (MatrExc& err) {
		cout << err.what() << endl;
	}
	return 0;
}