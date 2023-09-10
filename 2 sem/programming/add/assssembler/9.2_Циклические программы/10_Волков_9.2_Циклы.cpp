#include <iostream>

using namespace std;


/*

			ВОЛКОВ ЕВГЕНИЙ, 10 ГРУППА, ЦИКЛЫ

*/


int main()
{
	int y;
	int h;
	_asm 
	{
		mov ecx,5   //ecx = 5
		xor ebx, ebx   //ebx = 0
		mov edi, 1   //edi = 1
		cikl_k: mov esi, ecx   //esi = ecx
		push ecx
		mov ecx, edi   //ecx = edi
		mov eax, esi  //eax = esi
		mul eax  //eax = eax*eax
		cdq
		mov h, eax   //edx = k*k
		mov esi, 5   //esi = 5
		cikl_n: mov eax, esi
		mul eax   //eax = n*n
		cdq
		add eax, h  //eax+=h
		mul eax   //eax = eax*eax
		cdq
		add ebx, eax  //ebx = ebx+eax
		dec esi   // esi--
		loop cikl_n  //ecx--
		pop ecx
		inc edi   //edi++
		loop cikl_k   //ecx--
		mov y, ebx   //y = ebx
	}


	/*y = 0;
	for (int k = 1; k <= 5; k++)
	{
		for (int n = k; n <= 5; n++)
		{
			y += (n * n + k * k) * (n * n + k * k);
		}
	}*/

	cout << "y = " << y << endl;

	return 0;
}