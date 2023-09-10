#include <iostream>

using namespace std;

int main()
{
short n, y1, d1 = 1, d2 = 2, d3 = 3, d5 = 5, d920 = 920;
cin >> n;
_asm
{
	mov n, 1
	bl0:
	    mov ax, n
		add ax, d1
		imul n
		mov bx, ax
		mov ax, n
		imul d3
		sub ax, d2
		imul n
		add ax, d5
		imul n
		sub ax, d920
		cwd
		idiv bx
		cmp dx, 0
		jz bl2
		jmp bl1
	bl2 :
	    mov y1, ax
}
cout << n << endl;
bl1:
     _asm
     {
	inc n
	cmp n, 15
	jle bl0
     }
}
