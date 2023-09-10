#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#pragma warning (disable:4996)

using namespace std;

int main()
{
	setlocale(0, "");

	char Text[100] = { "7WeRtYuIoPlKjHgFdSaZxCvBnMÉöóÊåÍãØùÇõÚıÆäËîĞqWeRtYuIoPlKjHgFdSaZxCvBnMÉöóÊåÍãØùÇõÚıÆäËîĞïÂû×ñïÂû×ñÈ" };
	char P = ' ';

	_asm
	{
		lea ebx, Text
		xor ecx, ecx
		mov ah, 32
		xor al, al

	A : mov al, [ebx + ecx]
		cmp[ebx + ecx], 97
		jl R
		cmp[ebx + ecx], 122
		jg R
		mov al, [ebx + ecx]
		xor al, ah
		xchg al, [ebx + ecx]
		jmp N

	R : cmp[ebx + ecx], 224
		jl N
		cmp[ebx + ecx], 255
		jg N
		mov al, [ebx + ecx]
		xor al, ah
		xchg al, [ebx + ecx]

	N:  cmp ecx, 99
	    je END
		inc ecx
		jmp A

    END:
	}

	for (unsigned i(0); i < 100; i++)
		cout << Text[i];

	return 0;
}