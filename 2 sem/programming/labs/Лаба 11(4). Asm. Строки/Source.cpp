#include <iostream>
#include <Windows.h>
#include <string>
#include <cstring>

using namespace std;

int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char* String = new char[256];
	char* newOne = new char[256];

	cout << "Введите вашу строку: ";
	cin.getline(String, 256);

	int len(0);
	int length1(0), length2(0), begin1(0), begin2(0), tmp(0), k(0), nTimes(0), flag(0);

	_asm
	{
		mov ebx, String
		xor ecx, ecx
		xor esi, esi
		xor edx, edx
		xor edi, edi
		mov edi, newOne

		mov ah, '\0'
	    cmp [ebx][ecx], ah
		je CHECKING

		FIND :
		mov ah, '\0'
			mov al, ' '
			inc ecx
			cmp[ebx][ecx], al
			jne SSW
			inc edx
			SSW :
		cmp[ebx][ecx], ah
			jne FIND
			cmp ecx, 1
			je CHECKING
			cmp ecx, 256
			je CHECKING
			mov len, ecx
			xor ecx, ecx
			inc ecx

			mov nTimes, edx
			xor edx, edx
			jmp GODNESS

			SORT1 :
		mov edx, nTimes
			dec edx
			cmp edx, 0
			je END
			mov nTimes, edx

			GODNESS :
		mov ah, ' '
			xor ecx, ecx

			P :
		mov esi, ecx
			L1 :
		cmp[ebx][esi], ah
			jne LNEXT1
			sub esi, ecx
			mov length1, esi
			jmp GAP

			LNEXT1 :
		inc esi
			cmp esi, len
			jne L1
			sub esi, ecx
			mov length1, esi

			GAP :
		mov esi, ecx
			add esi, length1
			inc esi

			SORT2 :
		mov edx, esi

			L2 :

		cmp[ebx][esi], ah
			jne LNEXT2
			jmp SWAP
			mov tmp, esi

			LNEXT2 :
		inc esi
			cmp esi, len
			jne L2

			SWAP :
		sub esi, edx
			mov tmp, edx
			mov length2, esi
			cmp length1, esi
			jle NEXTSWAP

			xor esi, esi
			mov edi, newOne

			mov begin1, ecx
			mov tmp, ecx
			mov k, ecx
			LITTLE1 :
		mov ecx, tmp
			mov al, [ebx][ecx]
			mov[edi][esi], al
			inc ecx
			inc esi
			mov tmp, ecx
			sub ecx, begin1
			cmp ecx, length1
			jne LITTLE1

			mov begin2, edx
			mov tmp, edx
			mov ecx, begin1
			LITTLE2 :
		mov edx, tmp
			mov al, [ebx][edx]
			mov[ebx][ecx], al
			inc ecx
			inc edx
			mov tmp, edx
			sub edx, begin2
			cmp edx, length2
			jne LITTLE2

			mov ah, ' '
			mov[ebx][ecx], ah
			inc ecx

			xor esi, esi

			LITTLE3 :
		mov al, [edi][esi]
			mov[ebx][ecx], al
			inc ecx
			inc esi
			cmp esi, length1
			jne LITTLE3
			mov ah, ' '
			mov[ebx][ecx], ah
			jmp FINAL

			NEXTSWAP :
		add edx, length2
			cmp edx, len
			je SORT1
			cmp edx, len
			jl K
			K :
		add ecx, length1
			inc ecx
			cmp ecx, len
			jl P

			FINAL :
		cmp ecx, len
			je SORT1
			sub ecx, length1
			cmp ecx, len
			jle P

			END :
		xor ecx, ecx
			mov ah, ' '
			mov al, '\n'
			jmp Q
			REPPLEASE :
		inc ecx
			Q :
		cmp ecx, len
			je ENDEND
			cmp[ebx][ecx], ah
			jne REPPLEASE
			mov[ebx][ecx], al
			jmp REPPLEASE

			ENDEND :
		mov ah, '\0'
			mov[ebx][ecx], ah

		CHECKING:
	}

	cout << "Ваша строка, отсортированная по длине слов и выведенная в столбик:\n" << String << endl;;

	delete[] String;
	delete[] newOne;
	system("pause");
	return 0;
}