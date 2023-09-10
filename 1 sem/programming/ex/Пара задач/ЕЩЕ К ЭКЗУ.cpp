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

ifstream Input("C:\\Users\\aowl2\\source\\repos\\Еще к экзу\\in.txt");

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
	if (!Input.is_open()) throw "Ошибка открытия файла.";
	if (Input.peek() == EOF) throw "Ошибка, файл пуст.";
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
			cout << "Имя искомого абонента: " << Current->FIO << endl << "Номер искомого абонента: " << Current->Number << endl;
			break;
		}
		Current = Current->Next;
	}
	if (Current == NULL) cout << "Абонента с таким именем не найдено.\n";
}

void FindItemNumber(List* MainList, string number) {
	Sprav* Current = MainList->First;
	if (Current == NULL) cout << "Список пуст.";
	while (Current != NULL) {
	if (Current->Number == number) {
		cout << "Имя искомого абонента: " << Current->FIO << endl << "Номер искомого абонента: " << Current->Number << endl;
		break;
		}
		Current = Current->Next;
	}
	if (Current == NULL) cout << "Абонента с таким именем не найдено.\n";
}

void ShowList(List* MainList) {
	Sprav* Current = MainList->First;
	if (Current == NULL) cout << "Список пуст.\n";
	while (Current) {
		cout << "ФИО: " << Current->FIO << endl << "Номер: " << Current->Number << endl;
		Current = Current->Next;
	}
}

void DeleteList(List* MainList) {
	Sprav* Current = MainList->First;
	if (Current == NULL) cout << "Список пуст.\n";
	while (Current != NULL) {
		Sprav* P = Current;
		Current = Current->Next;
		delete P;
	}
	MainList->First = NULL;
	cout << "Список удален.\n";
}

void Menu(int &Choice) {
	cout << "Главное меню:\n2. Найти абонента по ...\n3. Показать список абонентов. \n4. Очистить список.\n0. Выйти из программы.\n";
	cin >> Choice;
	system("cls");
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try {
		StreamCheck();
		setlocale(0, "");
		cout << "Добро пожаловать в программу для работы с абонентскими номерами!\n";
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
				cout << "1. ... фамилии.\n2. ...номеру.\n";
				cin >> Choice;
				system("cls");
				if (Choice == 1) {
					cout << "Введите фамилию: ";
					string name;
					cin.ignore(1024, '\n');
					getline(cin, name);
					FindItemFIO(&MainList, name);
				}
				if (Choice == 2) {
					cout << "Введите номер: ";
					string number;
					cin.ignore(1024, '\n');
					getline(cin, number);
					FindItemNumber(&MainList, number);
				}
				cout << "1. Вернуться в меню.\n0. Завершить работу с программой.\n";
				cin >> Choice;
				if (Choice == 1) {
					system("cls");
				}
				break;
			case 3:
				ShowList(&MainList);
				cout << "1. Вернуться в меню.\n0. Завершить работу с программой.\n";
				cin >> Choice;
				if (Choice == 1) {
					system("cls");
				}
				break;
			case 4:
				DeleteList(&MainList);
				cout << "1. Вернуться в меню.\n0. Завершить работу с программой.\n";
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