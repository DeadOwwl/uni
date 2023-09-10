#include "Queue.h"

// Queue

Queue::Queue(const Queue& Q)
{
	Clone(Q);
}

Queue::~Queue()
{
	Erase();
}

Queue& Queue::operator=(const Queue& Q)
{
	if (this == &Q)
		return *this;
	Erase();
	Clone(Q);
	return *this;
}

// ListQueue

void ListQueue::Erase()
{
	while (Size != 0)
		Pop();
}

void ListQueue::Clone(const ListQueue& Q)
{
	Item* tmp = Q.Head;
	for (unsigned i(0); i < Q.Size; i++)
	{
		Push(tmp->Info);
		tmp = tmp->Next;
	}
}

ListQueue::ListQueue(const ListQueue& Q)
{
	Size = 0;
	Clone(Q);
}

ListQueue::~ListQueue()
{
	Erase();
	cout << "Вызван деструктор для ListQueue.\n";
}

//ListQueue& ListQueue:: operator=(const ListQueue& Q)
//{
//	if (this == &Q)
//		return *this;
//	Erase();
//	Clone(Q);
//	return *this;
//}

void ListQueue::Push(InfoType I)
{
	Item* tmp = new Item(I);
	if (Size > 0)
		Rear->Next = tmp;
	else
		Head = tmp;
	Rear = tmp;
	Size++;
}

bool ListQueue::Pop()
{
	if (Size == 0)
		throw QueueException("Невозможно выполнить удаление - очередь пуста");
	Item* tmp = Head;
	Head = Head->Next;
	delete tmp;
	Size--;
	if (Size == 0)
		Rear = NULL;
	return true;
}

InfoType ListQueue::GetFirst() const
{
	if (Size == 0)
		throw QueueException("Невозможно получить первый элемент - очередь пуста.");
	return Head->Info;
}

bool ListQueue::IsEmpty() const
{
	return (Size == 0);
}

unsigned ListQueue::GetSize() const
{
	return Size;
}

InfoType& ListQueue::operator[](unsigned k)
{
	return (InfoType&)GetByIndex(k);
}

const InfoType& ListQueue::GetByIndex(unsigned k) const
{
	if ((k < 0) || (k >= Size))
		throw QueueException("Невозможно использовать оператор [] - недопустимый индекс.");
	Item* tmp = Head;
	for (unsigned i(0); i < k; i++)
		tmp = tmp->Next;
	return tmp->Info;
}

void ListQueue::Browse(void ItemWork(InfoType)) const
{
	Item* tmp = Head;
	for (unsigned i(0); i < Size; i++)
	{
		ItemWork(tmp->Info);
		tmp = tmp->Next;
	}
}

void ListQueue::Browse(void ItemWork(InfoType&))
{
	Item* tmp = Head;
	for (unsigned i(0); i < Size; i++)
	{
		ItemWork(tmp->Info);
		tmp = tmp->Next;
	}
}

// ArrayQueue

void ArrayQueue::Erase()
{
	delete[] Array;
	First = 0;
	Last = 0;
	Capacity = 0;
}

void ArrayQueue::Clone(const ArrayQueue& Q) // опять же у конах тут кью
{
	Capacity = Q.Capacity;
	First = Q.GetFirst();
	Last = Q.Last;
	Array = new InfoType[Capacity + 1];
	for (unsigned i(0); i < Capacity; i++)
		Array[i] = Q.Array[i];
}

ArrayQueue::ArrayQueue(InfoType cpty)
{
	Capacity = cpty;
	Array = new InfoType[Capacity + 1];
	First = 0;
	Last = 0;
}

ArrayQueue::ArrayQueue(const ArrayQueue& Q)
{
	Erase();
	Clone(Q);
}

ArrayQueue::~ArrayQueue()
{
	cout << "Вызван деструктор для ArrayQueue.\n";
	Erase();
}

//ArrayQueue& ArrayQueue:: operator=(const ArrayQueue& Q)
//{
//	if (this == &Q)
//		return *this;
//	Erase();
//	Clone(Q);
//	return *this;
//}

void ArrayQueue::Push(InfoType a)
{
	if ((Last + 1 == First) || ((First == 0) && (Last == Capacity)))
		throw QueueException("Невозможно выполнить вставку нового элемента - очередь переполнена");
	Array[Last++] = a;
	if (Last == Capacity + 1)
		Last = 0;
}

bool ArrayQueue::Pop()
{
	if ((Capacity == 0) || (First == Last))
		throw QueueException("Невозможно выполнить удаление элемента - очередь пуста.");
	First++;
	if (First == Capacity + 1)
		First = 0;
	return true;
}

InfoType ArrayQueue::GetFirst() const
{
	return Array[First];
}

bool ArrayQueue::IsEmpty() const
{
	return (Capacity == 0 || First == Last);
}

unsigned ArrayQueue::GetSize() const
{
	return (Last - First);
}

InfoType& ArrayQueue:: operator [] (unsigned k)
{
	return (InfoType&)GetByIndex(k);
}

const InfoType& ArrayQueue::GetByIndex(unsigned k) const
{
	if (k < 0 && k >= Last - First)
		throw QueueException("Невозможно использовать оператор [] - неверный индекс.");
	return Array[First + k - 1];
}

void ArrayQueue::Browse(void ItemWork(InfoType)) const
{
	for (unsigned i(First); i < Last; i++)
		ItemWork(Array[i]);
}

void ArrayQueue::Browse(void ItemWork(InfoType&))
{
	for (unsigned i(First); i < Last; i++)
		ItemWork(Array[i]);
}