#include "Persons.h"
#include <typeinfo>
#include <windows.h>
#include <iomanip>

using namespace std;


int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try
	{
		int n(0), Choice(0);
		Person* Array[500];
		bool FlagS = false, FlagP = false;
		cout << "����� ���������� � ��������� ��� ������ � ��������������� � ����������!\n" << endl;
		do
		{

			cin >> Choice;
			cout << "_______________________________________________________________________\n";
			cout << endl;
			cout << "����\n";
			cout << "1. ������ ��������. " << endl;
			cout << "2. ������ �������������. " << endl;
			cout << "3. ������� ������ ���������. " << endl;
			cout << "4. ������� ������ ��������������. " << endl;
			cout << "5. ��������� ������. " << endl;
			cout << "_______\n";

			switch (Choice) {
			case 1:
			{
				cout << "������� ��� ��������: ";
				char* NewName = new char[256];
				cin.ignore();
				cin.getline(NewName, 256, '\n');
				int Gr, Cr;
				cout << "������� ����, �� ������� ��������� �������: ";
				cin >> Cr;
				cout << "������� ������ ��������: ";
				cin >> Gr;
				Student* AnotherStudent = new Student(NewName, Cr, Gr);
				Array[n++] = AnotherStudent;
				delete[] NewName;
				FlagS = true;
				cout << endl;
				system("pause");
				system("cls");
				break;
			}
			case 2:
			{
				cout << "������� ��� �������������: ";
				char* NewName = new char[256];
				cin.ignore();
				cin.getline(NewName, 256, '\n');
				char* Caf = new char[256];
				cout << "������� ������� �������������: ";
				cin.getline(Caf, 256, '\n');
				Professor* AnotherProfessor = new Professor(NewName, Caf);
				Array[n++] = AnotherProfessor;
				delete[] NewName;
				FlagP = true;
				cout << endl;
				system("pause");
				system("cls");
				break;
			}
			case 3:
			{

				if (FlagS == false)
					cout << "��� ������������������ ���������.\n";
				else
				{
					cout << "������ ���������: ";
					for (int i(0); i < n; i++)
					{
						if (typeid(*Array[i]) == typeid(Student))
							Array[i]->Print();
					}
				}
				break;
				cout << endl;
				system("pause");
				system("cls");
			}
			case 4:
			{
				if (FlagP == false)
					cout << "��� ������������������ ��������������.\n";
				else
				{
					cout << "������ ��������������: ";
					for (int i(0); i < n; i++)
					{
						if (typeid(*Array[i]) == typeid(Professor))
							Array[i]->Print();
					}
				}
				break;
				cout << endl;
				system("pause");
				system("cls");
			}
			case 5:
			{
				cout << "������ ���������! ������ ����� ����� ������ � ���������� ����������� ������� � ���.\n";
				system("pause");
				system("cls");
				break;
			}
			default:
			{
				cout << "������ �������������� �������. ������������ � ���� ��� ��� � ���������, ����������, ����.\n";
				system("pause");
				system("cls");
				return 0;
			}
			}
		} while (Choice != 5);


		Person* ArrayStudents[500];
		int q(0);
		for (int i(0); i < n; i++)
			if (typeid(*Array[i]) == typeid(Student))
				ArrayStudents[q++] = Array[i];
		int ArrayGroups[500][3];
		int w(0);
		for (int p(0); p < 500; p++)
		{
			ArrayGroups[p][0] = 0;
			ArrayGroups[p][1] = 0;
			ArrayGroups[p][2] = 0;
		}
		for (int i(0); i < q; i++)
		{
			for (int j(i); j < q; j++)
			{
				bool FL(false);
				if ((dynamic_cast<Student*>(ArrayStudents[i])->GetGroup() == dynamic_cast<Student*>(ArrayStudents[j])->GetGroup()) && 
					dynamic_cast<Student*>(ArrayStudents[i])->GetCourse() == dynamic_cast<Student*>(ArrayStudents[j])->GetCourse())
				{
					for (int p(0); p < w; p++)
					{
						if (ArrayGroups[p][0] == dynamic_cast<Student*>(ArrayStudents[i])->GetGroup() && 
							ArrayGroups[p][2] == dynamic_cast<Student*>(ArrayStudents[j])->GetCourse())
						{
							ArrayGroups[p][1]++;
							FL = true;
						}
					}
					if (FL == false)
					{
						ArrayGroups[w][0] = dynamic_cast<Student*>(ArrayStudents[i])->GetGroup();
						ArrayGroups[w][1] = 1;
						ArrayGroups[w][2] = dynamic_cast<Student*>(ArrayStudents[i])->GetCourse();
						w++;
					}
				}
			}
		}
		int MaxNum(0), MaxGroup(0), MaxCourse(0);
		int k(0);
		int FlagMax = 0;
		int e(0);
		int ArrayMax[500][3];
		if (w==q)
			cout << "������ � ���������� ����������� ������� �� ����������.\n ������, �� ���� ������� ���������� ���������� �������.\n";
		else
		{
			for (int i(0); i < w; i++)
			{
				if (ArrayGroups[i][1] > MaxNum || k == 0)
				{
					MaxNum = ArrayGroups[i][1];
					MaxGroup = ArrayGroups[i][0];
					MaxCourse = ArrayGroups[i][2];
					FlagMax = 1;
					k = 1;
				}
				else
					if (ArrayGroups[i][1] == MaxNum)
					{
						if (e == 0)
						{
							ArrayMax[e][0] = MaxGroup;
							ArrayMax[e][1] = MaxNum;
							ArrayMax[e][2] = MaxCourse;
							e++;
						}
						FlagMax = 2;
						ArrayMax[e][0] = ArrayGroups[i][0];
						ArrayMax[e][1] = ArrayGroups[i][1];
						ArrayMax[e][2] = ArrayGroups[i][2];
						e++;
					}
			}
			if (FlagMax == 1)
			{
				cout << "����� ������ � ����� � ��������� ����������� �������: " << MaxGroup << " ������, " << MaxCourse << " ����." << endl;
				for (int i(0); i < q; i++)
				{
					if (dynamic_cast<Student*>(ArrayStudents[i])->GetGroup() == MaxGroup &&
						dynamic_cast<Student*>(ArrayStudents[i])->GetCourse() == MaxCourse)
					{
						Array[i]->Print();
						cout << "ID: " << Array[i]->GetID() << endl;
						cout << "_________\n";
					}
				}
			}
			else
			{
				cout << "����� � ���������� ����������� ������� ���������. �������� ����.\n";
				for (int i(0); i < q; i++)
				{
					for (int j(0); j < e; j++)
						if (dynamic_cast<Student*>(ArrayStudents[i])->GetGroup() == ArrayMax[j][0] &&
							dynamic_cast<Student*>(ArrayStudents[i])->GetCourse() == ArrayMax[j][2])
						{
							Array[i]->Print();
							cout << "ID: " << Array[i]->GetID() << endl;
							cout << "_________\n";
						}
				}
				cout << "___________________________\n";
			}
		}
	}
	catch (const char* error)
	{
		cout << error << endl << "������������� ��������� ��� ��������� ������.\n";
	}

}