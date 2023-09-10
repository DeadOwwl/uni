#include <algorithm>
extern long int s, p;
void shaker(int* a, int size) {
	int left, right, i;
	left = 0;
	right = size - 1;
	while (left <= right) {
		s++;
		for (i = right; i > left; i--) {
			s++;
			if (a[i - 1] > a[i]) {
				s++;
				std::swap(a[i - 1], a[i]);
				p++;
			}
		}
		left++;
		for (i = left; i <= right; i++) {
			s++;
			if (a[i - 1] > a[i]) {
				s++;
				std::swap(a[i - 1], a[i]);
				p++;
			}
		}
		right--;
	}
}