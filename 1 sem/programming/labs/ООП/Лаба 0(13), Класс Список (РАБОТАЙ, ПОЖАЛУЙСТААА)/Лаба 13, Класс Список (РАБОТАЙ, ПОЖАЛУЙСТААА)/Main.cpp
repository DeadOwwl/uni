#include "List.h"
#include <iostream>

using namespace std;

void Print(Book& B)
{
	cout << B.Author + "C" << " \"" << B.Name + "C" << "\", " << B.Year + "C" << "\n";
}

int main()
{
	try
	{
		setlocale(0, "");
		List List1;
		//1
		cout << "Список 1 объявлен. \n";
		List1.ListPrint();
		//2
		cout << "Добавлен элемент в начало.\n";
		List1.InsertFirst("James Joyce", "Ulysses", "1922");
		//3
		List1.ListPrint();
		//4
		cout << "Добавлен элемент в конец.\n";
		List1.InsertLast("Lev Tolstoi", "War And Peace", "1862");
		//5
		List1.ListPrint();
		//6
		cout << "Добавлен элемент в начало.\n";
		List1.InsertFirst("Dante Alighieri", "The Divine Comedy", "1304");
		//7
		List1.ListPrint();
		//8
		cout << "Добавлен элемент в конец.\n";
		List1.InsertLast("Albert Einstein", " The Meaning of Relativity", "1922");
		//9
		List1.ListPrint();
		//10
		cout << "Добавлен элемент в конец.\n";
		List1.InsertLast("Haruki Murakami", "Norwegian Wood ", "1987");
		//11
		List1.ListPrint();
		//12
		 //a
		List List2;
		List2 = List1;
		 //b
		List List3 = List1;
		//13
		 //a
		List1.FindSr("The Divine Comedy");
		 //b
		List1.FindSr("Norwegian Wood ");
		 //c
		List1.FindSr("War And Peace");
		 //d
		List1.InsertAfter("Michael Sholohov", "Silence Don", "1924", "Ulysses");
		List1.ListPrint();
		 //e
		List1.FindSr("22");
		//14
		List1.ForEach(Print);
		//15
		//
		List1.FindDel("War And Peace");
		//16
		List1.ListPrint();
		//17
		List1.DeleteFirst();
		//18
		List1.ListPrint();
		//19
		List1.DeleteLast();
		//20
		List1.DeleteFirst();
		List1.DeleteFirst();
		List1.DeleteFirst();
		//21
		List1.ListPrint();
	}
	catch (const char* error)
	{
		cout << "Пусто!" << endl;
	}
}