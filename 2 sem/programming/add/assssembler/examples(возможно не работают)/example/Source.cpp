#include <iostream> 
using namespace std;
int main()
{
   // setlocale(LC_ALL, ".1251");
    char x1, y1, y11; 
    short pr1;
    short x2, y2, pr2;
    int x3, y3, pr3;

    //произведение двух чисел типа byte   
    cout << "введите два числа длиною в 1 байт" << endl;
    //cin >> x1 >> y1; //так нельзя ввести байты, будут коды символов  
    cin >> x2 >> y2;  //вводим в поля длиною short 
    x1 = x2; // копируем 
    y1 = y2;
    _asm {
        mov al, x1
        imul y1
        mov pr1, ax
    }
    cout << pr1 << endl;

    //произведение двух чисел типа short   
    cout << "введите два числа длиною в слово (2 байта)" << endl;
    cin >> x2 >> y2;
    _asm {
        mov ax, x2
        imul y2
        mov pr2, ax
    }
    cout << pr2 << endl;

    //произведение двух чисел типа int   
    cout << "введите два числа int длиною в 4 байта" << endl;
    cin >> x3 >> y3;
    _asm {
        mov eax, x3
        imul y3
        mov pr3, eax
    }
    cout << pr3 << endl;

    cout << "\numnozhenije x1 na 20\n";
    //умножение на число  pr2=x1*20; 
    //команда с 2-мя операндами 
    _asm {
        mov eax, 20
        imul x1
        mov pr2, ax
    }
    cout << "\numnozhenije x1 na 20\n";
    cout << pr2 << endl;

    _asm {
        mov eax, x3
        imul ebx, eax, 50
        mov pr3, ebx
    }
    cout << "\numnozhenije x3 na 50\n";
    cout << pr3 << endl;

    //умножение на число
    _asm {
        imul ebx, x3, 50
        mov pr3, ebx
    }
    cout << "\ndrugoe umnozhenije x1 na 50\n";
    cout << pr3 << endl;


    //деление двух чисел типа byte pr2=x1/y1 
    _asm {
        mov al, x1
        cbw
        idiv y1
        cbw
        mov pr2, ax
    }
    cout << "\ndelenije x1 na y1\n";
    cout << pr2 << endl;

    //деление двух чисел типа short pr2=x2/y2 
    _asm {
        mov ax, x2
        cwd
        idiv y2
        mov pr2, ax
    }
    cout << pr2 << endl;

    //деление двух чисел типа int pr3=x3/y3
    _asm {
        mov eax, x3
        cdq
        idiv y3
        mov pr3, eax
    }
    cout << pr3 << endl;

    system("pause");
    return 0;
}