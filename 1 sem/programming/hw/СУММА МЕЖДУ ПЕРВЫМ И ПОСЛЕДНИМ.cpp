#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	int k, sum = 0;
	int const max=500;
	int a[max];
	cout << "������� ���������� ��������� �������: ";
	int m, n, i=0;
	cin >> n;
	for (i = 0; i < n; i++) {
		cin >> a[i];
	}
	m = n; 
	i = 0;
	while (i<n && a[i]>=0) {
		i++;
		if (i==n) cout<<"������������� ��������� ��� \n";
		else {
			if (a[i] < 0) {
				m = n-1;
				while (m >= i && a[m] >= 0) {
					m--;
					if (m == i) cout << "� ������� ���� ������������� �������\n";
					else {
						if ((m - i) == 1) cout << "������������� �������� ��������� �����\n";
						else {
							i ++;
							for (i; i < m; i++) {
								sum += a[i];
							}
						}
					}
				}
			}
		}
	}
	cout << sum;
	return 0;
}