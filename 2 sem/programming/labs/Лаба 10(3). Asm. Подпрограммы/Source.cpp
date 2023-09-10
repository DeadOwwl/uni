#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

extern "C" int _stdcall DifElStd(int*, int);
extern "C" int __cdecl DifEl(int*, int);
extern "C" int _fastcall DifElFast(int*, int);

int main()
{
	setlocale(0, "");
	srand(time(NULL));

	int n(0);
	cout << "������� ���������� ��������� �������: ";
	while (n <= 0)
	{
		cin >> n;
		if (n <= 0)
			cout << "������ �����. ������������ ������ �������. ��������� ����: ";
	}
	int* intArr = new int[n];

	int a(0), b(0);
	cout << "\n������� ������� ������������� ��������� �������: ";
	cin >> a >> b;

	cout << "\n������: ";
	for (unsigned i(0); i < n; i++)
	{
		intArr[i] = rand() % (b - a + 1) + a;
		cout << intArr[i] << " ";
	}
	cout << endl;

	int c(DifElStd(intArr, n));
	cout << "\n(_stdcall)���������� ��������� ��������� � �������: " << c << endl;

	c = DifEl(intArr, n);
	cout << "\n(_cdecl)���������� ��������� ��������� � �������: " << c << endl;

	c= DifElFast(intArr, n);
	cout << "\n(_fastcall)���������� ��������� ��������� � �������: " << c << endl;

	delete[]intArr;

	return 0;
}