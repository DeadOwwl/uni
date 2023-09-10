#include <iostream>
using namespace std;
int main()
{
	setlocale(0, ""); //good luck to me 
	int  ch, n, i, d;
	cout << "¬ведите крайнее число n: ";
	cin >> n;
	for (i = 2; i <= n; i++) {
		d = 1;
		ch = 0;
		while (d <= i/2) {
			if (i % d == 0) ch++;
			d++;
			}
		if (ch == 1) cout << i << " \n";
	}
	return 0;
}