#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	setlocale(0, "");
	int A, B;
	cout << "¬ведите крайние точки A и B: \n";
	cin >> A >> B;
	int x, y;
	x = A;
	for (x; x <= B; x++) {
		int d_x, i;
		d_x = 1;
		i = 0;
		do {
		if (x % d_x == 0) i++;
		d_x++;
		} while (d_x <= x );
			if (i == 2) {
				y = A;
				for (y; y <= B; y++) {
					int d_y, k;
					d_y = 1;
					k = 0;
					do {
						if (y % d_y == 0) k++;
						d_y++;
					} while (d_y <= y);
					if (k == 2) {
						if (abs(x - y) == 2) cout << x << " и " << y << "\n";
					}
				}
			}
	}
	return 0;
}