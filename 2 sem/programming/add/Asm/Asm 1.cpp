#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, ".1251");

	char x1, y1, y11;
	short pr1;
	short x2, y2, pr2;
	int x3, y3, pr3;

	cout << "¬ведите два числа длиною в байт: " << endl;
	cin >> x2 >> y2; 
	x1 = x2; 
	y1 = y2;
	_asm 
	{
		mov al, x1
		imul y1
		mov pr1, ax
	}
	cout << pr1 << endl;

	cout << "¬ведите два числа длиною в слово: " << endl;
	cin >> x2 >> y2;
	_asm 
	{
		mov ax, x2
		imul y2
		mov pr2, ax
	}
	cout << pr2 << endl;
	
	cout << "¬ведите два числа int длиною в 4 байта" << endl;
	cin >> x3 >> y3;
	_asm 
	{
		mov eax, x3
		imul y3
		mov pr3, eax
	}
	cout << pr3 << endl;

	_asm 
	{
		mov al, 20
		imul x1
		mov pr2, ax
	}
	cout << pr2 << endl;

	_asm 
	{
		mov eax, x3
		imul ebx, eax, 50
		mov pr3, ebx
	}
	cout << pr3 << endl;
	
	_asm 
	{
		imul ebx, x3, 50
		mov pr3, ebx
	}
	cout << pr3 << endl;
	
	_asm 
	{
		mov al, x1
		cbw
		idiv y1
		cbw
		mov pr2, ax
	}
	cout << pr2 << endl;
	
	_asm
	{
		mov ax, x2
		cwd
		idiv y2
		mov pr2, ax
	}
	cout << pr2 << endl;
	
	_asm 
	{
		mov eax, x3
		cdq
		idiv y3
		mov pr3, eax
	}
	cout << pr3 << endl;

	return 0;
}