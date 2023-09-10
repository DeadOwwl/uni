#include <iostream>

using namespace std;

int main()
{
	int t(0), y(0);
	_asm
	{ 
		mov ecx, 5
		mov esi, 1
		xor ebx, ebx

		lab2 : push ecx
		mov ecx, esi

		lab1 : mov eax, ecx
		mul ecx
		mov t, eax
		mov eax, esi
		mul esi
		add eax, t
		mul eax
		add ebx, eax
		loop lab1

		pop ecx
		inc esi
		loop lab2

		mov y, ebx
	}
	cout << "y=" << y << endl;
}