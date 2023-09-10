#include<iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	int const max = 400;
	int a[max], i = 0, n, m;
	cout << "Размер массива: \n";
	cin >> n;
	cout << "Массив: \n";
	for (i; i < n; i++) {
		cin >> a[i];
	}
	for (int m = 0; m < n-1; m++) {
		for (i=0; i<n-m-1; i++)
			if (a[i] > a[i + 1]) {
				int temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
			}
	}
	cout << "Итоговый массив: \n";
	for (i=0; i < n; i++) {
		cout << a[i] << " ";
	}
	return 0;
} 