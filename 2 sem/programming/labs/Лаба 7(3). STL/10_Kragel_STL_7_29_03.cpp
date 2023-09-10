#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <functional>
#include <numeric>
#include <algorithm>
#include <Windows.h>

using namespace std;

ifstream Input("D:\\alink\\bsu\\2 s\\prog\\labs\\Лаба 7, Stl\\in.txt");

struct SMark
{
	string Subject;
	int Mark;
};

struct SStudData
{
	string Name;
	int Number;
	vector <SMark> Marks;
};

void fCheckFile()
{
	if (!Input.is_open())
		throw "Ошибка открытия файла ввода";
	if (Input.peek() == EOF)
		throw "Файл ввода пуст";
}

map<int, SStudData> fFillIn(map<int, SStudData>& sData)
{
	bool  q(false);
	while (!Input.eof())
	{
		SStudData sS;
		getline(Input, sS.Name, ';');
		if (q == true)
			(sS.Name).erase(0, 1);
		Input >> sS.Number;
		SMark sM;
		char c;
		c = Input.peek();
		while (c!='\n')
		{
			if (Input.eof())
				break;
			Input.putback(c);
			Input >> sM.Subject >> sM.Mark;
			(sS.Marks).push_back(sM);
			c = Input.peek();
		}
		sData.insert(make_pair(sS.Number, sS));
		q = true;
	}
	return sData;
}

void fPrint(map<int, SStudData>& sData)
{
	map <int, SStudData>::iterator M;
	vector <SMark>::iterator V;
	for (M = sData.begin(); M != sData.end(); M++) {
		cout << "Номер зачетки: " << ((*M).second).Number << endl << "Имя: " << ((*M).second).Name << endl << "Итоги семестра: " << endl;
		for (V = (((*M).second).Marks).begin(); V != (((*M).second).Marks).end(); V++)
			cout << "  " << (*V).Subject << " - " << (*V).Mark << endl;
		cout << endl;
	}
}

double fAvAr(vector <SMark> vec)
{
	vector <int> dvek;
	for (vector <SMark>::iterator i = vec.begin(); i != vec.end(); i++)
		dvek.push_back((*i).Mark);
	int s(accumulate(dvek.begin(), dvek.end(), 0));
	return(((double)(s) / dvek.size()));
}

void fPrintAv(map <int, SStudData>& sData)
{
	map <int, SStudData>::iterator M;
	vector <SMark>::iterator V;
	for (M = sData.begin(); M != sData.end(); M++) {
		cout << "Номер зачетки: " << ((*M).second).Number << endl << "Имя: " << ((*M).second).Name << endl << "Итоги семестра: " << endl;
		for (V = (((*M).second).Marks).begin(); V != (((*M).second).Marks).end(); V++)
			cout << "  " << (*V).Subject << " - " << (*V).Mark << endl;
		cout << "Средний балл: " << fAvAr(((*M).second).Marks) << endl;
		cout << endl;
	}
}

bool fSortPar(SStudData s1, SStudData s2)
{
	if (s1.Name != s2.Name)
		return (s1.Name < s2.Name);
	else
		return (fAvAr(s1.Marks) > fAvAr(s2.Marks));
}

void fPrintnFNAv(map <int, SStudData>& sData)
{
	map <int, SStudData>::iterator M;
	vector <SStudData> vS;
	vector <SStudData>::iterator vvS;
	for (M = sData.begin(); M != sData.end(); M++)
		vS.push_back((*M).second);
	sort(vS.begin(), vS.end(), fSortPar); 
	int n(1);
	for (vvS = vS.begin(), n; vvS != vS.end(); vvS++, n++)
		cout << n << ". Имя: " << (*vvS).Name << "\nНомер зачетки: " << (*vvS).Number << "\nСредний балл: " << fAvAr((*vvS).Marks) << endl << endl;
}

bool fSortParAv(SStudData s1, SStudData s2)
{
		return (fAvAr(s1.Marks) > fAvAr(s2.Marks));
}

