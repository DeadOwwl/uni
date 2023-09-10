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
	cout << "Главное Меню:\n1. Просмотреть список всех автобусов. \n2. Измененить статус автобуса. \n3. Получить сведения об автобусах... \n4. Добавить новый автобус.\n5. Удалить автобус.\n0.Завершить работу с программой.\n";
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
	cout << "Заполнение " << *i+1 << "-ого автобуса\n";
	cout << "Номер автобуса: №";
	cin >> ListItem->Number;
	cout << "Фамилия и инициалы водителя: ";
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
	if (k != 2) throw "Количество слов в поле \"Фамилия и инициалы водителя\" не соответствует необходимому.";
	cout << "Номер маршрута: №";
	cin >> ListItem->Route;
	string StatusStr;
	cout << "Состояние автобуса\n\t *Допустимы такие варианты, как \"На маршруте\" и \"В парке\": ";
	cin.ignore(1024, '\n');
	getline(cin, StatusStr);
	/*StatusStr.pop_back();
	StatusStr += ' ';*/
	if (StatusStr == "На маршруте") ListItem->Status = true;
	if (StatusStr == "В парке") ListItem->Status = false;
	if (StatusStr != "На маршруте" && StatusStr != "В парке") throw "Неверное значение поля \"Состояние автобуса\"\n ";
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
	if (P == NULL) cout << "Список пуст\n";
	while (P) {
		cout << "Автобус №" << P->Number << endl << "Фамилия и инициалы водителя: " << P->NameInit << endl << "Маршрут №" << P->Route << endl << "Состояние автобуса: ";
		if (P->Status == true) cout << "На маршруте\n"<<endl;
		else cout << "В парке\n"<<endl;
		P = P->Next;
	}
}

void DeleteListItem(List* MainList, int Num) {
	if (MainList->First == NULL) throw "Список пуст. ";
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
		if (MainList->Current == NULL) throw "Автобус с искомым номером не зарегистрирован.";
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
	if (MainList->Current == NULL) throw "Автобус с искомым номером не зарегистрирован.";
	else {
		if (MainList->Current->Status == true) {
			MainList->Current->Status = false;
			cout << "Статус автобуса №" << Num << " изменен на \"В парке\"\n";
		}
		else {
			MainList->Current->Status = true;
			cout << "Статус автобуса №" << Num << " изменен на \"На маршруте\"\n";
		}
	}
}

void OnTheRoute(List* MainList){
	cout << "На маршруте: \n";
	MainList->Current = MainList->First;
	int p(0);
	while (MainList->Current != NULL) {
		if (MainList->Current->Status == true) {
			p++;
			cout << "Автобус №" << MainList->Current->Number << endl << "Фамилия и инициалы водителя: " << MainList->Current->NameInit << endl << "Маршрут №" << MainList->Current->Route << endl << "Состояние автобуса: На маршруте. \n";
		}
		MainList->Current = MainList->Current->Next;
	}
	if (p == 0) throw "Автобусов в искомом состоянии не зарегистрировано.";
}

void InThePark(List* MainList) {
	cout << "В парке: \n";
	MainList->Current= MainList->First;
	int p(0);
	while (MainList->Current != NULL) {
		if (MainList->Current->Status == false) {
			p++;
			cout << "Автобус №" << MainList->Current->Number << endl << "Фамилия и инициалы водителя: " << MainList->Current->NameInit << endl << "Маршрут №" << MainList->Current->Route << endl << "Состояние автобуса: В парке. \n";
		}
		MainList->Current = MainList->Current->Next;
	}
	if (p == 0) 
		throw "Автобусов в искомом состоянии не зарегистрировано.";
}

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int t(0);
	try {
		cout << "Добро пожаловать в программу для работы с автобусами!\nДля начала работы введите необходимое начальное количество автобусов: ";
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
				cout << "1. Вернуться в меню\n0. Завершить работу с программой.\n";
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
				cout << "Введите номер автобуса, статус которого нужно изменить\n";
				int NumberOfChange;
				cin >> NumberOfChange;
				ChangeStatus(&MainList, NumberOfChange);
				cout << "1. Вернуться в меню\n0. Завершить работу с программой.\n";
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
				cout << "1. ..., находящихся на маршруте.\n 2. ..., находящихся в парке. \n";
				cin >> Choice;
				if (Choice == 1) {
					OnTheRoute(&MainList);
					cout << "1. Вернуться в меню\n0. Завершить работу с программой.\n";
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
					cout << "1. Вернуться в меню\n0. Завершить работу с программой\n.";
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
				cout << "1. Вернуться в меню\n0. Завершить работу с программой.\n";
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
				cout << "Введите номер удаляемого автобуса: \n";
				cin >> aNum;
				DeleteListItem(&MainList, aNum);
				cout << "Автобус №" << aNum << " удален.\n";
				cout << "1. Вернуться в меню\n0. Завершить работу с программой.\n";
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
				throw "Выбран непредложенный вариант. ";
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