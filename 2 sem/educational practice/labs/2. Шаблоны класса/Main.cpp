#include "TDeque.h"

template <typename TInfo>
void Ch(TInfo& t)
{
	t *= 10;
	cout << t << " ";
}

template <>
void Ch(char*& t)
{
	char* C = new char[strlen(t) + 2];
	strcpy(C, t);
	strcat(C, "*");
	delete[] t;
	t = new char[strlen(C) + 1];
	strcpy(t, C);
	cout << t << " ";
	delete[] C;
}

template <typename TInfo>
void Print(typename TInfo t)
{
	cout << t << " ";
}

int main()
{
	try
	{
		setlocale(0, "");
		TDeque<int> D;
		cout << "Демонстрация очереди для целочисленного типа.\nВставка в начало 9.\n";
		D.InsertFront(9);
		cout << "Вставка в начало 19.\n";
		D.InsertFront(19);
		cout << "Вставка в начало 99.\n";
		D.InsertFront(99);
		cout << "Вставка в конец 90.\n";
		D.InsertRear(90);
		cout << "Вставка в конец 109.\n";
		D.InsertRear(109);
		cout << "Вставка в конец 729.\n";
		D.InsertRear(729);
		cout << "Очередь: ";
		D.Browse(Print);
		cout << "\nУдаление из начала.\n";
		D.DeleteFront();
		cout << "Очередь: ";
		D.Browse(Print);
		cout << "\nУдаление из конца.\n";
		D.DeleteRear();
		cout << "Очередь: ";
		D.Browse(Print);
		unsigned n(0);
		int i(0);
		cout << "\nВведите индекс получаемого элемента: ";
		cin >> n;
		cout << "Элемент по индексу "<< n <<": "<< D.GetByIndex(n) << endl;
		cout << "Введите значение вставляемого элемента и индекс элемента, значение которого нужно изменить на заданное: ";
		cin >> i >> n;
		D.SetByIndex(i, n);
		cout << "Очередь: ";
		D.Browse(Print);
		cout << "\nОчередь после использования функции: ";
		D.Browse(Ch);
		cout << "\nИспользование конструктора копирования. Вывод содержимого объекта, присваивающего значения объявленного раннее.\n";
		TDeque<int>Ti;
		Ti = D;
		D.Browse(Print);
		cout << endl;

		TDeque<char*> Dc;
		char* S = new char;
		strcpy(S, " ");
		cout << "\n\nДемонстрация очереди для символов.\n";
		cout << "Введите строку: ";
		cin.ignore(1024, '\n');
		cin.getline(S, '\n');
		cout << "Вставка в начало\"" << S << "\"\n";
		Dc.InsertFront(S);
		cout << "Введите строку: ";
		cin.getline(S, '\n');
		cout << "Вставка в начало\"" << S << "\"\n";
		Dc.InsertFront(S);
		cout << "Введите строку: ";
		cin.getline(S, '\n');
		cout << "Вставка в начало\"" << S << "\"\n";
		Dc.InsertFront(S);
		cout << "Введите строку: ";
		cin.getline(S, '\n');
		cout << "Вставка в конец\"" << S << "\"\n";
		Dc.InsertRear(S);
		cout << "Введите строку: ";
		cin.getline(S, '\n');
		cout << "Вставка в конец\"" << S << "\"\n";
		Dc.InsertRear(S);
		cout << "Введите строку: ";
		cin.getline(S, '\n');
		cout << "Вставка в конец\"" << S << "\"\n";
		Dc.InsertRear(S);
		cout << "Очередь: ";
		Dc.Browse(Print);
		cout << "\nУдаление из начала.\n";
		Dc.DeleteFront();
		cout << "Очередь: ";
		Dc.Browse(Print);
		cout << "\nУдаление из конца.\n";
		Dc.DeleteRear();
		cout << "Очередь: ";
		Dc.Browse(Print);
		cout << "\nВведите индекс получаемого элемента: ";
		cin >> n;
		cout << "Элемент по индексу " << n << ": " << Dc.GetByIndex(n);
		cout << "\nВведите значение вставляемого элемента и индекс элемента, значение которого нужно изменить на заданное: ";
		cin.ignore(1024, '\n');
		cin.getline(S, '\n');
		cin >> n;
		Dc.SetByIndex(S, n);
		cout << "Очередь: ";
		Dc.Browse(Print);
		cout << "\nОчередь после использования функции: ";
		Dc.Browse(Ch);
		cout << endl;
		cout << "Использование конструктора копирования. Вывод содержимого объекта, присваивающего значения объявленного раннее.\n";
		TDeque<char*>Tс;
		Tс = Dc;
		Tс.Browse(Print);
		cout << endl;
		return 0;
	}
	catch (DQException E)
	{
		cout << E.what() << endl;
		return 0;
	}
}