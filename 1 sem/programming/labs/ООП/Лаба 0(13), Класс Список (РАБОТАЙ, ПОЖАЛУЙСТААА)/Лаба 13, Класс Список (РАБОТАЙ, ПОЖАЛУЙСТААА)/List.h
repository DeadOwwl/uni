#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>
#include <iomanip> 

using namespace std;

struct Book
{
	string Author;
	string Name;
	string Year;
};

class List {
protected:
	struct ListItem {
		Book Info;
		ListItem* Next;
	};
	ListItem* First;
public:
	void InsertFirst(const string& author, const string& name, const string& year);
	// добавление нового элемента в начало списка
	void InsertLast(const string& author, const string& name, const string& year);
	void InsertAfter(const string& author, const string& name, const string& year, const string& fname);
	bool DeleteFirst();
	void DeleteLast();
	// удаление элемента из начала списка
	const Book Top() const;
	// посмотреть первый элемент списка
	void ListPrint() const; // печать элементов списка
	void ListPrint(); // печать элементов списка
	void ForEach(void(*Fun)(Book))const;  // выполнить действия над всеми элементами списка, не изменяя его
	void ForEach(void(*Fun)(Book&));      // выполнить действия над всеми элементами списка, изменяя его
	// выполнить действия над всеми элементами списка, не изменяя его
	const int Find(string&);
	const int FindSr(string);
	const bool FindDel(string);
	// выполнить действия над всеми элементами списка, изменяя его
	List() { First = NULL; } // конструктор
	List(const List&); // конструктор копирования
	const List& operator = (const List&); // оператор присваивания
	virtual~List(); // деструктор
	void Erase(); // удаление элементов списка списка
protected:
	void Clone(const List&); // клонирование
};
