#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
int main()
{
	setlocale(0, "");
	srand(time(NULL));
	cout << "Размеры матрицы (строки и столбцы): ";
	int m, n;
	cin >> m >> n;
	int a[100][100];
	int i, j, sum = 0;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			a[i][j] = rand()%201 - 100;
			cout << setw(4)<< a[i][j] << " ";
		}
		cout << endl;
	}
	for (i = 0; i < m; i++) {
		for (j=i; j<n; j++)
			if (a[i][j]>=0) sum +=a[i][j];
	}
	cout << "Сумма правого верхнего треугольница матрицы: " << sum;
	return 0;
}