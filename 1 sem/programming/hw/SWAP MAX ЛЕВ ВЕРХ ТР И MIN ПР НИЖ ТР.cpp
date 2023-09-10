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
		a[i] = new int[n];
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			a[i][j] = rand() % (201) - 100;
			cout << setw(4) << a[i][j] << " ";
		}
		cout << endl;
	}
	int maxi, maxj, mini, minj, max, min;
	max = a[0][0];
	for (i = 0; i < m; i++) {
		for (j = 0; j < n-i; j++) {
			if (max < a[i][j]) {
				max = a[i][j];
				maxi = i;
				maxj = j;
			}
		}
		cout << endl;
	}
	min = a[0][0];
	for (i = m - 1; i >= 0; i--) {
		for (j = n-i; j < n; j++) {
			if (min > a[i][j]) {
				min = a[i][j];
				mini = i;
				minj = j;
			}
		}
		cout << endl;
	}
	int temp;
	temp = a[maxi][maxj];
	a[maxi][maxj] = a[mini][minj];
	a[mini][minj] = temp;
	cout << "После смены мест максимального и минимального:\n";
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