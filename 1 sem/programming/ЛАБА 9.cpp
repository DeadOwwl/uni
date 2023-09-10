#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <string>
using namespace std;
void ToLower(string str) {
	int i = 0;
	while (str[i]){
		str[i] = tolower(str[i]);
		i++;
	}
}
string DeleteWord(string buf, string delited) {
	int nach(0), kon(0);
	string slovo1, razd = " ";
	buf += " ";
	while ((nach = buf.find_first_not_of(razd, nach)) != -1) {
		kon = buf.find_first_of(razd, nach);
		slovo1 = buf.substr(nach, kon - nach);
		if (delited.compare(slovo1) == 0) {
			buf.erase(nach, delited.length());
			nach = 0;
		}
		else nach = kon;
	}
	return buf;
}
int main() {
	setlocale(0,"");
	ifstream input;
	input.open("C:\\Users\\aowl2\\source\\repos\\Лаба 9, номер 15\\input.txt");
	ofstream output; 
	output.open("C:\\Users\\aowl2\\source\\repos\\Лаба 9, номер 15\\output.txt");
	if (!input.is_open()) {
		cout << "Ошибка открытия файла ввода.\n";
		input.close();
		return -1;
	}
	if (!output.is_open()) {
		cout << "Ошибка открытия файла вывода.\n";
		output.close();
		return -1;
	}
	string a, A;
	while (!input.eof()) {
		getline(input, a, '\n');
		A += a;
	}
	if (A.find_first_not_of(" ", 0) == -1) {
		cout << "Входной файл пустой.\n";
		input.close();
		output.close();
		return -1;
	}
	string String;
	int NumberOfStrings(0);
	input.seekg(0, 0);
	while (!input.eof()) {
		getline(input, String, '\n');
		NumberOfStrings++;
	}
	input.seekg(0, 0);
	string Word, Buffer, ArrayOfWords[1000], ArrayOfRep[1000];
	int StringNumber(1), Left(0), Right(0), Flag(0), NumElements(0), i(0);
	getline(input, String, '\n');
	while (!input.eof()) {
		Buffer = String;
		ToLower(Buffer);
		if (StringNumber != NumberOfStrings) {
			Buffer.pop_back();
			Buffer += " ";
		}
		else Buffer += " ";
		while ((Left = Buffer.find_first_not_of(" ", Left)) != -1) {
			Right = Buffer.find_first_of(" ", Left);
			Word = Buffer.substr(Left, Right - Left);
			Left = Right;
			Flag = 1;
			for (i = 0; i < NumElements; i++) {
				if (ArrayOfWords[i].compare(Word) == 0) {
					ArrayOfRep[i] += " ";
					ArrayOfRep[i] += to_string(StringNumber);
					Flag = 0;
				}
			}
			if (Flag) {
				ArrayOfWords[NumElements] = Word;
				ArrayOfRep[i] += " ";
				ArrayOfRep[i] += to_string(StringNumber);
				NumElements++;
			}
			Buffer = DeleteWord(Buffer, Word);
			Left = 0, Right = 0;
		}
		StringNumber++;
		Left = 0, Right = 0;
		getline(input, String, '\n');
    }
	for (i = 0; i < NumElements; i++) {
		ArrayOfWords[i].append(ArrayOfRep[i]);
		ArrayOfWords[i] += '\n';
		output << ArrayOfWords[i];
	}
	cout << "Предметный указатель составлен. Результат находится в файле вывода output.txt.\n";
	input.close();
	output.close();
    return 0;
}