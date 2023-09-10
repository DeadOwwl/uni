#include <iostream>

using namespace std;

/*

ВОЛКОВ ЕВГЕНИЙ, 10 ГРУППА, ЛАБОРАТОРНАЯ №2 ПО АССЕМБЛЕРУ

Разработать алгоритм и составить программу для решения следующих задач:
Из массива чисел выбрать все простые числа

*/

const int NMAX = 100;

int main()
{
	int N;
	cout << "enter size:  ";
	cin >> N;
	while (N <= 0)
	{
		cout << "Error! Incorrect size. Enter size again:  ";
		cin >> N;
	}
	int Array[NMAX];
	cout << "enter elements\n";
	for (int i = 0; i < N; i++)
		cin >> Array[i];
	cout << "\n\n\t\tARRAY\n=========================================================\n";
	for (int i = 0; i < N; i++)
		cout << Array[i] << "  ";
	cout << "\n=========================================================\n";
	int k = 0, d2 = 2, j, i, c;
	cout << "\n\n\t\tSIMPLE NUMBERS:\n=========================================================\n";
	_asm 
	{
		mov ecx, N
		lea ebx, Array
		xor eax, eax
	arr : mov eax, [ebx]
		push ecx
		mov i, eax
		cdq
		cmp eax, 1
		jle N1
		cmp eax, 2
		je N2
		div d2
		mov ecx, eax
		mov j, 2
	h: mov eax, i
		cdq
		div j
		cmp edx, 0
		je N1
		inc j
	loop h
		jmp N2
	N1 : add ebx, 4
		pop ecx
	loop arr
		jmp N3
	N2:
	}
	cout << i << "  ";
	_asm
	{
		inc k
		jmp N1
		N3: 
	}
	if (k == 0)
		cout << "no simple numbers";
	cout << "\n=========================================================\n";
}