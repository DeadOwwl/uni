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

		cout << "����������� ������ ������� �� �������.\n";
		ListQueue LQ1;
		cout << "�������� ����� ������.\n";
		LQ1.Push(9);
		cout << "�������� ������� 9.\n";
		LQ1.Push(19);
		cout << "�������� ������� 19.\n";
		LQ1.Push(729);
		cout << "�������� ������� 729.\n";
		cout << "�������� �������: " << endl;
		LQ1.Browse(Func1);
		cout << "������ �������: " << LQ1.GetFirst() << endl;
		cout << "������ �������: " << LQ1.GetByIndex(1) << endl;
		ListQueue LQ2;
		cout << "�������� ����� ������.\n";
		LQ2 = LQ1;
		cout << "��������� ������������.\n";
		LQ2.Browse(Func2);
		cout << "���������� �������� ����� �������: " << endl;
		LQ2.Browse(Func1);
		if (LQ2.IsEmpty())
			cout << "������� �����.";
		else
			cout << "������� �������. �� ������: " << LQ2.GetSize() << endl;
		LQ2.Pop();
		cout << "������ ������� �������.\n";
		LQ2.Pop();
		cout << "������ ������� �������.\n";
		LQ2.Pop();
		cout << "������ ������� �������.\n";
		if (LQ2.IsEmpty())
			cout << "������� �����.";
		else
			cout << "������� �������. �� ������: " << LQ2.GetSize() << endl;
		cout << endl << "___________" << endl;

		cout << "����������� ������ ������� �� ��������.\n";
		ArrayQueue AQ1(4);
		cout << "�������� ����� ������.\n";
		for (int i(0); i < 400; i += 100)
			AQ1.Push(i);
		cout << "��������� ��������.\n";
		ArrayQueue AQ2(AQ1), AQ3;
		cout << "�������� ����������� �����������. �������� ����� ������.\n";
		AQ3 = AQ1;
		cout << "��������� ������������.\n";
		cout << "�������� �������: " << endl;
		AQ1.Browse(Func1);
		cout << "������ �������: " << AQ1.GetFirst() << endl;
		if (AQ2.IsEmpty())
			cout << "������� �����.\n";
		else
			cout << "������� �������. �� ������: " << AQ2.GetSize() << endl;
		AQ1.Pop();
		cout << "������ ������� �������.\n";
		AQ1.Pop();
		cout << "������ ������� �������.\n";
		cout << "������ �������: " << AQ1.GetFirst() << endl;
		cout << "������ �������: " << AQ1.GetByIndex(2) << endl;
		cout << "������ �� ������ ��������.\n";
		AQ2.Browse(Func1);
		if (AQ2.IsEmpty())
			cout << "������� �����.\n";
		else
			cout << "������� �������. �� ������: " << AQ2.GetSize() << endl;
		AQ2.Pop();
		cout << "������ ������� �������.\n";
		AQ2.Pop();
		cout << "������ ������� �������.\n";
		AQ2.Pop();
		cout << "������ ������� �������.\n";
		if (AQ2.IsEmpty())
			cout << "������� �����.\n";
		else
			cout << "������� �������. �� ������: " << AQ2.GetSize() << endl;
		cout << endl << "������������ ���������.\n";

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