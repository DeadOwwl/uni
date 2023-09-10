#include <iostream>
#include <cstring>

/*
Волков Евгений, Лабораторная №4 по Assembler

Для  строки длиною не более 255 символов выполнить следующие действия:
Заданы два символа С1 и С2. 
Исключить все подстроки, начинающиеся с 
символа С1 и заканчивающиеся символом С2, 
длина которых меньше заданного числа.
*/

using namespace std;

int main()
{
	char s[256];
	char C1, C2;
	char E = '\0';
	int n;
	cout << "input string: ";
	cin.getline(s, 256);
	cout << "input C1 and C2\nC1 = ";
	cin >> C1;
	cout << "C2 = ";
	cin >> C2;
	cout << "input n: ";
	cin >> n;
	int L = strlen(s);
	int count = 0;
	_asm{
		cld
		lea edi, s
		mov ecx, L
	_Cikl_1: 
		mov al, C1
		repne scasb
		jne _END
		push edi
		mov esi, edi
		dec esi
		mov al, C2
		push ecx
	_Cikl_2:
		mov ebx, ecx
		repne scasb
		jne _END
		sub ebx, ecx
		inc ebx
		cmp ebx, n
		jge _P_E
		mov edx, esi
		mov esi, edi
		mov edi, edx
		push ecx
		rep movsb
		mov al, E
		stosb
		pop ecx
	_P_E: 
		pop ecx
		pop edi
		jmp _Cikl_1
	_END:
	}
	cout << "new string = " << s << endl;
	system("pause");
	return 0;
}