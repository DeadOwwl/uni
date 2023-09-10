#include <iostream>
#include <ctime>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	int** a;
	int m, n, i, j;
	cout << "������� ������� ������� m (����� �����) � n (����� ��������): ";
	cin >> m >> n;
	a = new int* [m];
	for (i = 0; i < m; i++)
		a[i] = new int[n];

	int w;
	cout << "������� 0, ����� ������ ���������� ����;\n������� 1, ���� ������, ����� ������ ���������� ���������� �������:";
	cin >> w;
	if (w == 0) {
		cout << "������� �������� �������: ";
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++)
				cin >> a[i][j];
		}
	}
	else {
		cout << "������� �������� ��������� �����, ��� ������ ����� - ��������� ��������, ������ - ������� �������� ��������� (����� �����): ";
		int x, y;
		cin >> x >> y;
		cout << "\n";
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++) {
				a[i][j] = rand() % (y - x) + x;
				cout << a[i][j] << " ";
			}
			cout << endl;
		}
	}
	i = 0;
	j = 0;

	//����� ��������� � ��� �������, ������� �� �������� �����
	int sum = 0, nn = n - 1;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			if (a[i][j] == 0) {
				cout << "����� " << i + 1 << "-�� ������ �� ���������, ��� ��� � ��� ���� ������� �������\n";
				break;
			}
			else {
				sum += a[i][j];
				if (j == nn) cout << "����� " << i + 1 << "-�� ������: " << sum << endl;
			}
		}
		sum = 0;
	}

    //������ ������� ������ ������� � ���������, ������ � �������������, ... .
	int temp;
	nn = n;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n/2; j++) {
			temp = a[i][j];
			a[i][j] = a[i][nn-j-1];
			a[i][nn - j - 1] = temp;
		}
		nn = n;
	}
	cout << "������, � ������� ������ ������� ��������� ������� � ���������, ������ � ������������� � �.�.: \n";
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
		nn = n;
	}
	for (i = 0; i < m; i++) delete[] a[i];
	delete[] a;
	return 0;
}