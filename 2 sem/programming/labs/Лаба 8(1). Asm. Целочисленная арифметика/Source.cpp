#include <iostream>

using namespace std;

int main()
{
	setlocale(0, "");
	int a(0), b(0);
	bool flag(false);
	cout << "Введите границы отрезка: ";
	cin >> a >> b;
	cout << "Проcтые числа на отрезке: ";
	_asm
	{
		mov esi, a

		R : mov eax, esi
		mov edi, 2
		xor edx, edx
		div edi
		add eax, 1
		mov ecx, eax

		xor ebx, ebx
		L : add ebx, 1
		dec ecx
		cmp ecx, 0
		je END

		CHECK :
		mov eax, esi
		xor edx, edx
		div ecx
		cmp edx, 0
		je L
		loop CHECK

		END : cmp ebx, 2
		jne S
		cmp ebx, 2
		mov flag, 1
		cmp ebx, 2
		jne S


		WRITE :
		mov a, esi

	}
	cout << a << " ";
	_asm
	{
	    S: inc a
		mov esi, a
		cmp esi, b
		jle  R

		cmp flag, 0
		jne ENDEE
	}
	cout << "таких нет.\n";
	_asm
	{
		ENDEE:
	}
	return 0;
}