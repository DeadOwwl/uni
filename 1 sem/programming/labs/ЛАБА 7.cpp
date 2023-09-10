#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string ToLower(string str) {
	int i = 0;
	string buff = "";
	while (str[i]) {
		char character = str[i];
		buff += tolower(character);
		i++;
	}
	return buff;
}

int main() {
	setlocale(0, "");
	string Letters = "QWERTYUIOPLKJHGFDSAZXCVBNMqwertyuioplkjhgfdsazxcvbnm";
	int Position = 0, Length = 0;
	int Left = 0, Right = 0;
	string FirstString, SecondString;
	cout << "Введите первую строку, состоящую из латинских букв и разделителей остальных символов: \n";
	getline(cin, FirstString);
	cout << "Введите вторую строку, состоящую из латинских букв и разделителей остальных символов: \n";
	getline(cin, SecondString);

	//Проверка
	if (FirstString.find_first_of(Letters, Left) == -1 || FirstString.empty() || SecondString.find_first_of(Letters, Left) == -1 || SecondString.empty()) {
		cout << "Введенные строки состоят из резделителей. Перезапустите программу для корректной работы.\n";
		return 0;
	}
	int FirstCount = 0, SecondCount = 0;
	Left = 0, Right = 0;

	//Количество слов первой строки
	while (FirstString.find_first_of(Letters, Left) != -1) {
		Left = FirstString.find_first_of(Letters, Left);
		Right = FirstString.find_first_not_of(Letters, Left);
		FirstCount++;
		Left = Right;
	}
	Left = 0, Right = 0;
	string* FirstWords = new string[FirstCount];

	//Количество слов сторой строки
	while (SecondString.find_first_of(Letters, Left) != -1) {
		Left = SecondString.find_first_of(Letters, Left);
		Right = SecondString.find_first_not_of(Letters, Left);
		SecondCount++;
		Left = Right;
	}
	Left = 0, Right = 0;
	string* SecondWords = new string[SecondCount];
	int x1 = 0, x2 = 0;

	//Выделение слов первой строки в массив
	while (FirstString.find_first_of(Letters, Left) != -1) {
		Left = FirstString.find_first_of(Letters, Left);
		Right = FirstString.find_first_not_of(Letters, Left);
		FirstWords[x1] = FirstString.substr(Left, Right - Left);
		x1++;
		Left = Right;
	}
	Left = 0, Right = 0;

	//Выделение слов второй строки в массив
	while (SecondString.find_first_of(Letters, Left) != -1) {
		Left = SecondString.find_first_of(Letters, Left);
		Right = SecondString.find_first_not_of(Letters, Left);
		SecondWords[x2] = SecondString.substr(Left, Right - Left);
		x2++;
		Left = Right;
	}
	string FinalString="";
	int i = 0, k = 0;

	//Непосредственно сравнение и создание новой строки
	while (i < FirstCount && k < SecondCount) {
		if (ToLower(FirstWords[i]) < ToLower(SecondWords[k])) {
			FinalString += FirstWords[i] += ' ';
			i++;
		}
		else {
			FinalString += SecondWords[k] += ' ';
			k++;
		}
	}
	if (i < FirstCount) {
		while (i < FirstCount) {
			FinalString += FirstWords[i] += ' ';
			i++;
			k++;
		}
	}
	else {
		while (k < SecondCount) {
			FinalString += SecondWords[k] += ' ';
			k++;
			i++;
		}
	}
	cout << "Итоговая строка после преобразований: \n" << FinalString;
	delete[] FirstWords;
	delete[] SecondWords;
	return 0;
}