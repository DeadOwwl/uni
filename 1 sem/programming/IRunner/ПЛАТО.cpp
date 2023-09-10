#include <iostream>
#include <iomanip>
using namespace std;
int main() {
	int n;
	cin >> n;
	int* Array = new int[n];
	int Max = 0, Min = n, k = 0, c = 1;
	for (int i = 0; i < n; i++)	cin >> Array[i];
	for (int i = 0; i < n - 1; i++) {
		if (Array[i] == Array[i + 1]) c++;
		if (c > Max && c != 1) Max = c;
		if (((Array[i] != Array[i + 1]) || (c != 1) && (i == n - 2))) {
			if (c < Min) Min = c;
			k++;
			c = 1; 
			
		}
	}
	if (Max == 1) Max -= 1;
	if (Min == 1) Min = 0;
	if (k == 0) {
		Min = 0;
		Max = 0;
	}
	cout << k << " " << Max << " " << Min;
	delete[] Array;
	return 0;
	system("pause");
}
