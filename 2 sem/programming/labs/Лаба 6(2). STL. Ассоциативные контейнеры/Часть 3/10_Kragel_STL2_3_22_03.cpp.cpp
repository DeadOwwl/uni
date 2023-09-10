#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <functional>
#include <numeric>
#include <iterator>
#include <iomanip>
#include <windows.h>

using namespace std;

struct Author
{
	string Surname;
	string Name;
	string MiddleName;
};

struct Book
{
	int UDK;
	list <Author> Authors;
	string Tittle;
	int Year;
};

bool operator<(Author A1, Author A2)
{
	if (A1.Surname != A2.Surname)
		return(A1.Surname < A2.Surname);
	else
		if (A1.Name != A2.Name)
			return(A1.Name < A2.Name);
		else
			if (A1.MiddleName != A2.MiddleName)
				return(A1.MiddleName < A2.MiddleName);
}

bool operator>(Author A1, Author A2)
{
	if (A1.Surname != A2.Surname)
		return(A1.Surname > A2.Surname);
	else
		if (A1.Name != A2.Name)
			return(A1.Name > A2.Name);
		else
			if (A1.MiddleName != A2.MiddleName)
				return(A1.MiddleName > A2.MiddleName);
}

bool operator==(Author A1, Author A2)
{
	return(A1.Surname == A2.Surname && A1.Name == A2.Name && A1.MiddleName == A2.MiddleName);
}

bool operator<(Book B1, Book B2)
{
	return(B1.Tittle < B2.Tittle);
}

bool operator>(Book B1, Book B2)
{
	return(B1.Tittle > B2.Tittle);
}

bool operator==(Book B1, Book B2)
{
	return(B1.Tittle == B2.Tittle);
}

void fPrint(list<Author> Au)
{
	list <Author>::iterator i = Au.begin();
	cout << "������: ";
	for (i; i != Au.end(); i++)
		cout << (*i).Surname << " " << (*i).Name << " " << (*i).MiddleName << "; ";
	cout << endl;
}

void fPrint(list <Book> B)
{
	list<Book>::iterator i = B.begin();
	for (i; i != B.end(); i++)
	{
		cout << "UDK:" << (*i).UDK << endl;
		fPrint((*i).Authors);
		cout << "��������: \"" << (*i).Tittle << "\"\n";
		cout << "���:" << (*i).Year << endl << endl;
	}
}

list<Author> fAddAuthor(list<Author> la)
{
	Author a;
	int h;
	cout << "������� ���������� �������: ";
	cin >> h;
	for (int i(0); i < h; i++)
	{
		cout << "������� ������� ������: ";
		cin >> a.Surname;
		cout << "������� ��� ������: ";
		cin >> a.Name;
		cout << "������� �������� ������: ";
		cin >> a.MiddleName;
		la.push_back(a);
	}
	return la;
}

void fAddBook(list <Book>& Bb, Book bb)
{
	Book b;
	cout << "������� UDK �����: ";
	cin >> b.UDK;
	b.Authors = fAddAuthor(b.Authors);
	cout << "������� �������� �����: ";
	cin >> b.Tittle;
	cout << "������� ��� ������� �����: ";
	cin >> b.Year;
	list<Book>::iterator i = Bb.begin();
	bool flag(false);
	for (i; i != Bb.end(); i++)
		if ((*i).Tittle == b.Tittle && (*i).Year==b.Year && (*i).Authors==b.Authors)
		{
			flag = true;
			break;
		}
	if (flag==false)
	{
		Bb.push_back(bb);
		Bb.sort();
		cout << "���������� ��������� �������.\n";
	}
	else
		cout << "����� ����� ��� ������������ � ����������.\n";
}

void fPrintBook(Book lb)
{
	cout << "UDK:" << lb.UDK << endl;
	fPrint(lb.Authors);
	cout << "���������: \"" << lb.Tittle << "\"\n";
	cout << "���:" << lb.Year << endl << endl;
}

void fFindByTittle(list<Book>& B, string t)
{
	list<Book>::iterator i = B.begin();
	bool flag(false);
	for (i; i!=B.end();i++)
		if ((*i).Tittle == t)
		{
			flag = true;
			cout << "����� � ������� ���������: ";
			fPrintBook(*i);
			break;
		}
	if (flag == false)
		cout << "����� � ����� ��������� �� �������.\n";
}

void fFindByAUthor(list<Book>& B, string t)
{
	list<Book>::iterator i = B.begin();
	bool flag(false);
	for (i; i != B.end(); i++)
	{
		list<Author>::iterator j = ((*i).Authors).begin();
		for (j; j!=((*i).Authors).end(); j++)
		if (j->Surname == t && flag==false)
		{
			flag = true;
			cout << "�����(-�) �������� ������: \n";
			fPrintBook(*i);
		}
		else 
			if (j->Surname == t && flag == true)
				fPrintBook(*i);
	}
	if (flag == false)
		cout << "���� ������� ������ �� �������.\n";
}

void fFindByTittleToAddAu(list<Book>& B, string t)
{
	list<Book>::iterator i = B.begin();
	bool flag(false);
	bool aflag(false);
	for (i; i != B.end(); i++)
		if ((*i).Tittle == t)
		{
			flag = true;
			Author auB;
			cout << "������� �������, ���, �������� ������������ ������: ";
			cin >> auB.Surname >> auB.Name >> auB.MiddleName;
			list<Author>::iterator k = ((*i).Authors).begin();
			for (k; k != ((*i).Authors).end(); k++)
				if (k->Surname == auB.Surname && k->Name == auB.Name && k->MiddleName == auB.MiddleName)
				{
					aflag = true;
					cout << "����� ��� ������������ � �����. \n";
					break;
				}
			if (aflag == false)
			{
				((*i).Authors).push_back(auB);
				cout << "����� ������� ��������.\n";
			}
			break;
		}
	if (flag == false)
		cout << "����� � ����� ��������� �� �������.\n";
}

