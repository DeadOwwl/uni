#include <iostream>
using namespace std;

/*

ВОЛКОВ ЕВГЕНИЙ, 10 ГРУППА, ЛАБОРАТОРНАЯ №1 ПО АССЕМБЛЕРУ

Найти N пар простых чисел, которые отличались бы друг от
друга на 2 ("близнецы").

*/

bool simple (int a) 
{
	if (a == 1) 
		return false;
	for (int i = 2; i <= a / 2; i++)
		if (a % i==0) 
			return false;
	return true;
}

int main()
{
	int N;
	cout << "enter number of pairs ";
	cin >> N;
	int n = N;
	int k;
	int i;
	int d2 = 2;
	int j;
	cout << "\n====================\nASSEMBLER\n====================" << endl;
	_asm
	{
		mov i, 2
		mov k, 0
	F1: inc i
	F2 : mov eax, i
		cdq
		div d2
		mov ecx, eax
		mov j, 2
	h1 : mov eax, i 
		cdq
		div j
		cmp edx, 0
		je N1
		inc j
	loop h1  
		cmp k, 0
		je K0
		cmp k, 1
		je K1
	K0: mov k, 1
		mov ebx, i
		add ebx, d2  
		mov i, ebx
		jmp F2
	K1: mov k, 0
		dec N
		jmp V
	N1: cmp k, 0
		je F1
		cmp k, 1
		je N2
	N2: mov k, 0
		mov ebx, i
		sub ebx, d2
		mov i, ebx
		jmp F1
	}
V:
	cout << i - 2 << "  " << i << endl;
	_asm
	{
		mov ebx, i
		sub ebx, d2
		mov i, ebx
		cmp N, 0
		jne F1
	}
	cout <<endl<< "\n====================\nC++\n====================" << endl;
	k = 0;
	for (int i = 2;k<n;i++)
			if (simple(i) && simple(i + 2))
			{
				k++;
				cout << i << "  " << i + 2 << endl;
			}
	return 0;
}