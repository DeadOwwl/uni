#include <iostream>
#include <string>
#include "List.h"

using namespace std;

// добавление нового элемента в начало списка

void List::Erase()
{
	ListItem* p, * q;
	p = First;
	while (p != NULL)
	{
		q = p->Next;
		delete p;
		p = q;
	}
	First = NULL;
}

void List::Clone(const List& L)
{
	ListItem* p, * q, * r;
	r = NULL;
	p = L.First;
	while (p != NULL)
	{
		q = new ListItem;
		q->Info = p->Info;
		q->Next = NULL;
		if (r == NULL)
			First = q;
		else
			r->Next = q;
		r = q;
		p = p->Next;
	}
}


List::List(const List& L)
{
	Clone(L);
}

const List& List::operator = (const List& L)
{
	if (&L == this)
		return *this; 
	Erase();
	Clone(L);
	return *this;
}
List::~List()
{
	Erase();
}

void List::InsertFirst(const string& author, const string& name, const string& year)
{
	ListItem* P = new ListItem;
	P->Info.Name = name;
	P->Info.Author = author;
	P->Info.Year = year;
	P->Next = First;
	First = P;
}

void List::InsertLast(const string& author, const string& name, const string& year)
{
	ListItem* P = new ListItem;
	P->Info.Name = name;
	P->Info.Author = author;
	P->Info.Year = year;
	P->Next = NULL;
	ListItem* T = new ListItem;
	T = First;
	if (T == NULL)
	{
		P = First;
	}
	while (T != NULL)
	{
		if (T->Next != NULL)
		{
			T = T->Next;
		}
		else break;
	}
	T->Next = P;
}

void List::InsertAfter(const string& author, const string& name, const string& year, const string& fname)
{
	string f = fname;
	int t = Find(f);
	ListItem* P = new ListItem;
	P->Info.Name = name;
	P->Info.Author = author;
	P->Info.Year = year;
	ListItem* T = new ListItem;
	T = First;
	int k(0);
	while (T != NULL && k != t)
	{
		if (T->Next != NULL)
		{
			T = T->Next;
		}
		else 
			break;
	}
	if (T == First)
		InsertFirst(name, author, year);
	if (T->Next == NULL)
		InsertLast(name, author, year);
	ListItem* S = new ListItem;
	S = T;
	S = S->Next;
	S = S->Next;
	P->Next = S;
	T->Next = P;
}

bool List::DeleteFirst()
{
	if (First == NULL)
		return false; 
	ListItem* P = First;
	First = First->Next;
	delete P;
	return true;
}
void List::DeleteLast()
{
	ListItem* T = new ListItem;
	T = First;
	while (T != NULL)
	{
		if (T->Next != NULL)
		{
			T = T->Next;
		}
		else break;
	}
	delete T;
}
// посмотреть первый элемент списка
const Book List::Top() const
{
	if (First == NULL)
		throw "Список пустой";
	Book x = First->Info;
	return x;
}
// клонирование

const int List::Find(string& a)
{
	int num = 0;
	ListItem* T = new ListItem;
	T = First;
	while (T != NULL)
	{
		num++;
		if (T->Info.Name != a)
		{
			T = T->Next;
		}
		else
		{
			cout << "Элемент с таким значением в списке находится на " << num << " месте." << endl;
			return num;
		}
	}
	if (T == NULL)
	{
		cout << "Такого элемента не обнаружено." << endl;
		return 0;
	}
}
const int List::FindSr(string a)
{
	int num = 0;
	int sr = 0;
	ListItem* T = new ListItem;
	T = First;
	while (T != NULL)
	{
		num++;
		if (T->Info.Name != a)
		{
			T = T->Next;
			sr++;
		}
		else
		{
			cout << "Элемент с таким значением в списке находится на " << num << " месте. Найдено через " << sr << " cравнений." << endl;
			return num;
		}
	}
	if (T == NULL)
	{
		cout << "Такого элемента не обнаружено" << endl;
		return 0;
	}
}
const bool List::FindDel(string a)
{
	ListItem* P = new ListItem;
	ListItem* T = new ListItem;
	if (P == NULL)
		throw "Список пустой";
	if (P != NULL) {
		while (P != NULL)
		{
			if (P->Info.Name == a)
			{
				if (P == First)
				{
					DeleteFirst();
					return 1;
				}
				else {
					T->Next = P->Next;
					delete P;
					cout << "Элемент удален\n";
					return 1;
				}
			}
			else
			{
				T = P;
				P = P->Next;
			}
		}
		if (P == NULL)
		{
			cout << "Такого элемента не обнаружено" << endl;
			return 0;
		}
	}
}

// удаление списка

// конструктор копирования

// печать элементов списка 1-ый способ
void List::ListPrint()const
{
	ListItem* P = First;
	if (P == NULL)
		cout << "Cписок Пуст!" << endl;
	if (P != NULL)
	{
		cout << "Содержимое Списка:" << endl;
		while (P != NULL)
		{
			cout << P->Info.Author << " \"" << P->Info.Name << "\", " << P->Info.Year << "\n";
			P = P->Next;
		}
	};
}
void List::ListPrint()
{
	ListItem* P = First;
	if (P == NULL)
		cout << "Список Пуст!" << endl;
	if (P != NULL)
	{
		cout << "Содержимое Списка:" << endl;
		while (P != NULL)
		{
			cout << P->Info.Author << " \"" << P->Info.Name << "\", " << P->Info.Year << "\n";
			P = P->Next;
		}
	};
}
// печать элементов списка 2-ой способ
void Print(Book x)
{
	cout << x.Author << " \"" << x.Name << "\", " << x.Year << "\n";
}

// выполнить действия над всеми элементами списка,  изменяя его
void List::ForEach(void (*Fun)(Book&))
{
	ListItem* p = First;
	if (p == NULL)
		throw "Cписок пуст";
	while (p != NULL) {
		Fun(p->Info);
		p = p->Next;
	}
}

 //выполнить действия над всеми элементами списка, не изменяя его
void List::ForEach(void (*Fun)(Book)) const
{
	ListItem* P = First;
	if (P == NULL)
		throw  "Cписок пуст";
	if (P != NULL)
	{
		cout << "Cодержимое списка:" << endl;
		while (P != NULL)
		{
			Fun(P->Info);
			P = P->Next;
		}
	};
}