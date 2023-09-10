#include <iostream>
using namespace std;
int main()
{
	setlocale(0, "");
	long int i = 1, n, d, ch = 0, n1 = 1, ost;
	cout << "¬ведите число n простых чисел: ";
	cin >> n;
	while (n1 <= n) {
		i++;
		d = 1;
		while (d <= i) {
			ost = i % d;
			if (ost == 0) {
				ch++;
			}
			d++;
		}
	if (ch == 2) {
    cout << i << " ";
	n1++;
    }
	ch = 0;
	}
	return 0;
}