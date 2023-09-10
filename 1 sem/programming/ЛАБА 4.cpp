#include <iostream>
#include <ctime>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	int** a;
	int m, n, i, j;
	cout << "Введите размеры массива m (число строк) и n (число столбцов): ";
	cin >> m >> n;
	a = new int* [m];
	for (i = 0; i < m; i++)
		a[i] = new int[n];

	int w;
	cout << "Введите 0, чтобы массив заполнялся вами;\nВведите 1, если хотите, чтобы массив заполнился рандомными числами:";
	cin >> w;
	if (w == 0) {
		cout << "Введите элементы массива: ";
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++)
				cin >> a[i][j];
		}
	}
	else {
		cout << "Введите интервал рандомных чисел, где первое число - начальное значение, второе - крайнее значение интервала (числа целые): ";
		int x, y;
		cin >> x >> y;
		cout << "\n";
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++) {
				a[i][j] = rand() % (y - x) + x;
				cout << a[i][j] << " ";
			}
			cout << endl;
		}
	}
	i = 0;
	j = 0;

	//Сумма элементов в тех строках, которые не содержат нулей
	int sum = 0, nn = n - 1;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			if (a[i][j] == 0) {
				cout << "Сумма " << i + 1 << "-ой строки не посчитана, так как в ней если нулевой элемент\n";
				break;
			}
			else {
				sum += a[i][j];
				if (j == nn) cout << "Сумма " << i + 1 << "-ой строки: " << sum << endl;
			}
		}
		sum = 0;
	}

    //Меняем местами первый столбец с последним, второй с предпоследним, ... .
	int temp;
	nn = n;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n/2; j++) {
			temp = a[i][j];
			a[i][j] = a[i][nn-j-1];
			a[i][nn - j - 1] = temp;
		}
		nn = n;
	}
	cout << "Массив, в котором первый столбец поменялся местами с последним, второй с предпоследним и т.д.: \n";
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
		nn = n;
	}
	for (i = 0; i < m; i++) delete[] a[i];
	delete[] a;
	return 0;
}