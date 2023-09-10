// Задание 9.1.1.

/*
             (x-x^2+2)^2 - 8x, x>0
        y =  1000, x=0
             3 + 5x - (x-x^2+2), x<0
*/

#include <iostream>

using namespace std;

//int main()
//{
//    int x, y;
//    int a = 2, b = 8, c = 3, d = 5;
//    cout << "input x " << endl;
//    cin >> x;
//    _asm
//    {
//        mov eax, x // x->eax
//        cmp eax, 0
//        jz block0
//        imul x // x^2->eax
//        mov ebx, x // x->ebx
//        sub ebx, eax // x-x^2->ebx
//        add ebx, a // x-x^2+2->ebx
//        mov eax, x // x->eax
//        cmp eax, 0
//        jg block1
//        imul d
//        add eax, c
//        sub eax, ebx
//        mov y, eax
//        jmp stop
//        block1 :
//        imul b
//            mov ecx, eax
//            mov eax, ebx
//            imul eax
//            sub eax, ecx
//            mov y, eax
//            jmp stop
//            block0 :
//        mov y, 1000
//            stop :
//    }
//    cout << y << endl;
//    return 0;
//}


// Задание 9.1.2.

/*

Составить блок-схему и написать
программу нахождения таких чисел, принадлежащих
отрезку [a,b], для которых
y=(3n^3-2n^2+5n-920)/(n^2+n)
принимает целые значения.


*/

int main()
{
    cout << "input [a,b]" << endl;
    short a, b;
    cin >> a >> b;
    short n, y1, d1 = 1, d2 = 2, d3 = 3, d5 = 5, d920 = 920;
    _asm
    {
        mov ax, a
        mov n, ax
        bl0:
        mov ax, n
            add ax, d1
            imul n
            mov bx, ax
            mov ax, n
            imul d3
            sub ax, d2
            imul n
            add ax, d5
            imul n
            sub ax, d920
            cwd
            idiv bx
            cmp dx, 0
            jz bl2
            jmp bl1
            bl2 :
        mov y1, ax
    }
    cout << n << endl;
bl1:
    _asm
    {
        inc n
        mov ax, b
        cmp n, ax
        jle bl0
    }
    return 0;
}