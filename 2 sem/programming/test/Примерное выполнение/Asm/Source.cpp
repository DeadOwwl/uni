#include <iostream>
#include <cmath>
#include <ctime>
#include <Windows.h>

using namespace std;

void firstTask()
{
	int n(10);
	short int* firstArr = new short int[n];

	cout << "Первоначальный массив: ";
	for (unsigned i(0); i < n; i++)
	{
		firstArr[i] = rand() % 100 - 50;
		cout << firstArr[i] << " ";
	}

	_asm
	{
		mov ebx, firstArr
		mov eax, n
		mov edi, n
	    sal eax, 1
		mov n, eax
		mov edx, eax
		sub edx, 2
		xor ecx, ecx
		xor eax, eax

		L:
		xor esi, esi
		mov ax, [ebx][ecx]
		cmp ax, 10
		jg NEXT
		cmp ax, -10
		jl NEXT
		cmp ecx, n
		je END

		mov esi, ecx
		F:
	    mov ax, [ebx][ecx + 2]
		mov [ebx][ecx], ax
		add ecx, 2
		cmp ecx, n
		jne F
		mov ax, 0
		mov[ebx][edx], ax
		sub edx, 2
		mov ecx, esi
		mov eax, n
		sub eax, 2
		mov n, eax
		jmp L

		NEXT:
		add ecx, 2
		cmp ecx, n
		jne L

		END:
		mov n, edi
	}

	cout << "\nМассив после удаления элементов, по модулю не превышавших 10, и заполнения свободных ячеек нулями: ";
	for (unsigned i(0); i < n; i++)
		cout << firstArr[i] << " ";
}

void sixthTask()
{
	int n(10);
	int* firstArr = new int[n];

	cout << "Первоначальный массив: ";
	for (unsigned i(0); i < n; i++)
	{
		firstArr[i] = rand() % 100 ;
		cout << firstArr[i] << " ";
	}

	int k(0), arf(0);

	_asm
	{
		mov ebx, firstArr
	    xor eax, eax
		xor ecx, ecx
		xor esi, esi
		xor edx, edx

		ARF:
		add eax, [ebx][ecx * 4]
        inc ecx
		cmp ecx, n
		jne ARF
		div n
		mov arf, eax

        xor ecx, ecx
		dec ecx
		xor edi, edi
		CHECKING:
		inc ecx
	    cmp ecx, n
		je ENDEND
		mov edx, eax
		sub edx, [ebx][ecx * 4]
		cmp edx, 0
		jg NEXT
		neg edx

		NEXT:
		mov esi, eax
		sub esi, [ebx][edi * 4]
		cmp esi, 0
		jg NEXTSTEP
		neg esi
	    
		NEXTSTEP:
        cmp edx, esi
        jge CHECKING
		mov edi, ecx
        jmp CHECKING

		ENDEND:
		inc edi
		mov k, edi
	}

	cout << "\nСреднее арифметическое: " << arf << "\nИндекс элемента, который наиболее близок к среднему арифметическому всех элементов (начиная с 1): " << k;
}

int main()
{
	setlocale(0, " ");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	//firstTask();
	sixthTask();

	return 0;
}