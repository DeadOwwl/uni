#include <iostream>
#include <ctime>
using namespace std;
int main()
{
	setlocale(0, "");
	srand(time(NULL));
	int const max = 1000;
	int a[max], i, n;
	cout << "¬ведите размер массива: ";
	cin >> n;
	cout << endl;
	cout << "¬ведите отсортированный массив: ";
	for (i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << endl;

	int p;
	cout << "¬ведите число дл€ вставки в массив: ";
	cin >> p;
	cout << endl;
	if (a[1] < a[n]) {
		for (i = 0; i < n; i++) {
			if (a[i + 1] > p && a[i] < p) {
				for (int k = n + 1; k > i; k--) a[k] = a[k - 1];
				a[i] = p;
			}
		}
	}
	else {

	}
	
	for (i = 0; i < n + 1; i++) {
		cout << a[i] << " ";
	}
	return 0;
}