#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int m, n, i, j;
	cout << "Введите размер матрицы: ";
	cin >> m;
	n = m;
	int** a;
	a = new int* [m];
	for (i = 0; i < m; i++)
		a[i] = new int [n];
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			a[i][j] = rand() % (201) - 100;
			cout << setw(4) << a[i][j] << " ";
		}
		cout << endl;
	}
	for (i = 0; i < m; i++) {
		for (j = i+1; j < n; j++) {
			int temp = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = temp;
		}
	}
	cout << "Транспонированная матрица:\n";
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			cout << setw(4) << a[i][j] << " ";
		}
		cout << endl;
	}
	for (i = 0; i < m; i++)
		delete[] a[i];
	delete[] a;
	return 0;
}