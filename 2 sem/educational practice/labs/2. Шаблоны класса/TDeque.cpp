#include "TDeque.h"

template <typename TInfo>
void TDeque <TInfo>::Erase()
{
	while (DeleteRear());
	Size = 0;
}

template <typename TInfo>
void TDeque <TInfo>::Clone(const TDeque& TD)
{
	TDequeItem T = TD.Front;
	for (unsigned i(0); i < TD.Size; i++, T = T->Next)
		InsertRear(T);
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
		throw "Дек пуст.";
	else
		if (n < 0 || n > Size)
			throw"Неверный индекс.";
		else
			for (unsigned i(0); i < n; i++, T = T->Next);
	return T;
}

template <typename TInfo>
TDeque<TInfo>::TDeque(const TDeque& T): Front(NULL), Rear(NULL), Size(0)
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
	TDequeItem* T = Front;
	Rear = Rear->Next;
	Rear->Next = NULL;
	delete T;
	Size--;
	if (Rear)
		Rear->Next = NULL;
	if (Size == 0)
		Rear = Front = NULL;
	return true;
}

template <typename TInfo>
const TDeque<TInfo>& TDeque<TInfo>::operator=(const TDeque& TD)
{
	if (this != &TD)
	{
		Erase(TD);
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
	TDequeItem* T = (TDequeItem*)PtrByIndex(n);
	T->Info = i;
}

template <>
void TDeque<char*>::SetByIndex(char* i, unsigned n)
{
	TDequeItem* T = (TDequeItem*)PtrByIndex(n);
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