void fPrintNecStAv(map <int, SStudData>& sData)
{
	map <int, SStudData>::iterator M;
	cout << "Введите необходимый промежуток среднего балла от 0 до 10 (сначала нижнее значение, после - верхнее): ";
	double inf(-1), sup(-1);
	cin >> inf >> sup;
	while (inf < 0 || inf>10 || sup < 0 || sup>10 || inf>sup)
	{
		cout << "Введены недопустимые значения. Повторите ввод: ";
		cin >> inf >> sup;
	}
	vector<SStudData> nV;
	vector<SStudData>::iterator inV;
	for (M = sData.begin(); M != sData.end(); M++)
		if (fAvAr((*M).second.Marks) >= inf && fAvAr((*M).second.Marks) <= sup)
			nV.push_back((*M).second);
	sort(nV.begin(), nV.end(), fSortParAv);
	if (nV.empty())
		cout << "Студентов со средним баллом из заданного промежутка нет.\n";
	else
		for (inV = nV.begin(); inV != nV.end(); inV++)
			cout << "Имя: " << (*inV).Name << "\nСредний балл: " << fAvAr((*inV).Marks) << endl;
}

void fPrintNecStSub(map <int, SStudData>& sData)
{
	map <int, SStudData>::iterator M;
	vector<SMark>::iterator V;
	cout << "Введите необходимый предмет для поиска студентов, сдававших его: ";
	string sub;
	cin.ignore(1024, '\n');
	getline(cin, sub, '\n');
	vector<SStudData> nS;
	vector<SStudData>::iterator inS;

	for (M = sData.begin(); M != sData.end(); M++)
		for (V = ((*M).second.Marks).begin(); V != ((*M).second.Marks).end(); V++)
			if ((*V).Subject == sub)
				nS.push_back((*M).second);
	if (nS.empty())
		cout << "Студентов, сдававших этот предмет, нет.\n";
	else
	{
		cout << "Суденты, сдававшие заданный предмет: \n";
		for (inS = nS.begin(); inS != nS.end(); inS++)
		{
			cout << "Имя: " << (*inS).Name << "\nНомер зачетки: " << (*inS).Number << "\nОценка за экзамен: ";
			for (V = ((*inS).Marks).begin(); V != ((*inS).Marks).end(); V++)
				if ((*V).Subject == sub)
					cout << (*V).Mark << endl << endl;
		}
	}
}

void fPrintNumStSub(map <int, SStudData>& sData)
{
	struct SubNum
	{
		string Subj;
		int Num;
	};
	map <int, SStudData>::iterator M;
	vector <SMark>::iterator V;
	vector<SubNum> SN;
	vector<SubNum>::iterator iSN;
	M = sData.begin();
	for (V = ((*M).second).Marks.begin(); V != ((*M).second).Marks.end(); V++)
	{
		SubNum ssNN;
		ssNN.Subj = (*V).Subject;
		ssNN.Num = 0;
		SN.push_back(ssNN);
	}
	for (M = sData.begin(); M != sData.end(); M++)
	{
		bool cCom(false);
		for (V = ((*M).second).Marks.begin(); V != ((*M).second).Marks.end(); V++)
		{
			for (iSN = SN.begin(); iSN != SN.end(); iSN++)
				if ((*iSN).Subj == (*V).Subject)
				{
					cCom = true;
					(*iSN).Num++;
				}
			if (cCom == false)
				for (iSN = SN.begin(); iSN != SN.end(); iSN++)
					if ((*iSN).Subj != (*V).Subject)
					{
						SubNum ssNN;
						ssNN.Subj = (*V).Subject;
						ssNN.Num = 1;
						SN.push_back(ssNN);
					}
		}
	}
	for (iSN = SN.begin(); iSN != SN.end(); iSN++)
		cout << "Предмет: " << (*iSN).Subj << "\nКоличество сдававших экзамен студентов: " << (*iSN).Num << endl << endl;
}

struct SubAv
{
	string Subj;
	int Av;
	int Num;
};

bool fSortSubAv(SubAv s1, SubAv s2)
{
	return (((double)s1.Av) / s1.Num > ((double)s2.Av) / s2.Num);
}

