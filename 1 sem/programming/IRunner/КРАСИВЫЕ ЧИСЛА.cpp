#include <iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++) cin >> a[i];
	int p = 1, k = 0, ost = 0, l = 0, t = 0;
	for (int i = 0; i < n; i++) {
		while (a[i]) {
			if ((a[i] % 10) % 2 == p % 2) t++;
			p++;
			a[i] /= 10;
			l++;
		}
		if (t == l) k++;
		l = 0;
		p = 1;
		t = 0;
	}
	cout << k;
	delete[]a;
	return 0;
}