#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	int const maxa = 1000, maxb = 1000;
	int a[maxa], b[maxb];
	cout << "Введите размер массивов: \n";
	int ma, mb;
	cin >> ma >> mb;
	cout << endl;
	int ia = 0, ib = 0, ic = 0;
	cout << "Первый массив: ";
	for (ia; ia < ma; ia++) {
		cin >> a[ia];
		cout << endl;
	}
	cout << "Второй массив: ";
	for (ib; ib < mb; ib++) {
		cin >> a[ib];
		cout << endl;
	}
	int c[maxa + maxb];
	ia = 0, ib = 0, ic = 0;
	while (ia < ma && ib < mb) {
		if (a[ia++] > b[ib++]) c[ic++] = b[ib++];
		else c[ic] = a[ia];
		if (ia > ma) c[ic++] = b[ib++];
		else c[ic++] = a[ia++];
	}
	cout << "Третий массив: ";
	int mc = ma + mb;
	for
		(ic; ic < mc; ic++) {
		cout << a[ic] << endl;
	}
	return 0;
}