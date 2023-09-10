#include <iostream>
#include <ctime>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int const m = 100;
	int a[m], n, i, max, min, p, maxn, minn, x, y;
	cin >> n >> x >> y;
	for (i = 0; i < n; i++) {
		a[i] = rand()%(y-x+1)+x;
		cout << a[i] <<"\n";
	}
	max = a[0];
	min = a[0];
	for (i = 0; i < n; i++) {
		if (a[i] > max) {
			max = a[i];
			maxn = i;
		}
		if (a[i] < min) { 
			min = a[i];
			minn = i; 
		}
	}
	p = a[minn];
	a[minn] = a[maxn];
	a[maxn] = p;
	cout << "После замены: " << "\n";
	for (i = 0; i < n; i++)
		cout << a[i] << "\n";
	return 0;
}