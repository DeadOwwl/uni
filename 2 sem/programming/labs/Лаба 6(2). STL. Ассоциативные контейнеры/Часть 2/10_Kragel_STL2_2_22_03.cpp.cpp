#include <iostream>
#include <fstream>
#include <numeric>
#include <functional>
#include <map>
#include <iterator>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cctype>

using namespace std;

ifstream Input("D:\\alink\\bsu\\2 s\\prog\\labs\\Лаба 6, STL Ассоциативные Контейнеры. Задание 2\\in.txt");
ofstream Output("D:\\alink\\bsu\\2 s\\prog\\labs\\Лаба 6, STL Ассоциативные Контейнеры. Задание 2\\out.txt");

void fCheck()
{
	if (!Input.is_open())
		throw "Ошибка открытия файла ввода.";
	if (!Output.is_open())
		throw "Ошибка открытия файла вывода.";
	if (Input.peek() == EOF)
		throw "Файл ввода пуст.";
}

string fToLower(string w)
{
	for (unsigned i(0); i < w.size(); i++)
		w[i] = tolower(w[i]);
	return w;
}

int main()
{
	try
	{
		setlocale(0, "");
		fCheck();
		map <string, int> M;
		while (!Input.eof())
		{
			string w;
			bool flComp(false);
			Input >> w;
			w = fToLower(w);
			map <string, int>::iterator i = M.begin();
			for (i; i != M.end(); i++)
				if (w == i->first)
				{
					flComp = true;
					break;
				}
			if (flComp == true)
				i->second++;
			else
				M.insert(make_pair(w, 1));
		}
		map <string, int>::iterator i = M.begin();
		Output << "Частотный словарь для документа:\n";
		for (i; i != M.end(); i++)
			Output << i->first << " - " << i->second << endl;
		cout << "Программа выполнена успешно. Проверьте файлы вывода.\n";
		Input.close();
		Output.close();
		return 0;
	}
	catch (const char* Error)
	{
		cout << Error << endl;
		Input.close();
		Output.close();
	}
}