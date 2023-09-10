#include <iostream>
using namespace std;
int main()
{
	int a, d, ost_a, ost_d, dd, ch;
	cin >> a;
	d = 1;
	while (d <= a) {
		ost_a = a % d;
		if (ost_a == 0) { 
			ch = 0;
			dd = 1;
			while (dd <= d) {
				ost_d = d % dd;
				if (ost_d == 0) ch++;
				dd++;
			}
		    if (ch == 2) cout << d << " \n";
		}
		d++;
	}
	return 0;
}
