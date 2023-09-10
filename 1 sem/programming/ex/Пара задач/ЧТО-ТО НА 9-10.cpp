#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

fstream Stream("C:\\Users\\aowl2\\source\\repos\\К экзу 9-10\\f.txt");

void CheckOpen() {
	if (!Stream) throw "Ошибка открытия файла";
}

void CheckEmpty() {
	Stream.seekg(0);
	if (Stream.peek()==EOF) throw "Ошибка: файл пуст.";
}

void CheckWords() {
	string CheckString;
	string CheckWord;
	int k(0), t(0), i(0);
	while (!Stream.eof()) {
		getline(Stream, CheckString);
		while (i!=CheckString.length()) {
			k++;
			if (CheckString[i] == '.') t = 1;
			i++;
			if (k>=20) break;
		}
		if ((k < 20) && (t = 0)) throw "Недостаточно символов для работы с программой, отсутствует точка.";
		i = 0;
	}
	Stream.seekg(0);
}

int main() {
	setlocale(LC_ALL, ".1251");
	try {
		CheckOpen();
		CheckEmpty();
		CheckWords();
		int i(0), f(0), t(1), z(0);
		string String;
		while (!Stream.eof()) {
			Stream.seekp(z);
			char Symbol;
			Stream.get(Symbol);
			if ((Symbol == '.') && (f == 20)) {
				Stream.seekp(z);
				t++;
				Stream << "\n";
				f = 0;
				f++;
				z++;
				continue;
			}
			if (Symbol == '.') {
				Stream.seekp(z);
				t++;
				Stream << "\n";
				f = 0;
			}
			if (f==20) {
				Stream.seekp(z);
				t++;
				Stream << "\n";
				f = 0;
			}
			f++;
			z++;
		}
	}
	catch (const char* Error) {
		cout << Error << endl;
	}
	return 0;
}