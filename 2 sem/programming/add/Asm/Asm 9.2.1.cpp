#include <iostream>
using namespace std;
int main()
{
	int y;
	//пример 9.2.1. сумма квадратов натуральных чисел от 1 до 10 типа int
	_asm
	{
		mov ecx, 10
		xor ebx, ebx
		mov esi, 1
		cikl: mov eax, esi
		      mul eax
		      add ebx, eax
		      inc esi
		loop cikl
		mov y, ebx
	}
	cout << "y=" << y << endl;
	//2-ой вариант, используя регистр ecx для хранения n
	// суммирование идет, начиная с 10 и заканчивая 1
	_asm
	{ mov ecx, 10
		xor ebx, ebx
		cikl1 : mov eax, ecx
		        mul eax
		        add ebx, eax
		loop cikl1
		mov y, ebx
	}
	cout << "y=" << y << endl;
}