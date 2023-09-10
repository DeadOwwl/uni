#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int const max = 500;
	int a[max], i, n;
	cout << "Введите размер массива: ";
	cin >> n;
	cout << endl;
	for (i = 0; i < n; i++) {
		a[i] = rand();
		cout << a[i] << " ";
	}
	int m = n, maxa, mina;
	maxa = a[0];
	mina = a[0];
	int mini, maxi;
	for (i=0; i<n;i++){
		if (a[i] > maxa) { 
			maxa = a[i];
			maxi = i;
		}
		if (a[i] < mina) { 
			mina = a[i];
			mini = i;
		}
	}
	int sum = 0;
	if (abs(maxi - mini) > 1) {
		if (maxi > mini) {
			for (int k = mini+1; k < maxi; k++)	sum += a[k];
		}
		else {
			for (int k = maxi + 1; k < mini; k++) sum += a[k];
		}
		cout << "Сумма элементов между максимальным и минимальным элементами равна " << sum;
	}
	else {
		if (abs(maxi - mini) == 1) cout << "Максимальный и минимальный элементы совпадают";
		else cout << "Массив состоит из одинаковых элементов";
	}
	return 0;
}