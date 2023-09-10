#include <algorithm>
extern long int p, s;
void q_sort(int* a, int l, int r) {
	int left = l, right = r;
	int piv = a[(left + right) / 2]; // Опорным элементом для примера возьмём средний
	while (left <= right) {
		s++;
		while (a[left] < piv) {
			s++;
			left++;
		}
		while (a[right] > piv) {
			s++;
			right--;
		}
		if (left <= right) {
			s++;
			std::swap(a[left++], a[right--]);
			p++;
		}
	}
	if (l < right) {
		s++;
		q_sort(a, l, right);
	}
	if (r > left) {
		s++;
		q_sort(a, left, r);
	}
}