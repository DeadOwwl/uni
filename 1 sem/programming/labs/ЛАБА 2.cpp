#include <iostream>
using namespace std;
bool proverka(int a)
{
	int b, c;
	c = a;
	b = 0;
	do {
		b = a % 10 + 10 * b;
		a = a / 10;
	} while (a != 0);
	return (c == b);
	b = 0;
	c = 0;
}
int main()

{
	setlocale(0, "");
	cout << "¬ведите крайнее число: ";
	int n, k = 1;
	cin >> n;
	cout << "ƒвойные полиндромы меньше " << n << ": \n";
	for (k; k <= n; k++) {
		if (proverka(k) && proverka(k * k)) cout << k << endl;
	}
	return 0;
}