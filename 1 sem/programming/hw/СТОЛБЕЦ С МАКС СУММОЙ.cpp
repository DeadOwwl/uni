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
	int sum = 0, maxi, max=0;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			sum += a[j][i];
		}
		if (sum > max) {
			max = sum;
			maxi = i;
		}
		sum = 0;
	}
	cout << "Максимальная сумма в столбце с номером " << maxi + 1;
	for (i = 0; i < m; i++)
		delete[] a[i];
	delete[] a;
	return 0;
}