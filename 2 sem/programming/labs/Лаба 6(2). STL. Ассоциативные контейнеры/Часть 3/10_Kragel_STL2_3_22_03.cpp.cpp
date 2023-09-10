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
	cout << "Авторы: ";
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
		cout << "Название: \"" << (*i).Tittle << "\"\n";
		cout << "Год:" << (*i).Year << endl << endl;
	}
}

list<Author> fAddAuthor(list<Author> la)
{
	Author a;
	int h;
	cout << "Введите количество авторов: ";
	cin >> h;
	for (int i(0); i < h; i++)
	{
		cout << "Введите фамилию автора: ";
		cin >> a.Surname;
		cout << "Введите имя автора: ";
		cin >> a.Name;
		cout << "Введите отчество автора: ";
		cin >> a.MiddleName;
		la.push_back(a);
	}
	return la;
}

void fAddBook(list <Book>& Bb, Book bb)
{
	Book b;
	cout << "Введите UDK книги: ";
	cin >> b.UDK;
	b.Authors = fAddAuthor(b.Authors);
	cout << "Введите название книги: ";
	cin >> b.Tittle;
	cout << "Введите год издания книги: ";
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
		cout << "Добавление выполнено успешно.\n";
	}
	else
		cout << "Такая книга уже присутствует в библиотеке.\n";
}

void fPrintBook(Book lb)
{
	cout << "UDK:" << lb.UDK << endl;
	fPrint(lb.Authors);
	cout << "Названине: \"" << lb.Tittle << "\"\n";
	cout << "Год:" << lb.Year << endl << endl;
}

void fFindByTittle(list<Book>& B, string t)
{
	list<Book>::iterator i = B.begin();
	bool flag(false);
	for (i; i!=B.end();i++)
		if ((*i).Tittle == t)
		{
			flag = true;
			cout << "Книга с искомым названием: ";
			fPrintBook(*i);
			break;
		}
	if (flag == false)
		cout << "Книги с таким названием не найдено.\n";
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
			cout << "Книга(-и) искомого автора: \n";
			fPrintBook(*i);
		}
		else 
			if (j->Surname == t && flag == true)
				fPrintBook(*i);
	}
	if (flag == false)
		cout << "Книг данного автора не найдено.\n";
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
			cout << "Введите фамилию, имя, отчество добавляемого автора: ";
			cin >> auB.Surname >> auB.Name >> auB.MiddleName;
			list<Author>::iterator k = ((*i).Authors).begin();
			for (k; k != ((*i).Authors).end(); k++)
				if (k->Surname == auB.Surname && k->Name == auB.Name && k->MiddleName == auB.MiddleName)
				{
					aflag = true;
					cout << "Автор уже присутствует в книге. \n";
					break;
				}
			if (aflag == false)
			{
				((*i).Authors).push_back(auB);
				cout << "Автор успешно добавлен.\n";
			}
			break;
		}
	if (flag == false)
		cout << "Книги с таким названием не найдено.\n";
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
			cout << "Введите фамилию, имя, отчество удаляемого автора: ";
			cin >> auB.Surname >> auB.Name >> auB.MiddleName;
			list<Author>::iterator k = ((*i).Authors).begin();
			for (k; k != ((*i).Authors).end(); k++)
				if (k->Surname == auB.Surname && k->Name == auB.Name && k->MiddleName == auB.MiddleName)
				{
					aflag = true;
					((*i).Authors).erase(k);
					cout << "Автор успешно удален. \n";
					break;
				}
			if (aflag == false)
				cout << "Такого автора в книге не обнаружено.\n";
			break;
		}
	if (flag == false)
		cout << "Книги с таким названием не найдено.\n";
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

		//Заполняем это адище

		a.Surname = "Файнзильберг";
		a.Name = "Илья";
		a.MiddleName = "Арнольдович";
		A.push_back(a);
		a.Surname = "Катаев";
		a.Name = "Евгений";
		a.MiddleName = "Петрович";
		A.push_back(a);
		b.UDK = 800600;
		b.Authors = A;
		b.Tittle = "Двенадцать стульев. Золотой теленок. Светлая личность (сборник)";
		b.Year = 2009;
		B.push_back(b);
		A.clear();

		a.Surname = "Файнзильберг";
		a.Name = "Илья";
		a.MiddleName = "Арнольдович";
		A.push_back(a);
		a.Surname = "Катаев";
		a.Name = "Евгений";
		a.MiddleName = "Петрович";
		A.push_back(a);
		b.UDK = 800614;
		b.Authors = A;
		b.Tittle = "Одноэтажная Америка";
		b.Year = 2004;
		B.push_back(b);
		A.clear();

		a.Surname = "Стругацкий";
		a.Name = "Аркадий";
		a.MiddleName = "Наканович";
		A.push_back(a);
		a.Surname = "Стругацкий";
		a.Name = "Борис";
		a.MiddleName = "Натанович";
		A.push_back(a);
		b.UDK = 800679;
		b.Authors = A;
		b.Tittle = "За миллиард лет до конца света. Второе нашествие марсиан. Град обреченный. Отягощенные злом или сорок лет спустя (сборник)";
		b.Year = 1990;
		B.push_back(b);
		A.clear();

		a.Surname = "Гейнман";
		a.Name = "Нил";
		a.MiddleName = "";
		A.push_back(a);
		a.Surname = "Пратчетт";
		a.Name = "Терри";
		a.MiddleName = "";
		A.push_back(a);
		b.UDK = 800699;
		b.Authors = A;
		b.Tittle = "Добрые предзнаменования";
		b.Year = 1989;
		B.push_back(b);
		A.clear();

		B.sort();
		fPrint(B);

		int Choice(1);
		while (Choice != 0)
		{
			cout << "Меню\n1. Добавить книгу\n2. Удалить книгу\n3. Поиск книги по названию\n4. Поиск книг указанного автора\n5. Добавить автора определенной книги\n6. Удалить автора определенной книги\n7. Распечатать список книг\n0. Завершить работу с программой\nВаш выбор:";
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
				cout << "Введите название книги для удаления: ";
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
					cout << "Книги с таким названием нет.\n";
				else
					cout << "Книга удалена.\n";
				break;
			}
			case 3:
			{
				string n;
				cin.ignore(1024, '\n');
				cout << "Введите название искомой книги: ";
				getline(cin, n);
				fFindByTittle(B, n);
				break;
			}
			case 4:
			{
				string aut;
				cout << "Введите фамилию автора: ";
				cin.ignore(1024, '\n');
				getline(cin, aut);
				fFindByAUthor(B, aut);
				break;
			}
			case 5:
			{
				cout << "Введите название книги, автора который вы хотите добавить: ";
				string tittle;
				cin.ignore(1024, '\n');
				getline(cin, tittle);
				fFindByTittleToAddAu(B, tittle);
				break;
			}
			case 6:
			{
				cout << "Введите название книги, автора который вы хотите удалить: ";
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
				cout << "Выбран непредложенный вариант.\n";
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