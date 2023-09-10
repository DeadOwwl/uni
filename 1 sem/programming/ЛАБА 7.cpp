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
	cout << "������� ������ ������, ��������� �� ��������� ���� � ������������ ��������� ��������: \n";
	getline(cin, FirstString);
	cout << "������� ������ ������, ��������� �� ��������� ���� � ������������ ��������� ��������: \n";
	getline(cin, SecondString);

	//��������
	if (FirstString.find_first_of(Letters, Left) == -1 || FirstString.empty() || SecondString.find_first_of(Letters, Left) == -1 || SecondString.empty()) {
		cout << "��������� ������ ������� �� ������������. ������������� ��������� ��� ���������� ������.\n";
		return 0;
	}
	int FirstCount = 0, SecondCount = 0;
	Left = 0, Right = 0;

	//���������� ���� ������ ������
	while (FirstString.find_first_of(Letters, Left) != -1) {
		Left = FirstString.find_first_of(Letters, Left);
		Right = FirstString.find_first_not_of(Letters, Left);
		FirstCount++;
		Left = Right;
	}
	Left = 0, Right = 0;
	string* FirstWords = new string[FirstCount];

	//���������� ���� ������ ������
	while (SecondString.find_first_of(Letters, Left) != -1) {
		Left = SecondString.find_first_of(Letters, Left);
		Right = SecondString.find_first_not_of(Letters, Left);
		SecondCount++;
		Left = Right;
	}
	Left = 0, Right = 0;
	string* SecondWords = new string[SecondCount];
	int x1 = 0, x2 = 0;

	//��������� ���� ������ ������ � ������
	while (FirstString.find_first_of(Letters, Left) != -1) {
		Left = FirstString.find_first_of(Letters, Left);
		Right = FirstString.find_first_not_of(Letters, Left);
		FirstWords[x1] = FirstString.substr(Left, Right - Left);
		x1++;
		Left = Right;
	}
	Left = 0, Right = 0;

	//��������� ���� ������ ������ � ������
	while (SecondString.find_first_of(Letters, Left) != -1) {
		Left = SecondString.find_first_of(Letters, Left);
		Right = SecondString.find_first_not_of(Letters, Left);
		SecondWords[x2] = SecondString.substr(Left, Right - Left);
		x2++;
		Left = Right;
	}
	string FinalString="";
	int i = 0, k = 0;

	//��������������� ��������� � �������� ����� ������
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
	cout << "�������� ������ ����� ��������������: \n" << FinalString;
	delete[] FirstWords;
	delete[] SecondWords;
	return 0;
}