#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <iterator>
#include <functional>
#include <numeric>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <Windows.h>

using namespace std;

ifstream Input("D:\\alink\\bsu\\2 s\\prog\\tr\\����������� STL �������\\data.txt");
ofstream Output("D:\\alink\\bsu\\2 s\\prog\\tr\\����������� STL �������\\answers.txt");

void fCheckFiles()
{
	if (!Input.is_open())
		throw"������ �������� ����� �����";
	if (Input.peek() == EOF)
		throw"���� ����� ����";
	if (!Output.is_open())
		throw"����� �������� ����� ������";
}

class Bus;
class LessString;
class CompareRegister;
typedef vector<string> vDrivers;
typedef list<Bus> lBuses;
typedef set<string, LessString> sSet;

vDrivers mV, firstV, littleV;
vDrivers::iterator v;
lBuses L;
lBuses::iterator l;

//yes
static bool fComp(const char c1, const char c2)
{
	return tolower(c1) < tolower(c2);
}

//yes
static bool ifEqual(const string s1, const string s2)
{
	if (s1.size() == s2.size())
		if (!lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), fComp) && !lexicographical_compare(s2.begin(), s2.end(), s1.begin(), s1.end(), fComp))
			return true;
	return false;
}

//yes
class Bus
{
private:
	int Number;
	string Name;
	vDrivers Drivers;
public:
	Bus():Number(0), Name("��� �� ����������") {}
	Bus(int n, string name, vDrivers dr)
	{
		Number = n;
		Name = name;
		Drivers = dr;
	}
	vDrivers GetDrivers() { return Drivers;}
	void SetDrivers(vDrivers v) { Drivers = v; }
	int GetNumber() const { return Number;}
	string GetName() const { return Name; }
	friend bool operator < (const Bus& B1, const Bus& B2)
	{
		if (ifEqual(B1.Name, B2.Name))
			return B1.Number < B2.Number;
		return(lexicographical_compare(B1.Name.begin(), B1.Name.end(), B2.Name.begin(), B2.Name.end(), fComp));
	}
	void Print()const
	{
		Output << "����� ��������: " << Number << "\n�������: " << Name << "\n��������: ";
		copy(Drivers.begin(), Drivers.end(), ostream_iterator<string>(Output, " "));
		Output << endl << endl;
	}
	void PrintConsole()const
	{
		cout << "����� ��������: " << Number << "\n�������: " << Name << "\n��������: ";
		copy(Drivers.begin(), Drivers.end(), ostream_iterator<string>(cout, " "));
		cout << endl << endl;
	}
};

//yes
class LessString : binary_function<string, string, bool>
{
public:
	bool operator()(string s1, string s2) const
	{
		return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), fComp);
	}
	friend static bool fComp(const char c1, const char c2);
};

//yes
class CompareRegister
{
public:
	string String;
	friend static bool ifEqual(const string s1, const string s2);
	friend static bool fComp(const char c1, const char c2);
	CompareRegister(string S)
	{
		String = S;
	}
	bool operator()(Bus& B)
	{
		string sS = B.GetName();
		return(ifEqual(sS, String));
	}

};

//yes
string fTranslate(string s)
{
	string S(s);
	for (unsigned i(0); i < S.size(); i++)
		if ((S[i] >= -128) && (S[i] <= -81))
			S[i] += 64;
		else
			if ((S[i] >= -32) && S[i] - 17)
				S[i] += 16;
	return S;
}

//yes
string fEdit(string& s)
{
	int i(0);
	if (s[0] == ' ')
	{
		i = s.find_first_not_of(" ", 0);
		s.erase(0, i);
	}
	if (s[s.size()]=='\n')
		s.erase(s.size(), 1);
	return s;
}

//yes
int fInput(lBuses& lt)
{
	string route, name, driver, s;
	vDrivers vect;
	int iRoute;
	unsigned begin(0), end(0);
	fCheckFiles();
	while (!Input.eof())
	{
		getline(Input, s, '\n');

		begin = s.find_first_of("1234567890", begin);
		end = s.find_first_of(";", begin);
		route = s.substr(begin, end - begin);
		route = fEdit(route);
		begin = end;
		iRoute = stoi(route);

		begin = s.find_first_not_of(";", begin);
		end = s.find_first_of(";", begin);
		name = s.substr(begin, end - begin);
		name = fEdit(name);
		begin = end;

		while (end != -1)
		{
			begin = s.find_first_not_of(";", begin);
			end = s.find_first_of(";", begin);
			driver = s.substr(begin, end - begin);
			driver = fEdit(driver);
			begin = end;
			vect.push_back(driver);
		}

		begin = end = 0;
		Bus bB(iRoute, name, vect);
		L.push_back(bB);
		vect.clear();
	}
	return 0;
}

//yes
void fAllDrivers(lBuses& L, sSet& Set)
{
	sSet::iterator ss;
	for (l = L.begin(); l != L.end(); l++)
	{
		firstV = (*l).GetDrivers();
		for (unsigned i(0); i < firstV.size(); i++)
			Set.insert(firstV[i]);
	}
	if (Set.size() == 0)
		Output << "��������� ���.\n";
	else
	{
		Output << "��������: \n";
		copy(Set.begin(), Set.end(), ostream_iterator<string>(Output, " \n"));
	}
	Output << endl;
}

