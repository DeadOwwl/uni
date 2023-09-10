#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cctype>
#pragma warning(disable:4996)
using namespace std;
string ToLower(string str) {
	int i = 0;
	while (str[i]) {
		str[i] = tolower(str[i]);
		i++;
	}
	return str;
}
int main() {
	setlocale(0, "");
	FILE* In;
	FILE* Out;
	In = fopen("C:\\Users\\aowl2\\source\\repos\\���� 8, ����� 14\\input.txt", "r");
	Out = fopen("C:\\Users\\aowl2\\source\\repos\\���� 8, ����� 14\\output.txt", "w");

	//�������� �� ����������� �������� �����
	if (!In) {
		cout << "������ �������� �����." << endl;
		return -1;
	}

	//�������� �� ������� �����
	string  A;
	char a[1000];
	while (!feof(In)) {
		fgets(a, 100, In);
		A += (string)a;
	}
	if (A.find_first_not_of(" ", 0) == -1) {
	cout << "���� ������." << endl;
	fclose(In);
	system("pause");
	return -1;
    }
	rewind(In);
	char FirstStringCh[300];
	string String, StringOne, StringTwo;
	fgets(FirstStringCh, 100, In);
	String = string(FirstStringCh);

	//�������� �� ������� ���� � ������
	if (String.find_first_not_of(" \n", 0) == -1){
		cout << "� ������ ������ ��� ����" << endl;
		fclose(In);
		return -1;
	}

	//�������� �� ������������ ���������� ���� � ������ ������
	int Left(0), Right(0), i(0);
	int Count(0);
	while (String.find_first_not_of(" \n", Left) != -1) {
		Left = String.find_first_not_of(" \n", Left);
		Right = String.find_first_of(" \n", Left);
		Count++;
		Left = Right;
	}
	if (Count != 2) {
		cout << "���������� ���� � ������ ������ �� ������������� ������������." << endl;
		return -1;
	}
	Left = 0, Right = 0;
	Left = String.find_first_not_of(" \n", Left);
	Right = String.find_first_of(" \n", Left);
	StringOne = String.substr(Left, Right - Left);
	Left = String.find_first_not_of(" \n", Right);
	Right = String.find_first_of(" \n", Left);
	StringTwo = String.substr(Left, Right - Left);
	Left = 0, Right = 0;

	//�������� �� ������������ ���� ������ ������ 
	if (ToLower(StringOne) == ToLower(StringTwo)) {
		cout << "� ������ ������ ������������� ��� ���������� �����." << endl;
		return -1;
	}

	cout << "�������� ����� \"" << StringOne << "\" �� \"" << StringTwo <<"\" � ��������." << endl;
	char TextCh[300];
	string Text;
	int TextCount(0);
	while (fgets(TextCh, 300, In) != NULL) Text += string(TextCh) + " ";
	cout << "�������������� �����: " << endl << Text << endl << endl;
	string Word;
	int NumberOfWords(0);
	Left = 0, Right = 0;
	while (Text.find_first_not_of(" ", Left) != -1) {
		Left = Text.find_first_not_of(" ", Left);
		Right = Text.find_first_of(" ", Left);
		Left = Right;
		NumberOfWords++;
	}
	Left = 0, Right = 0;
	string* TextArray = new string[NumberOfWords+1];
	for (i = 0; i < NumberOfWords; i++) {
		Left = Text.find_first_not_of(" ", Left);
		Right = Text.find_first_of(" ", Left);
		Word = Text.substr(Left, Right - Left);
		TextArray[i] = Word;
		Left = Right;
	}
	int FirstFlag(1), SecondFlag(1);
	int FirstInd(0), SecondInd(0);
	for (i = 0; i < NumberOfWords; i++) {
		if (TextArray[i] == StringOne) {
			FirstFlag = 0;
			FirstInd = i;
			break;
		}
		if (TextArray[i] == StringTwo) {
			SecondFlag = 0;
			SecondInd = i;
			break;
		}
	}
	for (i=NumberOfWords-1;  i>=0 ; i--) {
		if (TextArray[i] == StringOne && FirstFlag != 0) {
			FirstFlag = 0;
			FirstInd = i;
			break;
		}
		if (TextArray[i] == StringTwo && SecondFlag != 0) {
			SecondFlag = 0;
			SecondInd = i;
			break;
		}
	}
	if (FirstFlag == 0 && SecondFlag == 0) {
		TextArray[FirstInd] = StringTwo;
		TextArray[SecondInd] = StringOne;
	}
	else {
		cout << "� ������ ��� ���� ��� ������.\n";
		return -1;
	}
	string NewText;
	for (int i = 0; i < NumberOfWords; i++) NewText += TextArray[i] += " ";
	cout << "���������� �����: \n" << NewText << endl;
	int NLength = NewText.length();
	char* NewTextCh = new char[NLength+1];
	strcpy(NewTextCh, NewText.c_str());
	fputs(NewTextCh, Out);
	fclose(In);
	fclose(Out);
	delete[] TextArray;
	delete[] NewTextCh;
	return 0;
}