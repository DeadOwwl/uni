#ifndef __TDeque_defined__
#define __TDeque_defined__

#include <iostream>
#include <cstring>
#pragma warning (disable:4996)

using namespace std;

class DQException : public exception
{
public:
    DQException(const char* Error) : exception(Error) {};
    DQException(const DQException& right) : exception(right) {};
};

template <typename TInfo>
class TDeque 
{
protected:
    struct TDequeItem 
    {
        TInfo Info; 
        TDequeItem* Next; 
        TDequeItem* Prev; 
    };
    TDequeItem* Front, * Rear;
    unsigned Size; 
    void Erase(); 
    void Clone(const TDeque&);
    void DeleteItem(TDequeItem*); 
    void* PtrByIndex(unsigned)const;
public:
    TDeque() : Front(NULL), Rear(NULL), Size(0) {};
    TDeque(const TDeque&); 
    virtual ~TDeque(); 
    void InsertFront(TInfo); 
    void InsertRear(TInfo); 
    bool DeleteFront(); 
    bool DeleteRear(); 
    const TDeque& operator = (const TDeque&);
    const TInfo& GetByIndex(unsigned)const; 
    void SetByIndex(TInfo, unsigned); 
    void Browse(void(TInfo&)); 
    void Browse(void(TInfo)) const; 
};

template <typename TInfo>
void TDeque <TInfo>::Erase()
{
	while (DeleteRear());
	Size = 0;
}

template <typename TInfo>
void TDeque <TInfo>::Clone(const TDeque& TD)
{
	TDequeItem* T = (TDequeItem *) TD.Front;
	for (unsigned i(0); i < TD.Size; i++, T = T->Next)
		InsertRear(T->Info);
	Size = TD.Size;
}

template <typename TInfo>
void TDeque <TInfo>::DeleteItem(TDequeItem* TD)
{
	if (Size != 0)
	{
		(TD->Prev)->Next = TD->Next;
		(TD->Next)->Prev = TD->Prev;
		delete TD;
		Size--;
	}
}

template <>
void TDeque <char*>::DeleteItem(TDequeItem* TD)
{
	if (Size != 0)
	{
		(TD->Prev)->Next = TD->Next;
		(TD->Next)->Prev = TD->Prev;
		delete[] TD;
		delete TD;
		Size--;
	}
}

template <typename TInfo>
void* TDeque <TInfo>::PtrByIndex(unsigned n)const
{
	TDequeItem* T = Front;
	if (Size == 0)
		throw DQException("Дек пуст.");
	else
		if (n < 0 || n > Size)
			throw DQException("Неверный индекс.");
		else
			for (unsigned i(0); i < n; i++, T = T->Next);
	return T;
}

template <typename TInfo>
TDeque<TInfo>::TDeque(const TDeque& T) : Front(NULL), Rear(NULL), Size(0)
{
	Clone(T);
}

template <typename TInfo>
TDeque<TInfo>:: ~TDeque()
{
	Erase();
}

template <typename TInfo>
void TDeque<TInfo>::InsertFront(TInfo i)
{
	TDequeItem* T = new TDequeItem;
	T->Info = i;
	if (Size == 0)
		Front = Rear = T;
	else
	{
		Front->Prev = T;
		T->Next = Front;
		Front = T;
	}
	Size++;
}

template <>
void TDeque<char*>::InsertFront(char* i)
{
	TDequeItem* T = new TDequeItem;
	T->Info = new char[strlen(i) + 1];
	strcpy(T->Info, i);
	if (Size == 0)
		Front = Rear = T;
	else
	{
		Front->Prev = T;
		T->Next = Front;
		Front = T;
	}
	Size++;
}

template <typename TInfo>
void TDeque<TInfo>::InsertRear(TInfo i)
{
	TDequeItem* T = new TDequeItem;
	T->Info = i;
	if (Size == 0)
		Front = Rear = T;
	else
	{
		Rear->Next = T;
		T->Prev = Rear;
		Rear = T;
	}
	Size++;
}

template <>
void TDeque<char*>::InsertRear(char* i)
{
	TDequeItem* T = new TDequeItem;
	T->Info = new char[strlen(i) + 1];
	strcpy(T->Info, i);
	if (Size == 0)
		Front = Rear = T;
	else
	{
		Rear->Next = T;
		T->Prev = Rear;
		Rear = T;
	}
	Size++;
}

template <typename TInfo>
bool TDeque<TInfo>::DeleteFront()
{
	if (Size == 0)
		return false;
	else
	{
		TDequeItem* T = Front;
		Front = Front->Next;
		Front->Prev = NULL;
		delete T;
		Size--;
		return true;
	}
}

template <typename TInfo>
bool TDeque<TInfo>::DeleteRear()
{
	if (Size == 0)
		return false;
	TDequeItem* T = Rear;
	if (Size == 1)
		Rear = Front = NULL;
	else
	{
		Rear = Rear->Prev;
		Rear->Next = NULL;
	}
	delete T;
	Size--;
	return true;
}

template <typename TInfo>
const TDeque<TInfo>& TDeque<TInfo>::operator=(const TDeque& TD)
{
	if (this != &TD)
	{
		Erase();
		Clone(TD);
	}
	return *this;
}

template <typename TInfo>
const TInfo& TDeque<TInfo>::GetByIndex(unsigned n)const
{
	TDequeItem* T = (TDequeItem*)PtrByIndex(n);
	return T->Info;
}

template <typename TInfo>
void TDeque<TInfo>::SetByIndex(TInfo i, unsigned n)
{
	((TDequeItem*)PtrByIndex(n))->Info = i;
}

template <>
void TDeque<char*>::SetByIndex(char* i, unsigned n)
{
	TDequeItem* T = (TDequeItem*)PtrByIndex(n);
	delete[] (char*)T->Info;
	T->Info = new char[strlen(i) + 1];
	strcpy(T->Info, i);
}

template <typename TInfo>
void TDeque<TInfo>::Browse(void Func(TInfo&))
{
	if (Size == 0)
		throw "Дек пуст.";
	TDequeItem* T = Front;
	for (unsigned i(0); i < Size; i++, T = T->Next)
		Func(T->Info);
}

template <typename TInfo>
void TDeque<TInfo>::Browse(void Func(TInfo)) const
{
	if (Size == 0)
		throw "Дек пуст.";
	TDequeItem* T = Front;
	for (unsigned i(0); i < Size; i++, T = T->Next)
		Func(T->Info);
}
#endif