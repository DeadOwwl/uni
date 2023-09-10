#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	setlocale(0, "");
	int m, n, j = 0, i = 0;
	cout << "¬ведите размер матрицы: \n";
	cin >> m >> n;
	int k = 1;
	int** a;
	a = new int* [m];
	for (i = 0; i < m; i++)
		a[i] = new int[n];
	int p = 0;
	for (k; k <= m * n;) {
		i = p;
		j = p;
		for (j; j < n; j++) {
			a[i][j] = k;
			k++;
		}
		i++;
		j = p;
		for (i; i < m; i++) {
			a[i][j] = k;
			k++;
		}
		p++;
	}
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			cout << setw(4) << a[i][j] << " ";
		}
		cout << endl;
	}	
	return 0;
}