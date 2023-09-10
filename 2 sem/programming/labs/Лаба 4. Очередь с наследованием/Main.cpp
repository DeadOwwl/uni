#include <iostream>
#include "Queue.h"

using namespace std;

void Func1(InfoType A)
{
	cout << A << endl;
}

void Func2(InfoType& A)
{
	A *= 10;
}

int main()
{
	try
	{
		setlocale(0, "");

		cout << "Деомнтрация класса очереди на списках.\n";
		ListQueue LQ1;
		cout << "Объявлен новый объект.\n";
		LQ1.Push(9);
		cout << "Добавлен элемент 9.\n";
		LQ1.Push(19);
		cout << "Добавлен элемент 19.\n";
		LQ1.Push(729);
		cout << "Добавлен элемент 729.\n";
		cout << "Элементы очереди: " << endl;
		LQ1.Browse(Func1);
		cout << "Первый элемент: " << LQ1.GetFirst() << endl;
		cout << "Второй элемент: " << LQ1.GetByIndex(1) << endl;
		ListQueue LQ2;
		cout << "Объявлен новый объект.\n";
		LQ2 = LQ1;
		cout << "Выполнено присваивание.\n";
		LQ2.Browse(Func2);
		cout << "Измененные элементы новой очереди: " << endl;
		LQ2.Browse(Func1);
		if (LQ2.IsEmpty())
			cout << "Очередь пуста.";
		else
			cout << "Очередь непуста. Ее размер: " << LQ2.GetSize() << endl;
		LQ2.Pop();
		cout << "Удален элемент очереди.\n";
		LQ2.Pop();
		cout << "Удален элемент очереди.\n";
		LQ2.Pop();
		cout << "Удален элемент очереди.\n";
		if (LQ2.IsEmpty())
			cout << "Очередь пуста.";
		else
			cout << "Очередь непуста. Ее размер: " << LQ2.GetSize() << endl;
		cout << endl << "___________" << endl;

		cout << "Деомнтрация класса очереди на массивах.\n";
		ArrayQueue AQ1(4);
		cout << "Объявлен новый объект.\n";
		for (int i(0); i < 400; i += 100)
			AQ1.Push(i);
		cout << "Объявлены элементы.\n";
		ArrayQueue AQ2(AQ1), AQ3;
		cout << "Выполнен конструктор копирования. Объявлен новый объект.\n";
		AQ3 = AQ1;
		cout << "Выполнено присваивание.\n";
		cout << "Элементы очереди: " << endl;
		AQ1.Browse(Func1);
		cout << "Первый элемент: " << AQ1.GetFirst() << endl;
		if (AQ2.IsEmpty())
			cout << "Очередь пуста.\n";
		else
			cout << "Очередь непуста. Ее размер: " << AQ2.GetSize() << endl;
		AQ1.Pop();
		cout << "Удален элемент очереди.\n";
		AQ1.Pop();
		cout << "Удален элемент очереди.\n";
		cout << "Первый элемент: " << AQ1.GetFirst() << endl;
		cout << "Второй элемент: " << AQ1.GetByIndex(2) << endl;
		cout << "Работа со второй очередью.\n";
		AQ2.Browse(Func1);
		if (AQ2.IsEmpty())
			cout << "Очередь пуста.\n";
		else
			cout << "Очередь непуста. Ее размер: " << AQ2.GetSize() << endl;
		AQ2.Pop();
		cout << "Удален элемент очереди.\n";
		AQ2.Pop();
		cout << "Удален элемент очереди.\n";
		AQ2.Pop();
		cout << "Удален элемент очереди.\n";
		if (AQ2.IsEmpty())
			cout << "Очередь пуста.\n";
		else
			cout << "Очередь непуста. Ее размер: " << AQ2.GetSize() << endl;
		cout << endl << "Демонстрация завершена.\n";

		ListQueue* L1, *L2;
		L1 = new ListQueue;
		L2 = new ListQueue;
		L1->Push(5);
		L1->Push(15);
		L1->Push(125);
		*L2 = *L1;

		ArrayQueue* A1, *A2;
		A1 = new ArrayQueue(4);
		A2 = new ArrayQueue(5);
		A1->Push(5);
		A1->Push(15);
		A1->Push(125);
		*A2 = *A1;
		return 0;
	}
	catch (QueueException & Error)
	{
		cout << Error.what() << endl;
		return 0;
	}
}