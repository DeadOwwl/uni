#include <iostream>

using namespace std;

int main()
{
    int x, y;
    int a(2), b(8), c(3), d(5);
    cout << "Input x, pls: " << endl;
    cin >> x;
    _asm
    {
        mov eax, x // x->eax
        cmp eax, 0 //����������
        jz block0 //���� 0, �� ���� 0
        imul x // x^2->eax
        mov ebx, x // x->ebx
        sub ebx, eax // x-x^2->ebx
        add ebx, a // x-x^2+2->ebx
        mov eax, x // x->eax
        cmp eax, 0 // ���������� � 0
        jg block1 //���� >0, �� ���� 1
        imul d // �������� � �� 5
        add eax, c //����� ��� � 3
        sub eax, ebx
        mov y, eax
        jmp stop
        block1 :
            imul b
            mov ecx, eax
            mov eax, ebx
            imul eax
            sub eax, ecx
            mov y, eax
            jmp stop
        block0 :
            mov y, 1000
            stop :
    }
    cout << y << endl;
    return 0;
}