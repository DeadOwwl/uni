#include <iostream>
using namespace std;
int main()
{
	int n, k=0;
	cin >> n;
	do {
		n -= 3;
		if (n <= 1) break;
		k++;
	} while (n > 1);
	cout << k;
	return 0;
}