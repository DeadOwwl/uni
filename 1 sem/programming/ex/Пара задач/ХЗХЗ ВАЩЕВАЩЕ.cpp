#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <string>
#include <cstring>
#include <io.h>
#include <cmath>
#include <windows.h>
#include <algorithm>

using namespace std;

fstream Fo("SKLAD.DAT", ios::binary);
ifstream Ch("DEN.DAT", ios::binary);

void CheckFiles()
{
	if (!Fo.is_open())
		throw "Ошибка открытия файла с информацией о продукции на складе";
	if (!Ch.is_open())
		throw "Ошибка открытия файла с изменениями продукции на складе";
	if (Fo.peek() == EOF)
		throw "Файл с информацией о продукции на складе пуст";
	if (Ch.peek() == EOF)
		throw "Файл с изменениями продукции на складе пуст";
}

struct Good {
	string Cipher;
	string VendorCode;
	string Name;
	int Quantity;
	int Change;
	int AfterQ;
};

int main()
{
	setlocale(0, "");
	try
	{
		CheckFiles();
		Good Array[100];
		int i(0);
		while (!Fo.eof())
		{
			for (int j(0); j < 7; j++)
			{
				char s;
				Fo.get(s);
				Array[i].Cipher += s;
			}
			for (int j(0); j < 5; j++)
			{
				char s;
				Fo.get(s);
				Array[i].VendorCode += s;
			}
			for (int j(0); j < 15; j++)
			{
				char s;
				Fo.get(s);
				Array[i].Name += s;
			}
			string Temp;
			for (int j(0); j < 7; j++)
			{
				char s;
				Fo.get(s);
				Temp += s;
			}
			Array[i].Quantity = stoi(Temp);
		}
		Fo.ignore(27, '\n');
		string Temp;
		for (int j(0); j < 7; j++)
		{
			char s;
			Fo.get(s);
			Temp += s;
		}
		Array[i].Change = stoi(Temp);
		Array[i].AfterQ = Array[i].Quantity + Array[i].Change;
		cout << "Информация из файлов считана.\nЖелаете записать результаты в файл?\n\t1 - Да\n\t2 - Нет\n";
		int Choice;
		cin >> Choice;
		while (Choice != 1 && Choice != 2)
		{
			cout << "Недопустимый вариант. Попробуйте снова.\n";
			cin >> Choice;
		}
		switch (Choice)
		{
		case 1:
		{
			ofstream Output("Output.txt");
			for (int j(0); j <= i; j++)
			{
				Output << "Шифр товара: " << Array[i].Cipher << endl 
					<< "Артикул товара: " << Array[i].VendorCode << endl 
					<< "Наименование товара: " << Array[i].Name << endl 
					<< "Артикул товара: " << Array[i].AfterQ << endl;
			}
		}
		case 2:
		{
			cout << "Выполнениe программы завершено.";
			system("pause");
			return 0;
		}
		}

		i++;
	}
	catch (const char* Error)
	{
		cout << Error;
		return 0;
	}
	return 0;
}