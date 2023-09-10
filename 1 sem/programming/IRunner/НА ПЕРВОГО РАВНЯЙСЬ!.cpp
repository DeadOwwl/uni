#include <iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++) cin >> a[i];
	int k = 0;
	for (int i = 1; i < n; i++) {
		if (a[i] == a[0]) k++;
	}
	cout << k;
	delete[]a;
	return 0;
}