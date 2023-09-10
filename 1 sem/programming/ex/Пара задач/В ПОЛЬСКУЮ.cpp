#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <io.h>
#include <cstring>
#include <string>

using namespace std;

enum Optype { dev = 2, mul = 2, min = 1, pl = 1, null = 0 };

struct Stack
{
	char Data;
	Stack* Next;
	Optype type;
} 
*First;

void push(char S)
{
	Stack* Current = new Stack;
	Current->Data = S;
	Current->Next = First;
	First = Current;
}

char pop() 
{
	Stack* q = First;
	char p = First->Data;
	First = First->Next;
	free(q);
	return p;
}

bool isEmpty()
{
	return First == NULL;
}

int main()
{
	setlocale(LC_ALL, ".1251");
	try
	{
		string String;
		getline(cin, String);
		char temp(' ');
		Optype tp;
		Optype tpt;
		for (int i(0); i < String.length(); i++)
		{
			if (String[i] >= '0' && String[i] <= '9')
				cout << String[i];
			else
				if (String[i] == '(') push(String[i]);
				else
					if (String[i] == ')')
						while (temp != '(')
						{
							temp = pop();
							if (temp == '(')
							{
								temp = ' ';
								break;
							}
							else
								cout << temp;
							temp = ' ';
						}
					else
						if (String[i] == '+' || String[i] == '-' || String[i] == '*' || String[i] == '/')
						{
							if (String[i] == '+')
								tp = pl;
							if (String[i] == '-')
								tp = min;
							if (String[i] == '*')
								tp = mul;
							if (String[i] == '/')
								tp = dev;
							if (isEmpty())
								push(String[i]);
							else
								while (!isEmpty())
								{
									char t = pop();
									if (t == '+')
										tpt = pl;
									if (t == '-')
										tpt = min;
									if (t == '*')
										tpt = mul;
									if (t == '/')
										tpt = dev;
									if (t != '+' && t != '-' && t != '*' && t != '/')
										tpt = null;
									if ((t == '(') || (tpt < tp))
									{
										push(t);
										push(String[i]);
										break;
									}
									else
									{
										cout << t;
										push(String[i]);
										break;
									}
								}
						}
		}
		while (!isEmpty())
		{
			temp = pop();
			if (temp == '(' || temp == ')')
				break;
			else
				cout << temp;
		}
	}
	catch (const char* Error)
	{
		cout << Error;
		return 0;
	}
	return 0;
}