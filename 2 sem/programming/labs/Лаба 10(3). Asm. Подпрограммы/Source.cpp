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
	cout << "Введите количество элементов массива: ";
	while (n <= 0)
	{
		cin >> n;
		if (n <= 0)
			cout << "Ошибка ввода. Некорректный размер массива. Повторите ввод: ";
	}
	int* intArr = new int[n];

	int a(0), b(0);
	cout << "\nВведите границы генерирования элементов массива: ";
	cin >> a >> b;

	cout << "\nМассив: ";
	for (unsigned i(0); i < n; i++)
	{
		intArr[i] = rand() % (b - a + 1) + a;
		cout << intArr[i] << " ";
	}
	cout << endl;

	int c(DifElStd(intArr, n));
	cout << "\n(_stdcall)Количество различных элементов в массиве: " << c << endl;

	c = DifEl(intArr, n);
	cout << "\n(_cdecl)Количество различных элементов в массиве: " << c << endl;

	c= DifElFast(intArr, n);
	cout << "\n(_fastcall)Количество различных элементов в массиве: " << c << endl;

	delete[]intArr;

	return 0;
}