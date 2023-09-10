#include "Persons.h"
#include <fstream>
#pragma warning(disable: 4996)


int Person::next_ID = 200000;

Person::Person(const char* name) : ID(++next_ID)
{
	cout << "*����������� ����������� Person*\n";
	Name = new char[strlen(name) + 1];
	strcpy(Name, name);
}

Person::~Person()
{
	cout << "*���������� Person*\n";
	delete[] Name;
}

void Person::SetName(const char* n)
{
	delete[] Name;
	Name = new char[strlen(n) + 1];
	strcpy(Name, n);
}

char* Person::GetName(char* name) const
{
	strcpy(name, Name);
	return name;
}

void Person::Print() const
{
	cout << "|���: " << Name << endl;
}

Student::Student(const char* name, const int cr, const int gr) : Person(name)//:++next_ID();
{
	cout << "*����������� Student*\n";
	Course = cr;
	Group = gr;
}

void Student::Print()const
{
	Person::Print();
	cout << "|����: " << Course << endl << "|������: " << Group << endl;
	cout << "____\n";
}

Professor::Professor(const char* name,const char* caf) : Person(name) //:++next_ID();
{
	cout << "*����������� Professor*\n";
	Caf = new char[strlen(caf) + 1];
	strcpy(Caf, caf);
}

Professor::~Professor()
{
	cout << "*���������� Professor*\n";
	delete[] Caf;
}

void Professor::SetCaf(const char* c)
{
	delete[] Caf;
	Caf = new char[strlen(c) + 1];
	strcpy(Caf, c);
}

char* Professor::GetCaf(char* c) const
{
	strcpy(c, Caf);
	return c;
}

void Professor::Print() const
{
	Person::Print();
	cout << "|�������: " << Caf << endl;
	cout << "_____\n";
}