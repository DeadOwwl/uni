#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
using namespace std;
int main() {
	int a, n;
	cin >> a >> n;
	int sum_a = 0;
	int a_t = a;
	while (a !=0 ) {
		sum_a += a % 10;
		a /= 10;
	}
	int b = pow(10, n), sum_b = 0, k = 0, b_t = 0;
	while (k!=n && sum_b!=a_t) {
		b_t = b;
		while (b != 0) {
			sum_b += b % 10;
			b /= 10;
			k++;
		}
		if (k != n || sum_b != a_t) {
			sum_b = 0;
			b = --b_t;
			k = 0;
		}
	}
	cout << b_t;
	return 0;
}