void fPrintSbAv(map <int, SStudData>& sData)
{
	map <int, SStudData>::iterator M;
	vector <SMark>::iterator V;
	vector<SubAv> SA;
	vector<SubAv>::iterator iSA;
	M = sData.begin();
	for (V = ((*M).second).Marks.begin(); V != ((*M).second).Marks.end(); V++)
	{
		SubAv ssAA;
		ssAA.Subj = (*V).Subject;
		ssAA.Av = 0;
		ssAA.Num = 0;
		SA.push_back(ssAA);
	}
	for (M = sData.begin(); M != sData.end(); M++)
	{
		int s(0);
		bool Fl(false);
		for (V = ((*M).second).Marks.begin(); V != ((*M).second).Marks.end(); V++)
		{
			for (iSA = SA.begin(); iSA != SA.end(); iSA++)
				if ((*iSA).Subj == (*V).Subject)
				{
					Fl = true;
					(*iSA).Av += (*V).Mark;
					(*iSA).Num++;
					break;
				}
			if (Fl == false)
				for (iSA = SA.begin(); iSA != SA.end(); iSA++)
					if ((*iSA).Subj != (*V).Subject)
					{
						SubAv ssAA;
						ssAA.Subj = (*V).Subject;
						ssAA.Av = (*V).Mark;
						(*iSA).Num = 1;
						SA.push_back(ssAA);
					}
		}
	}
	sort(SA.begin(), SA.end(), fSortSubAv);
	for (iSA = SA.begin(); iSA != SA.end(); iSA++)
		cout << "Предмет: " << (*iSA).Subj << "\nСредний балл по предмету: " << ((double)(*iSA).Av)/ (*iSA).Num << endl << endl;
}

int fSum(vector <SMark> vec)
{
	vector <int> dvek;
	for (vector <SMark>::iterator i = vec.begin(); i != vec.end(); i++)
		dvek.push_back((*i).Mark);
	return(accumulate(dvek.begin(), dvek.end(), 0));
}

void fPrintMaxStuf(map <int, SStudData>& sData)
{
	multimap<int, string> mMaxStud;
	multimap <int, string>::iterator m;
	map <int, SStudData>::iterator M;
	int Max(0);
	for (M = sData.begin(); M != sData.end(); M++)
	{
		if (fSum((*M).second.Marks) >= Max)
		{
			Max = fSum((*M).second.Marks);
			mMaxStud.insert(make_pair(Max, (*M).second.Name));
		}
	}
	cout << "Студенты с максимальными баллами: \n";
	for (m = mMaxStud.begin(); m != mMaxStud.end(); m++)
		if ((*m).first == Max)
			cout << "Имя: " << (*m).second << "\nКоличество набранных баллов: " << (*m).first << endl << endl;
}

void fPrintLessF(map <int, SStudData>& sData)
{
	map <int, SStudData>::iterator M;
	for (M = sData.begin(); M != sData.end(); M++)
	{
		for (vector <SMark>::iterator i = (*M).second.Marks.begin(); i != (*M).second.Marks.end(); i++)
		{
			if ((*i).Mark < 4)
			{
				cout << "Номер зачетки: " << ((*M).second).Number << endl << "Имя: " << ((*M).second).Name << endl << "Итоги семестра: " << endl;
				for (vector <SMark>::iterator V = (((*M).second).Marks).begin(); V != (((*M).second).Marks).end(); V++)
					cout << "  " << (*V).Subject << " - " << (*V).Mark << endl;
				cout << endl;
				break;
			}
		}
	}
}


int main()
{
	try
	{
		setlocale(0, "");
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);

		map <int, SStudData> sData;

		fCheckFile();

		cout << "____________________________________________________________1___________________________________________________________\n";

		sData = fFillIn(sData);
		if (sData.empty())
			cout << "Контейнер \"map\" пуст\n";
		else
			cout << "Контейнер \"map\" успешно заполнен.\n";

		cout << "____________________________________________________________2___________________________________________________________\n";

		fPrint(sData);

		cout << "____________________________________________________________3___________________________________________________________\n";

		fPrintAv(sData);

		cout << "____________________________________________________________4___________________________________________________________\n";

		fPrintnFNAv(sData);

		cout << "____________________________________________________________5___________________________________________________________\n";

		fPrintNecStAv(sData);

		cout << "____________________________________________________________6___________________________________________________________\n";

		fPrintNecStSub(sData);

		cout << "____________________________________________________________7___________________________________________________________\n";

		fPrintNumStSub(sData);

		cout << "____________________________________________________________8___________________________________________________________\n";

		fPrintSbAv(sData);

		cout << "____________________________________________________________9___________________________________________________________\n";

		fPrintMaxStuf(sData);

		cout << "____________________________________________________________10_________________________________________________________\n";

		fPrintLessF(sData);

		Input.close();
		return 0;
	}
	catch (const char* Error)
	{
		cout << Error << endl;
		Input.close();
		return 0;
	}
}