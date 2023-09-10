#include <iostream>
using namespace std;
int main()
{
	int a, ost, i;
	cin >> a;
	i = 1;
	do {
		ost = a % i;
		if (ost == 0) cout << i << " ";
		i++;
	} while (i <= a) ;
	return 0;
}