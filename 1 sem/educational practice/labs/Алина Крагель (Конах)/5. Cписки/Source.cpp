#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <windows.h>
#include <fcntl.h>

using namespace std;

int i;

void Menu(int &Choice) {
	cout << "������� ����:\n1. ����������� ������ ���� ���������. \n2. ���������� ������ ��������. \n3. �������� �������� �� ���������... \n4. �������� ����� �������.\n5. ������� �������.\n0.��������� ������ � ����������.\n";
	cin >> Choice;
	system("cls");
}

struct ListItemBus {
	int Number;
	string NameInit;
	int Route;
	bool Status;
	ListItemBus* Next = NULL;
};

struct List {
	ListItemBus* First = NULL;
	ListItemBus* Current = NULL;
};

void FillingOut(List* MainList, int *i, ListItemBus* ListItem){
	//ListItemBus* ListItem = new ListItemBus();
	cout << "���������� " << *i+1 << "-��� ��������\n";
	cout << "����� ��������: �";
	cin >> ListItem->Number;
	cout << "������� � �������� ��������: ";
	cin.ignore(1024, '\n');
	getline (cin, ListItem->NameInit);
	string Word;
	int k(0), left(0), right(0);
	string StringCheck = ListItem->NameInit;
	while (StringCheck.find_first_not_of(" \n", left) != -1) {
		left = StringCheck.find_first_not_of(" \n", left);
		right = StringCheck.find_first_of(" \n", left);
		Word = StringCheck.substr(left, right - left);
		k++;
		left = right;
	}
	if (k != 2) throw "���������� ���� � ���� \"������� � �������� ��������\" �� ������������� ������������.";
	cout << "����� ��������: �";
	cin >> ListItem->Route;
	string StatusStr;
	cout << "��������� ��������\n\t *��������� ����� ��������, ��� \"�� ��������\" � \"� �����\": ";
	cin.ignore(1024, '\n');
	getline(cin, StatusStr);
	/*StatusStr.pop_back();
	StatusStr += ' ';*/
	if (StatusStr == "�� ��������") ListItem->Status = true;
	if (StatusStr == "� �����") ListItem->Status = false;
	if (StatusStr != "�� ��������" && StatusStr != "� �����") throw "�������� �������� ���� \"��������� ��������\"\n ";
	system("cls");
}

void AddItem(List *MainList, int k) {
	ListItemBus* Current_ = new ListItemBus;
	FillingOut(&*MainList, &k, Current_);
	Current_->Next = MainList->First;
	MainList->First = Current_;
}

void ShowList(List* MainList){
	ListItemBus* P = MainList->First;
	if (P == NULL) cout << "������ ����\n";
	while (P) {
		cout << "������� �" << P->Number << endl << "������� � �������� ��������: " << P->NameInit << endl << "������� �" << P->Route << endl << "��������� ��������: ";
		if (P->Status == true) cout << "�� ��������\n"<<endl;
		else cout << "� �����\n"<<endl;
		P = P->Next;
	}
}

void DeleteListItem(List* MainList, int Num) {
	if (MainList->First == NULL) throw "������ ����. ";
	MainList->Current = MainList->First;
	int i(0);
	if (MainList->Current->Next == NULL && MainList->Current->Number == Num) {
		ListItemBus* buff = MainList->Current;
		MainList->First = NULL;
		delete buff;
	}
	else {
		while (MainList->Current->Number != Num) {
			MainList->Current = MainList->Current->Next;
			i++;
		}
		if (MainList->Current == NULL) throw "������� � ������� ������� �� ���������������.";
		if (MainList->Current == MainList->First) {
			ListItemBus* buff = MainList->First;
			MainList->First = MainList->First->Next;
			delete buff;
		}
		else {
				ListItemBus* buff = MainList->Current;
				ListItemBus* buff2 = MainList->First;
				for (int j = 0; j < i-1; j++, buff2 = buff2->Next);
				buff2->Next = MainList->Current->Next;
				delete buff;
		}
	}
}

void ChangeStatus(List* MainList,int Num) {
	MainList->Current = MainList->First;
	while (MainList->Current->Number != Num) {
		MainList->Current = MainList->Current->Next;
	}
	if (MainList->Current == NULL) throw "������� � ������� ������� �� ���������������.";
	else {
		if (MainList->Current->Status == true) {
			MainList->Current->Status = false;
			cout << "������ �������� �" << Num << " ������� �� \"� �����\"\n";
		}
		else {
			MainList->Current->Status = true;
			cout << "������ �������� �" << Num << " ������� �� \"�� ��������\"\n";
		}
	}
}

