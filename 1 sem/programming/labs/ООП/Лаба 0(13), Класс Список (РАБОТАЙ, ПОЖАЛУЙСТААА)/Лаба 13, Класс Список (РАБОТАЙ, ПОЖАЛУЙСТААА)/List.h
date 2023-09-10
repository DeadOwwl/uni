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
	// ���������� ������ �������� � ������ ������
	void InsertLast(const string& author, const string& name, const string& year);
	void InsertAfter(const string& author, const string& name, const string& year, const string& fname);
	bool DeleteFirst();
	void DeleteLast();
	// �������� �������� �� ������ ������
	const Book Top() const;
	// ���������� ������ ������� ������
	void ListPrint() const; // ������ ��������� ������
	void ListPrint(); // ������ ��������� ������
	void ForEach(void(*Fun)(Book))const;  // ��������� �������� ��� ����� ���������� ������, �� ������� ���
	void ForEach(void(*Fun)(Book&));      // ��������� �������� ��� ����� ���������� ������, ������� ���
	// ��������� �������� ��� ����� ���������� ������, �� ������� ���
	const int Find(string&);
	const int FindSr(string);
	const bool FindDel(string);
	// ��������� �������� ��� ����� ���������� ������, ������� ���
	List() { First = NULL; } // �����������
	List(const List&); // ����������� �����������
	const List& operator = (const List&); // �������� ������������
	virtual~List(); // ����������
	void Erase(); // �������� ��������� ������ ������
protected:
	void Clone(const List&); // ������������
};
