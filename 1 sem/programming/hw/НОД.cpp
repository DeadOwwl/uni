#include <iostream>
using namespace std;
int main()
{
	int long a, b, m, n;
	cout << "enter 2 numbers\n";
	cin >> a;
	cin >> b;
	m = a;
	n = b;
	while (a != b) {
		if (a > b) a = a - b;
		else
			b = b - a;
	}
	cout << "NOD(" << m << "," << n << ")=" << a << "\n";
	return 0;
}
