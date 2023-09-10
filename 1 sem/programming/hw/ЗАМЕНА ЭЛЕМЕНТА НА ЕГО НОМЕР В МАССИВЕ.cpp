#include <iostream>
#include <string>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	signed int a[20], i;
	for (i = 0; i < 20; i++) {
		a[i] = rand();
	}
	for (i = 0; i < 20; i++) {
		if (a[i] < 0)cout << i << endl;
		else cout << a[i] << endl;
	}
	return 0;
}