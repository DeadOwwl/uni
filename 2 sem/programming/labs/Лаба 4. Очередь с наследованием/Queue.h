#ifndef __Queue_defined__
#define __Queue_defined__

#include <iostream>

using namespace std;

typedef int InfoType;


class QueueException : public exception
{
public:
	QueueException(const char* Error) : exception(Error) {};
	QueueException(const QueueException& right) : exception(right) {};
};


class Queue
{
private:
	virtual void Erase() {};
	virtual void Clone(const Queue&) {};
public:
	Queue() {};
	Queue(const Queue&);
	virtual ~Queue();
	virtual Queue& operator=(const Queue&);
	virtual void Push(InfoType a) = 0;
	virtual bool Pop() = 0;
	virtual InfoType GetFirst() const = 0;
	virtual bool IsEmpty() const = 0;

	virtual unsigned GetSize() const = 0;
	virtual InfoType& operator[] (unsigned) = 0;
	virtual const InfoType& GetByIndex(unsigned) const = 0;
	virtual void Browse(void ItemWork(InfoType)) const = 0;
	virtual void Browse(void ItemWork(InfoType&)) = 0;
};


class ListQueue : public Queue
{
private:
	struct Item
	{
		InfoType Info;
		Item* Next;
		Item(InfoType a) : Info(a), Next(NULL) {};
	};
	Item* Head, * Rear;
	unsigned Size;

	void Erase();
	void Clone(const ListQueue&);// В условии кью
public:
	ListQueue() : Head(NULL), Rear(NULL), Size(0) {};
	ListQueue(const ListQueue&);
	~ListQueue();
	//ListQueue& operator=(const ListQueue& Q);
	void Push(InfoType a);
	bool Pop();
	InfoType GetFirst() const;
	bool IsEmpty() const;
	unsigned GetSize() const;
	InfoType& operator [] (unsigned);
	const InfoType& GetByIndex(unsigned) const;
	void Browse(void ItemWork(InfoType)) const;
	void Browse(void ItemWork(InfoType&));
};


class ArrayQueue : public Queue {
private:
	int* Array;
	unsigned First, Last, Capacity;
	void Erase();
	void Clone(const ArrayQueue&); // у конах тут кью аааа почему
public:
	ArrayQueue() : First(0), Last(0), Capacity(0) {};
	ArrayQueue(InfoType cpty);
	ArrayQueue(const ArrayQueue&);
	~ArrayQueue();
	//ArrayQueue& operator=(const ArrayQueue&);
	void Push(InfoType a);
	bool Pop();
	InfoType GetFirst() const;
	bool IsEmpty() const;
	unsigned GetSize() const;
	InfoType& operator [] (unsigned);
	const InfoType& GetByIndex(unsigned) const;
	void Browse(void ItemWork(InfoType)) const;
	void Browse(void ItemWork(InfoType&));
};

#endif
