#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace std;

ifstream Input("C:\\Users\\aowl2\\source\\repos\\что-то тоже к экзу\\in.txt");

void CheckFile() 
{
	if (!Input.is_open()) throw "Ошибка открытия файла";
	if (Input.peek() == EOF) throw "Ошибка: файл пуст";
}

int main()
{
	setlocale(0, "");
	setlocale(LC_NUMERIC, "C");
	double Sum(0);
	try
	{
		while (!Input.eof())
		{
			string String;
			string Word;
			string Necess = "123456789.";
			int Flag(0);
			getline(Input, String);
			int Left(0), Right(0);
			while (String.find_first_not_of(" ", Left) != -1) {
				Left = String.find_first_not_of(" ", Left);
				Right = String.find_first_of(" ", Left);
				Word = String.substr(Left, Right - Left);
				if (Word.find_first_of(Necess, 0) != -1) {
					double Num = stod(Word);
					Sum += Num;
					Flag = 1;
				}
				Left = Right;
			}
			if (Flag == 0)
				cout << "В строке нет вещественных чисел\n";
			else 
				cout << Sum << endl;
			Sum = 0;
			Left = 0; 
			Right = 0;
			Flag = 0;
		}
		
	}
	catch (const char* Error)
	{
		cout << Error;
		Input.close();
		return 0;
	}
	Input.close();
	return 0;
}