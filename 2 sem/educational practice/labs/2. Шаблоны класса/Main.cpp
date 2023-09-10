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
		cout << "������������ ������� ��� �������������� ����.\n������� � ������ 9.\n";
		D.InsertFront(9);
		cout << "������� � ������ 19.\n";
		D.InsertFront(19);
		cout << "������� � ������ 99.\n";
		D.InsertFront(99);
		cout << "������� � ����� 90.\n";
		D.InsertRear(90);
		cout << "������� � ����� 109.\n";
		D.InsertRear(109);
		cout << "������� � ����� 729.\n";
		D.InsertRear(729);
		cout << "�������: ";
		D.Browse(Print);
		cout << "\n�������� �� ������.\n";
		D.DeleteFront();
		cout << "�������: ";
		D.Browse(Print);
		cout << "\n�������� �� �����.\n";
		D.DeleteRear();
		cout << "�������: ";
		D.Browse(Print);
		unsigned n(0);
		int i(0);
		cout << "\n������� ������ ����������� ��������: ";
		cin >> n;
		cout << "������� �� ������� "<< n <<": "<< D.GetByIndex(n) << endl;
		cout << "������� �������� ������������ �������� � ������ ��������, �������� �������� ����� �������� �� ��������: ";
		cin >> i >> n;
		D.SetByIndex(i, n);
		cout << "�������: ";
		D.Browse(Print);
		cout << "\n������� ����� ������������� �������: ";
		D.Browse(Ch);
		cout << "\n������������� ������������ �����������. ����� ����������� �������, �������������� �������� ������������ ������.\n";
		TDeque<int>Ti;
		Ti = D;
		D.Browse(Print);
		cout << endl;

		TDeque<char*> Dc;
		char* S = new char;
		strcpy(S, " ");
		cout << "\n\n������������ ������� ��� ��������.\n";
		cout << "������� ������: ";
		cin.ignore(1024, '\n');
		cin.getline(S, '\n');
		cout << "������� � ������\"" << S << "\"\n";
		Dc.InsertFront(S);
		cout << "������� ������: ";
		cin.getline(S, '\n');
		cout << "������� � ������\"" << S << "\"\n";
		Dc.InsertFront(S);
		cout << "������� ������: ";
		cin.getline(S, '\n');
		cout << "������� � ������\"" << S << "\"\n";
		Dc.InsertFront(S);
		cout << "������� ������: ";
		cin.getline(S, '\n');
		cout << "������� � �����\"" << S << "\"\n";
		Dc.InsertRear(S);
		cout << "������� ������: ";
		cin.getline(S, '\n');
		cout << "������� � �����\"" << S << "\"\n";
		Dc.InsertRear(S);
		cout << "������� ������: ";
		cin.getline(S, '\n');
		cout << "������� � �����\"" << S << "\"\n";
		Dc.InsertRear(S);
		cout << "�������: ";
		Dc.Browse(Print);
		cout << "\n�������� �� ������.\n";
		Dc.DeleteFront();
		cout << "�������: ";
		Dc.Browse(Print);
		cout << "\n�������� �� �����.\n";
		Dc.DeleteRear();
		cout << "�������: ";
		Dc.Browse(Print);
		cout << "\n������� ������ ����������� ��������: ";
		cin >> n;
		cout << "������� �� ������� " << n << ": " << Dc.GetByIndex(n);
		cout << "\n������� �������� ������������ �������� � ������ ��������, �������� �������� ����� �������� �� ��������: ";
		cin.ignore(1024, '\n');
		cin.getline(S, '\n');
		cin >> n;
		Dc.SetByIndex(S, n);
		cout << "�������: ";
		Dc.Browse(Print);
		cout << "\n������� ����� ������������� �������: ";
		Dc.Browse(Ch);
		cout << endl;
		cout << "������������� ������������ �����������. ����� ����������� �������, �������������� �������� ������������ ������.\n";
		TDeque<char*>T�;
		T� = Dc;
		T�.Browse(Print);
		cout << endl;
		return 0;
	}
	catch (DQException E)
	{
		cout << E.what() << endl;
		return 0;
	}
}