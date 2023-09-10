#include <iostream>

using namespace std;

int main()
{
	int y(0);

	//    10       3
	//𝑦 = ∑(2𝑛 − 1)
	//   n=1

	_asm
	{
		mov ecx, 10
		xor ebx, ebx
    cikl2 :
	    mov eax, 2
		mul ecx
		dec eax
		mov esi, eax
		mul eax
		mul esi
		add ebx, eax
		loop cikl2
		mov y, ebx
	}
	cout << "y=" << y << endl;}