#include "iostream"

using namespace std;

int main()
{
	setlocale(0, "");

	int x(0), y(0);
	cout << "¬ведите x: ";
	cin >> x;
	int xx(x), xxx(x);

	//Y=(5x^2+2)^2-1
	_asm
	{
		mov eax, x;
		imul x;
		mov x, eax;

		mov al, 5;
		imul x;

		add eax, 2;

		imul eax;

		sub eax, 1;

		mov y, eax;
	}
	cout << "1. " << y << endl;

	int x1(0), x2(0);
	//Y=(2+(50x^2+1)/(6+x^2))
	_asm
	{
		mov eax, xx;
		imul xx;
		mov xx, eax;

		mov eax, 50;
		imul xx;

		add eax, 1;
		mov x1, eax;

		mov eax, xxx;
		imul xxx;
		mov xxx, eax;

		mov eax, 6;
		add eax, xxx;
		mov x2, eax;

		mov eax, x1;
		mov ebx, x2;
		idiv ebx;
		mov xxx, eax;

		mov eax, 2;
		add eax, xxx;

		mov y, eax;
	}
	cout << "2. " << y << endl;

	//скал€рное произведение 2-х векторов на плоскости
	struct vector
	{
		int vX;
		int vY;
	};
	vector v1, v2;
	cout << "¬ведите координы дл€ 2-х векторов на плоскости: ";
	cin >> v1.vX >> v1.vY >> v2.vX >> v2.vY;
	int vectMul(0);

	_asm
	{
		mov eax, v1.vX;
		imul v2.vX;
		mov x1, eax;

		mov eax, v1.vY;
		imul v2.vY;

		add eax, x1;
		mov y, eax;
	}
	cout <<"3. "<< y << endl;

	//квадрат площади треугольника
	cout << "¬ведите стороны треугольника: ";
	cin >> x >> xx >> xxx;
	int p(0), s1(0), s2(0), s3(0);
	_asm
	{
		mov eax, x;
		add eax, xx;
		add eax, xxx;
		xor edx, edx;
		mov ebx, 2;
		idiv ebx;
		mov p, eax;

		sub eax, x;
		mov s1, eax;

		mov eax, p;
		sub eax, xx;
		mov s2, eax;

		mov eax, p;
		sub eax, xxx;
		mov s3, eax;

		mov eax, p;
		imul s1;
		imul s2;
		imul s3;

		mov y, eax;
	}
	cout << "4. " << y << endl;

	return 0;
}