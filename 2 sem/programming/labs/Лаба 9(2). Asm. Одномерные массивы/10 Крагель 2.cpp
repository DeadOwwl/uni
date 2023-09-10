#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	setlocale(0, "");

	int n(0);
	cout << "Введите количество элементов массива: ";
	cin >> n;
	int *iArray = new int[n];

	cout << "Введите границы генерирования элементов массива: ";
	int a(0), b(0);
	cin >> a >> b;

	cout << "Массив до сортировки: ";
	for (unsigned i(0); i < n; i++)
	{
		iArray[i] = rand() % (b - a + 1) + a;
		cout << iArray[i] << " ";
	}

	cout << "\nМассив после сортировки: ";

	int q(n), k(-1), tmp(0), aTmp(0), bTmp(0);

	_asm
	{
		mov ebx, iArray
		mov ecx, n

	L1:
		mov eax, q
		sub eax, 1
		mov q, eax

		xor eax, eax
		mov k, eax

		cmp q, 0
		je END

	L2:
		mov eax, k
		add eax, 1
		mov k, eax

		cmp eax, q
		ja L1

		xor eax, eax

		mov ecx, k
		mov eax, [ebx][ecx * 4 - 4]
		mov a, eax

		//cmp eax, 0
		//jge AFTERABS1

		//mov ecx, -1
		//mul ecx
		//mov ecx, k

	AFTERABS1:
		mov aTmp, eax

		add ecx, 1 
		mov eax, [ebx][ecx * 4 - 4]
		mov b, eax
		//cmp eax, 0
		//jge AFTERABS2

		//mov ecx, -1
		//mul ecx;
		//mov ecx, k
		//add ecx, 1

	AFTERABS2:
		mov bTmp, eax

		mov eax, bTmp
		cmp aTmp, eax
		jge L2

		mov eax, a
		mov tmp, eax
		sub ecx, 1
		mov eax, b
		mov[ebx][ecx * 4 - 4], eax
		add ecx, 1
		mov eax, a
		mov[ebx][ecx * 4 - 4], eax
		jmp L2

		END:
	}

	for (unsigned i(0); i < n; i++)
		cout << iArray[i] << " ";
	cout << endl;
	delete[] iArray;

	return 0;
}