//yes
void fDoNotWork(lBuses& L, string NN)
{
	bool flag(false);
	Output << "��������. �� ������� �� �������� " << NN << ": ";
	for (l = L.begin(); l != L.end(); l++)
	{
		mV = (*l).GetDrivers();
		bool p(true);
		for (unsigned i(0); i < mV.size(); i++)
			if (ifEqual(NN, mV[i]))
				p = false;
		if (p == true)
		{
			Output << (*l).GetName() << "; ";
			flag = true;
		}
	}
	if (flag == false)
		Output << "��� ����� ���������.";
	Output << endl;
}

//yes
void fSearchBestWorker(lBuses& L)
{
	lBuses::iterator ll(L.begin());
	vDrivers dr((*ll).GetDrivers());
	vDrivers::iterator vv(dr.begin());
	sSet mSet, Set1, Set2;
	for (vv; vv != dr.end(); vv++)
		mSet.insert(*vv);
	Output << "\n�������� �� ���� ���������: ";
	for (ll; ll != L.end(); ll++)
	{
		Set1.clear();
		dr = (*ll).GetDrivers();
		for (vv = dr.begin(); vv != dr.end(); vv++)
		{
			Set1.insert(*vv);
			set_intersection(mSet.begin(), mSet.end(), Set1.begin(), Set1.end(), inserter(Set2, Set2.begin()), LessString());
		}
		mSet = Set2;
		Set2.clear();
	}
	if (mSet.size() == 0)
		Output << "�� ����������.\n";
	else
	{
		copy(mSet.begin(), mSet.end(), ostream_iterator<string>(Output, " "));
		Output << endl;
	}
	Output << endl;
}

//yes
void fCountRoutes(string fRoute, lBuses& L)
{
	int nRoutes = count_if(L.begin(), L.end(), CompareRegister(fRoute));
	if (nRoutes != 0)
		Output << "���������� ��������� �� ����������� " << fRoute << ": " << nRoutes << endl;
	else
		Output << "�� ����������� " << fRoute << " ��� ���������" << endl;
}

//yes
void fDeleteDriver(string fDr, lBuses& L)
{
	bool flag(false);
	for (l = L.begin(); l != L.end(); l++)
	{
		littleV = (*l).GetDrivers();
		bool p(false);
		for (v = littleV.begin(); v != littleV.end(); v++)
		{
			string s = (*v);
			if (ifEqual(s, fDr))
			{
				p = true;
				flag = true;
				littleV.erase(v);
				break;
			}
		}
		if (p = true)
			(*l).SetDrivers(littleV);
	}
	if (flag == false)
		Output << "�������� " << fDr << " �� ����������. ������ �� ���������.\n\n";
	else
	{
		Output << "������ ����� �������� " << fDr << ": \n";
		for_each(L.begin(), L.end(), mem_fun_ref(&Bus::Print));
	}
}

void fDeleteDriverConsole(string fDr, lBuses& L)
{
	bool flag(false);
	for (l = L.begin(); l != L.end(); l++)
	{
		littleV = (*l).GetDrivers();
		bool p(false);
		for (v = littleV.begin(); v != littleV.end(); v++)
		{
			string s = (*v);
			if (ifEqual(s, fDr))
			{
				p = true;
				flag = true;
				littleV.erase(v);
				break;
			}
		}
		if (p = true)
			(*l).SetDrivers(littleV);
	}
	if (flag == false)
		cout << "�������� " << fDr << " �� ����������. ������ �� ���������.\n\n";
	else
	{
		cout << "������ ����� �������� " << fDr << ": \n";
		for_each(L.begin(), L.end(), mem_fun_ref(&Bus::PrintConsole));
	}
}


int main()
{
	try
	{
		setlocale(0, "");
		//SetConsoleCP(1251);
		//SetConsoleOutputCP(1251);
		
		Output << "������ ������.\n ����� ������.\n\n";
		fInput(L);
		Output << "������ �� ����������: \n";
		for (l = L.begin(); l != L.end(); l++)
			(*l).Print();

		L.sort();

		Output << "������ ����� ����������: \n";
		for_each(L.begin(), L.end(), mem_fun_ref(&Bus::Print));

		Output << " ����� ������. \n\n";

		sSet Set;
		sSet::iterator s;
		fAllDrivers(L, Set);

		string fio;
		fDoNotWork(L, "����");
		fDoNotWork(L, "�������");
		fDoNotWork(L, "�����");

		fSearchBestWorker(L);

		Output << "����� ������.\n\n";

		fCountRoutes("��������", L);
		fCountRoutes("�����", L);

		Output << "�������� ���������\n";
		fDeleteDriver("����", L);
		fDeleteDriver("������", L);
		fDeleteDriver("����", L);

		fSearchBestWorker(L);

		cout << "����� � ���� ��������.\n����� ���������.\n�������� ���� �������� � �������.\n��������� �� ������\n������� �������� ��� ��������: ";
		string name;
		getline(cin, name, '\n');
		name = fTranslate(name);
		fDeleteDriverConsole(name, L);

		Input.close();
		Output.close();
		return 0;
	}
	catch (const char* Error)
	{
		cout << Error << endl;
		Input.close();
		Output.close();
		return 0;
	}
}