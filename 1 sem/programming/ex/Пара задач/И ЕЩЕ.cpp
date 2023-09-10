#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream Input("C:\\Users\\aowl2\\source\\repos\\и еще\\in.txt");
ofstream Output("C:\\Users\\aowl2\\source\\repos\\и еще\\out.txt");

void CheckFiles()
{
	if (!Input.is_open()) throw "Ошибка открытия файла ввода";
	if (!Output.is_open()) throw "Ошибка открытия файла вывода";
	if (Input.peek() == EOF) throw "Файл ввода пуст";
}

int main()
{
	setlocale(LC_ALL, ".1251");
	try
	{
		CheckFiles();
		string Deviders;
		string Word;
		string String;
		int flag(0);
		int anflag(0);
		int k(0);
		int pr(0);
		string Numbers("1234567890");
		getline(Input, Deviders);
		int arr[255][2];
		int i(0);
		while (!Input.eof())
		{
			getline(Input, String);
			k++;
			if (String.find_first_not_of(Deviders, 0) == -1)
				anflag++;
			int Left(0), Right(0);
			while (String.find_first_not_of(Deviders, Left) != -1)
			{
				Left = String.find_first_not_of(Deviders, Left);
				Right = String.find_first_of(Deviders, Left);
				Word = String.substr(Left, Right - Left);
				Left = Right;
				if (Word.find_first_of(Numbers, 0) != -1)
				{
					if (Word.find_first_not_of(Numbers, 0) != -1)
						continue;
					flag = 1;
					int lWord = Word.size();
					int Num = stoi(Word);
					int lNum(0);
					int CheckNum = Num;
					while (CheckNum != 0)
					{
						CheckNum /= 10;
						lNum++;
					}
					if (lNum != lWord)
						continue;
					CheckNum = Num;
					int Sum(0);
					while (CheckNum != 0)
					{
						Sum += CheckNum % 10;
						CheckNum /= 10;
					}
					CheckNum = Num;
					int dNum(0);
					for (int d(2); d <= Sum / 2; d++)
						if (Sum % d == 0)
							dNum++;
					if (dNum == 0)
					{
						pr = 1;
						arr[i][0] = Num;
						arr[i][1] = Sum;
						i++;
					}
				}
			}
		}
		int l(0), r(i);
		int w(0);
		for (l, r; l <= r;)
		{
			for (w = l; w <= r; w++)
			{
				if (arr[w][0] > arr[w + 1][0])
				{
					swap(arr[w][0], arr[w + 1][0]);
					swap(arr[w][1], arr[w + 1][1]);
				}
				r--;
			}
			for (w = r; w >= l; w--)
			{
				if (arr[w-1][0] > arr[w][0])
				{
					swap(arr[w][0], arr[w - 1][0]);
					swap(arr[w][1], arr[w - 1][1]);
				}
				l++;
			}
		}
		for (w = 0; w < i; w++)
			Output << arr[w][0] << "->" << arr[w][1] << endl;
		if (anflag == k) throw "Строки состоят из разделителей";
		if (flag == 0) throw "Целых чисел не обнаружено";
		if (pr == 0) throw "Слов-чисел, сумма цифр которых - простое число, не найдено";
	}
	catch (const char* Error)
	{
		cout << Error;
		return 0;
	}
	cout << "Программа выполнена!\n";
	return 0;
}