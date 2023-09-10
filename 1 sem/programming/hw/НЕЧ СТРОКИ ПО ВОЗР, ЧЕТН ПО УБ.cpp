#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;
int main()
{
	setlocale(0, "");
	srand(time(NULL));
	int m, n, i, j;
	cout << "Введите количество строк и количество столбцов матрицы: ";
	cin >> m >> n;
	int** a;
	a = new int* [m];
	for (i = 0; i < m; i++)
		a[i] = new int[n];
	cout << "Первоначальная матрица: \n";
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			a[i][j] = rand() % (1000) - 500;
			cout << setw(5)<< a[i][j] << " ";
		}
		cout << endl;
	}
	int k;
	for (i=0;i<m;i++){
		if (i % 2 == 0) {
			for (j = 1; j < n; j++) {
				for (k = j; k > 0 && a[i][k - 1] > a[i][k]; k--) {
					int temp = a[i][k - 1];
					a[i][k - 1] = a[i][k];
					a[i][k] = temp;
				}
			}
		}
	}
	for (i = 0; i < m; i++) {
		if (i % 2 == 1) {
			for (j = 1; j < n; j++) {
				for (k = j; k > 0 && a[i][k - 1] <a[i][k]; k--) {
					int temp = a[i][k - 1];
					a[i][k - 1] = a[i][k];
					a[i][k] = temp;
				}
			}
		}
	}
	cout << "Матрица с отсортированными элементами (в четных рядах по убыванию, в нечетных по возрастанию): \n";
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			cout << setw(5) << a[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}