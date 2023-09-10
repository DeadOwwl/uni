#include <iostream>
#include <string>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

using namespace std;

ifstream Input("C:\\Users\\aowl2\\source\\repos\\��� � ����\\in.txt");

struct Sprav {
	string FIO;
	string Number;
	//Sprav* Previously = NULL;
	Sprav* Next = NULL;
};

struct List {
	Sprav* First = NULL;
};

void StreamCheck() {
	if (!Input.is_open()) throw "������ �������� �����.";
	if (Input.peek() == EOF) throw "������, ���� ����.";
}

int Sort(List* MainList) {
	if (MainList->First == NULL) {
		return 0;
	}
	else {
		if (MainList->First->Next == NULL) return 0;
	    else {
		Sprav* Left = MainList->First;
		Sprav* Right = MainList->First->Next;
		while (Left->Next) {
			while (Right) {
				if (Left->FIO > Right->FIO) {
					string tmp;
					tmp = Left->FIO;
					Left->FIO = Right->FIO;
					Right->FIO = tmp;
					tmp = Left->Number;
					Left->Number = Right->Number;
					Right->Number = tmp;
				}
				Right = Right->Next;
			}
			Left = Left->Next;
			Right = Left->Next;
		}
		return 0;
	    }
	}
}

void FindItemFIO(List* MainList, string fio) {
	Sprav* Current = MainList->First;
	while (Current != NULL) {
		if (Current->FIO == fio) {
			cout << "��� �������� ��������: " << Current->FIO << endl << "����� �������� ��������: " << Current->Number << endl;
			break;
		}
		Current = Current->Next;
	}
	if (Current == NULL) cout << "�������� � ����� ������ �� �������.\n";
}

void FindItemNumber(List* MainList, string number) {
	Sprav* Current = MainList->First;
	if (Current == NULL) cout << "������ ����.";
	while (Current != NULL) {
	if (Current->Number == number) {
		cout << "��� �������� ��������: " << Current->FIO << endl << "����� �������� ��������: " << Current->Number << endl;
		break;
		}
		Current = Current->Next;
	}
	if (Current == NULL) cout << "�������� � ����� ������ �� �������.\n";
}

void ShowList(List* MainList) {
	Sprav* Current = MainList->First;
	if (Current == NULL) cout << "������ ����.\n";
	while (Current) {
		cout << "���: " << Current->FIO << endl << "�����: " << Current->Number << endl;
		Current = Current->Next;
	}
}

void DeleteList(List* MainList) {
	Sprav* Current = MainList->First;
	if (Current == NULL) cout << "������ ����.\n";
	while (Current != NULL) {
		Sprav* P = Current;
		Current = Current->Next;
		delete P;
	}
	MainList->First = NULL;
	cout << "������ ������.\n";
}

void Menu(int &Choice) {
	cout << "������� ����:\n2. ����� �������� �� ...\n3. �������� ������ ���������. \n4. �������� ������.\n0. ����� �� ���������.\n";
	cin >> Choice;
	system("cls");
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try {
		StreamCheck();
		setlocale(0, "");
		cout << "����� ���������� � ��������� ��� ������ � ������������ ��������!\n";
		int Choice(1);
		List MainList;
		MainList.First = NULL;
		while (!Input.eof()) {
			Sprav* Current = new Sprav;
			Current->FIO = "";
			for (int k(0); k < 3; k++) {
				string str("");
				Input >> str;
				Current->FIO += str += ' ';
			}
			Current->FIO.pop_back();
			Input >> Current->Number;
			Current->Next = MainList.First;
			MainList.First = Current;
			Sort(&MainList);
		}
		while (Choice) {
			Menu(Choice);
			switch (Choice) {
			case 2:
				cout << "1. ... �������.\n2. ...������.\n";
				cin >> Choice;
				system("cls");
				if (Choice == 1) {
					cout << "������� �������: ";
					string name;
					cin.ignore(1024, '\n');
					getline(cin, name);
					FindItemFIO(&MainList, name);
				}
				if (Choice == 2) {
					cout << "������� �����: ";
					string number;
					cin.ignore(1024, '\n');
					getline(cin, number);
					FindItemNumber(&MainList, number);
				}
				cout << "1. ��������� � ����.\n0. ��������� ������ � ����������.\n";
				cin >> Choice;
				if (Choice == 1) {
					system("cls");
				}
				break;
			case 3:
				ShowList(&MainList);
				cout << "1. ��������� � ����.\n0. ��������� ������ � ����������.\n";
				cin >> Choice;
				if (Choice == 1) {
					system("cls");
				}
				break;
			case 4:
				DeleteList(&MainList);
				cout << "1. ��������� � ����.\n0. ��������� ������ � ����������.\n";
				cin >> Choice;
				if (Choice == 1) {
					system("cls");
				}
				break;
			}
		}
	}
	catch (const char* Error) {
		cout << Error;
		return 0;
	}
	Input.close();
	system("cls");
	system("pause");
	return 0;
}