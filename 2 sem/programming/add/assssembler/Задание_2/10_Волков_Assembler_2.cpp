#include <iostream>

using namespace std;

/*

VOLKOV EVGENIJ, 10 group

*/

int main()
{
	//  1) Y=(5*x*x+2)^2-1
	cout << "enter x = ";
	int x;
	int Y;
	cin >> x;
	_asm 
	{
		mov eax, x
		mul x
		cdq
		imul eax, 5
		cdq
		add eax, 2
		imul eax
		sub eax, 1
		mov Y, eax
	}
	cout << "\nY=(5*x*x+2)^2-1 =  " << Y << endl<<endl;

	// 2) Y=(2+(50*x*x+1)/(6+x*x)) 
	cout << "enter x = ";
	int delitel; 
	cin >> x;
	int q; 
	_asm
	{
		mov eax, x
		mul x
		cdq
		mov q, 50
		mul q
		cdq
		add eax, 1
		mov ebx, eax
		mov eax, x
		mul x
		cdq
		add eax, 6
		mov delitel, eax
		mov eax, ebx
		idiv delitel
		add eax, 2
		mov Y, eax
	}

	cout << "\nY=(2+(50*x*x+1)/(6+x*x)) =  " << Y << endl << endl;

	//   3)  a(a1,a2)*b(b1,b2)
	int x1, x2, y1, y2;
	cout << "enter coordinates. vector 1: ";
	cin >> x1 >> y1;
	cout << "enter coordinates. vector 2: ";
	cin >> x2 >> y2;
	int summa;
	_asm 
	{
		mov eax, x1
		imul x2
		cdq
		mov ebx, eax
		mov eax, y1
		imul y2
		cdq
		add eax, ebx
		mov summa, eax
	}
	cout << "\nv1*v2 = x1*x2 + y1*y2 =  " << summa << endl << endl;

	//  4) S*S
	cout << "enter lengths of the triangle\na, b, c = ";
	int a, b, c, p;
	cin >> a >> b >> c;
	while (a + b <= c || a + c <= b || b + c <= a || a<=0 || b<=0 || c<=0)
	{
		cout << "incorrect a,b,c. Try again.\na,b,c = ";
		cin >> a >> b >> c;
	}
	int h = 2, w;
	_asm
	{
		mov eax, 0
		add eax, a
		add eax, b
		add eax, c
		cdq
		div h
		mov p, eax
		mov w, eax
		// p = (a + b + c)/2
		sub eax, c
		mul p
		cdq
		mov p, eax
		// p = p*(p-c)
		mov eax, w
		sub eax, b
		mul p
		cdq
		mov p, eax
		//  p = p*(p-c)*(p-b)
		mov eax, w
		sub eax, a
		mul p
		// eax = p*(p-c)*(p-b)*(p-a)
		cdq
		mov p, eax
	}
	cout << "\nS*S = " << p << endl;
	system("pause");
	return 0;
}