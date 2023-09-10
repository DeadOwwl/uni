#include <iostream>
using namespace std;
int main()
{
	int N;
	cin >> N;
	int* a = new int [N];
	for (int i = 0; i < N; i++) cin >> a[i];
	int M;
	cin >> M;
	int max = 0, sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				if (i != k && i != j && j != k) 
					sum = a[i] + a[j] + a[k]; 
				if (sum <= M && sum>max) max = sum;
				sum = 0;
			}
		}
	}
	cout << max;
	delete[]a;
	return 0;
}