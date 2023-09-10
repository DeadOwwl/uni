#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int m, n, i, j;
	cout << "Введите размер массива: ";
	cin >> m >> n;
	int** a;
	a = new int* [m];
	for (i = 0; i < m; i++)
		a[i] = new int[n];
	cout << "Первоначальный массив: \n";
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			a[i][j] = rand() % 201 - 100;
			cout << setw(5) << a[i][j] << " ";
		}
		cout << endl;
	}
	for (int p = 0; p < m - 1; p++) {
		for (i = 0; i < m - 1; i++) {
			if (a[i + 1][0] < a[i][0]) {
				for (j = 0; j < n; j++) {
					int temp;
					temp = a[i][j];
					a[i][j] = a[i + 1][j];
					a[i + 1][j] = temp;
				}
			}
		}
	}
	cout << "Отсортированный массив: \n";
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			cout << setw(5) << a[i][j] << " ";
		}
		cout << endl;
	}
	for (i = 0; i < m; i++)
		delete[] a[i];
	delete[] a;
	return 0;
}