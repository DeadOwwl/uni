#include <iostream>
using namespace std;
int main()
{
	int a, d, dd, ch;
	cin >> a;
	d = a;
	while (d > 0) {
		if (a%d == 0) {
			ch = 0;
			dd = 1;
			while (dd <= d) {
				if (d%dd == 0) ch++;
				dd++;
			}
			if (ch == 2) cout << d << " ";
		}
		d--;
	}
	return 0;
}
