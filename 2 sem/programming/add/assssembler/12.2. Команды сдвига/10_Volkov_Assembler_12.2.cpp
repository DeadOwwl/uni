/*
Написать программу (одну) решения следующих задач:

а) подсчета количества единиц в представлении числа, записанного в регистре BX;

б) умножения числа Х на 15 без использования команд умножения, если известно, что

результат умещается в четырех байтах.
*/

/*

Волков Евгений, 10а группа

Ассемблер, №12.2

*/

#include <iostream>

using namespace std;

int main()
{
    //ПУНКТ А
    short x1, result, c_16 = 16;
    cout << "PART A\nenter x\nx = ";
    cin >> x1;
    __asm
    {
        mov cx, c_16
        //cx = 16
        //т.к. регистры AX-DX занимают 16 бит
        xor dx, dx
        mov bx, x1
     L1:push bx
        and bx, 1 //смотрим остаток от деления на 2
        cmp bx, 1 //если 1, то увеличиваем счётчик DX
        jne L2
        inc dx  //счётчик DX
     L2:pop bx
        sar bx, 1 //делим на 2
        cmp cx, 1
        je L3
     loop L1
     L3:mov result, dx
    }
    cout << "\nnumber of '1' in x: " << result << '\n';

	//  ПУНКТ Б
	int x2;
	cout << "\nPART B\nenter x\nx = ";
	cin >> x2;
	//предусматриваем ситуацию, когда число х*15 помещается в 4 байта, а х*16 - нет
	_asm
	{
		mov eax, x2
		sal eax, 3
		mov ebx, eax
		sub ebx, x2
		add eax, ebx
		mov x2, eax
	}
    cout << "\nx*15 = " << x2 << endl << endl;

	return 0;
}