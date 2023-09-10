#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <fcntl.h>
#include <Windows.h>
#include <string>

using namespace std;

struct Comp1
{
	int Num = 0;
	Comp1* Next = NULL;
	Comp1* Previously = NULL;
};

struct ListDouble
{
	Comp1* First = NULL;
	Comp1* Last = NULL;
};

void AddItem1(ListDouble* MainList, int n)
{
	Comp1* Current = new Comp1;
	//Current->Next = NULL;
	Current->Num = n;
	if (MainList->First == NULL)
	{
		//Current->Previously = NULL;
		MainList->First = MainList->Last = Current;
	}
	else
	{
		Current->Previously = MainList->Last;
		MainList->Last->Next = Current;
		MainList->Last = Current;
	}
}

void ShowReverseList(ListDouble* MainList)
{
	Comp1* Current = MainList->Last;
	while (Current != NULL)
	{
		cout << Current->Num << "  " << endl;
		Current = Current->Previously;
	}
}

int main()
{
	try
	{
		setlocale(0, "");
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		ListDouble MainList;
		MainList.First = MainList.Last;
		for (int i(0); i < 5; i++)
			AddItem1(&MainList, i);
		cout << "Добавление выполнено успешно.\n";
		ShowReverseList(&MainList);
		return 0;
    }
	catch (const char* Error)
	{
		cout << Error << endl;
		return 0;
	}
}