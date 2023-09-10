#include <iostream>

using namespace std;

int main()
{

	int y(0);

	//     10 10
	//m𝑦 = ∑  ∑ (5𝑛 − 𝑖)
	//    i=1 n=1

	_asm
	{ mov ecx, 10
		mov esi, 1
		xor ebx, ebx
		lab2 : push ecx
		mov ecx, 10
		lab1 : mov eax, 5
		mul ecx
		sub eax, esi
		add ebx, eax
		loop lab1
		pop ecx
		inc esi
		loop lab2
		mov y, ebx
	}
	cout << "y=" << y << endl;
}