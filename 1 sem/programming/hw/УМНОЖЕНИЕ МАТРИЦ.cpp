#include <iostream>
#include <ctime>
using namespace std;
int main()
{
	setlocale(0, "");
	srand(time(NULL));
	int i = 0, m1, m2, n1, n2, j = 0;
	cout << "������� ������� ������: ";
	cin >> m1 >> n1 >> m2 >> n2;
	cout << endl;
	int sum = 0;
	if (m1 != n2 || m2 != n1) cout << "��������� ������ �� ��������� ";
	else {
		int** a1;
		a1 = new int* [m1];
		for (i = 0; i < m1; i++) {
			a1[i] = new int[n1];
		}
		int** a2;
		a2 = new int* [m2];
		for (i = 0; i < m2; i++) {
			a2[i] = new int[n2];
		}
		cout << "������ �������: \n";
		for (i = 0; i < m1; i++) {
			for (j = 0; j < n1; j++) {
		 a1[i][j] = rand();
		 cout << a1[i][j] << " ";
			}
			cout << endl;
		}
		cout << "������ �������: \n";
		for (i = 0; i < m2; i++) {
			for (j = 0; j < n2; j++) {
				a2[i][j] = rand();
				cout << a2[i][j] << " ";
			}
			cout << endl;
		}
		int** a3;
		a3 = new int* [m1];
		for (i = 0; i < m1; i++) {
			a3[i] = new int[n2];
		}

		// ������������ ������
		int l = 0;
		for (i = 0; i < m1; i++) {
			for (j = 0; j < n2; j++) {
				for (l; l <l++) a3[i][j] = a1[i][l] * a2[l][j];
			}
		}
		for (i = 0; i < m1; i++) {
			for (j = 0; j < n2; j++) {
				cout << a3[i][j] << " ";
			}
			cout << endl;
		}
		for (int i = 0; i < m1; i++) {
			delete[] a1[i];
		}
		delete a1;
		for (int i = 0; i < m2; i++) {
			delete[] a2[i];
		}
		delete a2;
		for (int i = 0; i < m2; i++) {
			delete[] a3[i];
		}
		delete a3;
	}
	return 0;
}