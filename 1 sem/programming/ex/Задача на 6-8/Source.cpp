/*5. Составить программу решения следующей задачи:
В текстовом файле записаны строки длиной не более 255 символов, слова в которых разделены хотя бы одним
пробелом или знаками препинания. В каждой строке найти слова, являющиеся простыми числами и поменять местами
максимальное и минимальное. Если максимальных и/или минимальных чисел несколько, то брать последнее. Результаты 
записать в новый текстовый файл, сохраняя все разделители. */
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

ifstream fin;
ofstream fout;

bool simple(int k)
{
	int g = 0;
	for (int i = 1; i < k / 2 + 1; i++)
	{
		if (k % i == 0)
			g++;
		if (g > 1)
			return false;
	}
	if (g <= 1)
		return true;
}

int main()
{
	setlocale(LC_ALL, "rus");
	fin.open("input.txt");
	fout.open("output.txt");
	if (!fin.is_open())
	{
		cout << "Входной файл не открылся!\n";
		fin.close();
		fout.close();
		system("pause");
		return 0;
	}
	if (!fout.is_open())
	{
		cout << "Выходной файл не открылся\n";
		fin.close();
		fout.close();
		system("pause");
		return 0;
	}
	string str;
	getline(fin, str);
	if (str == "")
	{
		cout << "Входной файл пустой\n";
		fin.close();
		fout.close();
		system("pause");
		return 0;
	}
	do
	{
		int a = 0, b;
		int kolvo = 0;
		int fmax = 0, fmin = 0, f1, f2;
		cout << "str = " << str << endl;
		while ((a = str.find_first_not_of(" ,.;:", a)) != -1)
		{
			b = str.find_first_of(" ,.;:", a);
			string d = str.substr(a, b - a);
			int f;
			if (d.find_first_not_of("1234567890+", 0) != -1)
				f = -1;
			else
				f = atoi(d.c_str());
			cout << "d = " << d << "\tf = " << f << endl;
			if (f > 0 && simple(f))
			{
				if (kolvo == 0)
				{
					fmax = fmin = f;
					f1 = f2 = a;
				}
				else
				{
					if (f >= fmax)
					{
						fmax = f; f1 = a;
					}
					if (f <= fmin)
					{
						fmin = f; f2 = a;
					}
				}
				kolvo++;
			}
			a = b;
		}
		if (fmax == fmin || kolvo <= 1)
		{
			fout << str << endl;
		}
		else
		{
			cout << "fmin = " << fmin << "\tfmax = " << fmax << "\tf1 = " << f1 << "\tf2 = " << f2 << endl;
			if (f1 < f2)
			{
				str.replace(f2, to_string(fmin).length(), to_string(fmax));
				str.replace(f1, to_string(fmax).length(), to_string(fmin));
			}
			else
			{
				str.replace(f1, to_string(fmax).length(), to_string(fmin));
				str.replace(f2, to_string(fmin).length(), to_string(fmax));
			}
			fout << str << endl;
		}
	} while (getline(fin, str));
	fin.close();
	fout.close();
	system("pause");
	return 0;
}