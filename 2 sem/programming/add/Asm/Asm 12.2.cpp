#include <iostream>

using namespace std;

int main()
{
	setlocale(0, "");

	int x(10), y(0), xx(x);
	short h(1001), t(h);

	_asm
	{
		xor eax, eax
		xor ecx, ecx
		mov di, 10
		mov bx, h
		L:  
		xor edx, edx
		and bx, 1b
		cmp bx, 1
		jne S
        inc ecx
		S:
		mov ax, h
		mov bx, h
		div di
		cmp ax, bx
		jg K
		mov h, ax
		mov bx, ax
		cmp bx, 0
		jne L
	    
		K:
		mov y, ecx
		mov ebx, x
		mov eax, ebx
		sal eax, 4
		sub eax, ebx
		mov x, eax
	}

	cout << "Регистр bx: " << t << ", количество единиц в региcте bx: " << y <<
		"\nx: " << xx << ", результат умножения х на 15: " << x << endl;

	return 0;
}