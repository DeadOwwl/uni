#include <iostream>
using namespace std;
int main()
{
	int y;
	//������ 9.2.1. ����� ��������� ����������� ����� �� 1 �� 10 ���� int
	_asm
	{
		mov ecx, 10
		xor ebx, ebx
		mov esi, 1
		cikl: mov eax, esi
		      mul eax
		      add ebx, eax
		      inc esi
		loop cikl
		mov y, ebx
	}
	cout << "y=" << y << endl;
	//2-�� �������, ��������� ������� ecx ��� �������� n
	// ������������ ����, ������� � 10 � ���������� 1
	_asm
	{ mov ecx, 10
		xor ebx, ebx
		cikl1 : mov eax, ecx
		        mul eax
		        add ebx, eax
		loop cikl1
		mov y, ebx
	}
	cout << "y=" << y << endl;
}