void OnTheRoute(List* MainList){
	cout << "�� ��������: \n";
	MainList->Current = MainList->First;
	int p(0);
	while (MainList->Current != NULL) {
		if (MainList->Current->Status == true) {
			p++;
			cout << "������� �" << MainList->Current->Number << endl << "������� � �������� ��������: " << MainList->Current->NameInit << endl << "������� �" << MainList->Current->Route << endl << "��������� ��������: �� ��������. \n";
		}
		MainList->Current = MainList->Current->Next;
	}
	if (p == 0) throw "��������� � ������� ��������� �� ����������������.";
}

void InThePark(List* MainList) {
	cout << "� �����: \n";
	MainList->Current= MainList->First;
	int p(0);
	while (MainList->Current != NULL) {
		if (MainList->Current->Status == false) {
			p++;
			cout << "������� �" << MainList->Current->Number << endl << "������� � �������� ��������: " << MainList->Current->NameInit << endl << "������� �" << MainList->Current->Route << endl << "��������� ��������: � �����. \n";
		}
		MainList->Current = MainList->Current->Next;
	}
	if (p == 0) 
		throw "��������� � ������� ��������� �� ����������������.";
}

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int t(0);
	try {
		cout << "����� ���������� � ��������� ��� ������ � ����������!\n��� ������ ������ ������� ����������� ��������� ���������� ���������: ";
		int Numb;
		cin >> Numb;
		system("cls");
		List MainList;
		MainList.First = NULL;
		for (i = 0; i < Numb; i++) AddItem(&MainList, i);
		system("cls");
		int Choice(1);
		int aNum(0);
		while (Choice) {
			Menu(Choice);
			switch (Choice) {
			case 1:
				ShowList(&MainList);
				cout << "1. ��������� � ����\n0. ��������� ������ � ����������.\n";
				cin >> Choice;
				if (Choice == 1) {
					system("cls");
				}
				if (Choice == 2) {
					system("cls");
					return 0;
				}
				break;
			case 2:
				cout << "������� ����� ��������, ������ �������� ����� ��������\n";
				int NumberOfChange;
				cin >> NumberOfChange;
				ChangeStatus(&MainList, NumberOfChange);
				cout << "1. ��������� � ����\n0. ��������� ������ � ����������.\n";
				cin >> Choice;
				if (Choice == 1) {
					system("cls");
				}
				if (Choice == 0) {
					system("cls");
					return 0;
				}
				break;
			case 3:
				cout << "1. ..., ����������� �� ��������.\n 2. ..., ����������� � �����. \n";
				cin >> Choice;
				if (Choice == 1) {
					OnTheRoute(&MainList);
					cout << "1. ��������� � ����\n0. ��������� ������ � ����������.\n";
					cin >> Choice;
					if (Choice == 1) {
						system("cls");
					}
					if (Choice == 0) {
						system("cls");
						return 0;
					}
				}
				if (Choice == 2) {
					InThePark(&MainList);
					cout << "1. ��������� � ����\n0. ��������� ������ � ����������\n.";
					cin >> Choice;
					if (Choice == 1) {
						system("cls");
					}
					if (Choice == 0) {
						system("cls");
						return 0;
					}
				}
				break;
			case 4: 
				t = i + 1;
				AddItem(&MainList, i);
				cout << "1. ��������� � ����\n0. ��������� ������ � ����������.\n";
				cin >> Choice;
				if (Choice == 1) {
					system("cls");
				}
				if (Choice == 0) {
					system("cls");
					return 0;
				}
				break;
			case 5:
				cout << "������� ����� ���������� ��������: \n";
				cin >> aNum;
				DeleteListItem(&MainList, aNum);
				cout << "������� �" << aNum << " ������.\n";
				cout << "1. ��������� � ����\n0. ��������� ������ � ����������.\n";
				cin >> Choice;
				if (Choice == 1) {
					system("cls");
				}
				if (Choice == 0) {
					system("cls");
					return 0;
				}
				break;
			case 0:
				return 0;
				break;
			default:
				throw "������ �������������� �������. ";
				continue;
			}
		}
	}
	catch (const char* error) {
		cout << error << endl;
		return 0;
	}
	return 0;
}