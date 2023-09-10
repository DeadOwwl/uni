#include <iostream>
#include <cmath>

double mnoz(int* x, int n)
{
	if (n == 0) return x[n];
	return x[n] * mnoz(x, n - 1);
}

int main()
{
	int i, n;
	std::cout << "Input n=";
	std::cin >> n;
	int* a = new int[n];
	for (i = 0; i < n; i++)
		std::cin >> a[i];
	std::cout << mnoz(a, n - 1);
	delete[] a;
	return 0;
}