void fFindByTittleToDelAu(list<Book>& B, string t)
{
	list<Book>::iterator i = B.begin();
	bool flag(false);
	bool aflag(false);
	for (i; i != B.end(); i++)
		if ((*i).Tittle == t)
		{
			flag = true;
			Author auB;
			cout << "������� �������, ���, �������� ���������� ������: ";
			cin >> auB.Surname >> auB.Name >> auB.MiddleName;
			list<Author>::iterator k = ((*i).Authors).begin();
			for (k; k != ((*i).Authors).end(); k++)
				if (k->Surname == auB.Surname && k->Name == auB.Name && k->MiddleName == auB.MiddleName)
				{
					aflag = true;
					((*i).Authors).erase(k);
					cout << "����� ������� ������. \n";
					break;
				}
			if (aflag == false)
				cout << "������ ������ � ����� �� ����������.\n";
			break;
		}
	if (flag == false)
		cout << "����� � ����� ��������� �� �������.\n";
}

int main()
{
	try
	{
		setlocale(0, "");
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);

		list<Book> B;
		Book b;
		list<Author> A;
		Author a;

		//��������� ��� �����

		a.Surname = "������������";
		a.Name = "����";
		a.MiddleName = "�����������";
		A.push_back(a);
		a.Surname = "������";
		a.Name = "�������";
		a.MiddleName = "��������";
		A.push_back(a);
		b.UDK = 800600;
		b.Authors = A;
		b.Tittle = "���������� �������. ������� �������. ������� �������� (�������)";
		b.Year = 2009;
		B.push_back(b);
		A.clear();

		a.Surname = "������������";
		a.Name = "����";
		a.MiddleName = "�����������";
		A.push_back(a);
		a.Surname = "������";
		a.Name = "�������";
		a.MiddleName = "��������";
		A.push_back(a);
		b.UDK = 800614;
		b.Authors = A;
		b.Tittle = "����������� �������";
		b.Year = 2004;
		B.push_back(b);
		A.clear();

		a.Surname = "����������";
		a.Name = "�������";
		a.MiddleName = "���������";
		A.push_back(a);
		a.Surname = "����������";
		a.Name = "�����";
		a.MiddleName = "���������";
		A.push_back(a);
		b.UDK = 800679;
		b.Authors = A;
		b.Tittle = "�� �������� ��� �� ����� �����. ������ ��������� �������. ���� ����������. ����������� ���� ��� ����� ��� ������ (�������)";
		b.Year = 1990;
		B.push_back(b);
		A.clear();

		a.Surname = "�������";
		a.Name = "���";
		a.MiddleName = "";
		A.push_back(a);
		a.Surname = "��������";
		a.Name = "�����";
		a.MiddleName = "";
		A.push_back(a);
		b.UDK = 800699;
		b.Authors = A;
		b.Tittle = "������ ����������������";
		b.Year = 1989;
		B.push_back(b);
		A.clear();

		B.sort();
		fPrint(B);

		int Choice(1);
		while (Choice != 0)
		{
			cout << "����\n1. �������� �����\n2. ������� �����\n3. ����� ����� �� ��������\n4. ����� ���� ���������� ������\n5. �������� ������ ������������ �����\n6. ������� ������ ������������ �����\n7. ����������� ������ ����\n0. ��������� ������ � ����������\n��� �����:";
			cin >> Choice;
			switch (Choice)
			{
			case 1:
			{
				Book bb;
                fAddBook(B, bb);

				break;
			}
			case 2:
			{
				bool flag(false);
				string n;
				cout << "������� �������� ����� ��� ��������: ";
				cin.ignore(1024, '\n');
				getline(cin, n);
				list<Book>::iterator i = B.begin();
				for (i; i != B.end();)
					if ((*i).Tittle == n)
					{
						flag = true;
						i = B.erase(i);
					}
					else
						i++;
				if (flag == false)
					cout << "����� � ����� ��������� ���.\n";
				else
					cout << "����� �������.\n";
				break;
			}
			case 3:
			{
				string n;
				cin.ignore(1024, '\n');
				cout << "������� �������� ������� �����: ";
				getline(cin, n);
				fFindByTittle(B, n);
				break;
			}
			case 4:
			{
				string aut;
				cout << "������� ������� ������: ";
				cin.ignore(1024, '\n');
				getline(cin, aut);
				fFindByAUthor(B, aut);
				break;
			}
			case 5:
			{
				cout << "������� �������� �����, ������ ������� �� ������ ��������: ";
				string tittle;
				cin.ignore(1024, '\n');
				getline(cin, tittle);
				fFindByTittleToAddAu(B, tittle);
				break;
			}
			case 6:
			{
				cout << "������� �������� �����, ������ ������� �� ������ �������: ";
				string tittle;
				cin.ignore(1024, '\n');
				getline(cin, tittle);
				fFindByTittleToDelAu(B, tittle);
				break;
			}
			case 7:
			{
				fPrint(B);
				break;
			}
			case 0:
			{
				return 0;
				break;
			}
			default:
			{
				cout << "������ �������������� �������.\n";
				break;
			}
			}
		}
		return 0;
	}
	catch (const char * Error)
	{
		cout << Error << endl;
		return 0;
	}
}