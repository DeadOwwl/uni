#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <string>
#include "Tree.h"

using namespace std;

ifstream input("C:\\Users\\aowl2\\Desktop\\bsu\\2 s\\prog\\pr\\Бинарное Дерево (Класс)\\INPUT.txt");
ofstream output("C:\\Users\\aowl2\\Desktop\\bsu\\2 s\\prog\\pr\\Бинарное Дерево (Класс)\\OUTPUT.txt");

void Print(int& ss)
{
	output << ss << " ";
}

void Check() {
	if (!input.is_open()) {
		cout << "Ошибка открытия файла ввода.\n";
		input.close();
	}
	if (!output.is_open()) {
		cout << "Ошибка открытия файла вывода.\n";
		output.close();
	}
}

int main()
{ 
	try {
		setlocale(0, "");
		string a, A;
		int k;
		bool b;
		Tree tree;
		while (!input.eof())
		{
			input >> a;
			if (a == "I")
			{
				input >> a;
				k = stoi(a);
				b = tree.Add(k);
				if (b == true)
					output << "inserted\n";
				else
					output << "not inserted\n";
			}
			else
				if (a == "D")
				{
					input >> a;
					k = stoi(a);
					b = tree.Remove(k);
					if (b == true)
						output << "deleted\n";
					else
						output << "not deleted\n";
				}
				else
					if (a == "F")
					{
						input >> a;
						k = stoi(a);
						int p(0);
						b = tree.FindByValue(k, p);
						if (b == true)
							output << "found after " << p << " comparisons\n";
						else
							output << "not found after " << p << " comparisons\n";
					}
					else
						if (a == "L")
						{
							if (tree.RootCheck())
							{
								output << "List of elements:\n";
								tree.Walk(Print);
								output << endl;
							}
							else
								output << "Empty\n";
						}
		}
		Tree tree11 = tree;
	}
	catch (const char* error)
	{
		cout << error << endl;
		input.close();
		output.close();
	}
	return 0;
}