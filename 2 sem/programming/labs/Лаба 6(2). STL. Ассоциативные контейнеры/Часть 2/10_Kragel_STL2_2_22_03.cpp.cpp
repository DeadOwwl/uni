#include <iostream>
#include <fstream>
#include <numeric>
#include <functional>
#include <map>
#include <iterator>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cctype>

using namespace std;

ifstream Input("D:\\alink\\bsu\\2 s\\prog\\labs\\���� 6, STL ������������� ����������. ������� 2\\in.txt");
ofstream Output("D:\\alink\\bsu\\2 s\\prog\\labs\\���� 6, STL ������������� ����������. ������� 2\\out.txt");

void fCheck()
{
	if (!Input.is_open())
		throw "������ �������� ����� �����.";
	if (!Output.is_open())
		throw "������ �������� ����� ������.";
	if (Input.peek() == EOF)
		throw "���� ����� ����.";
}

string fToLower(string w)
{
	for (unsigned i(0); i < w.size(); i++)
		w[i] = tolower(w[i]);
	return w;
}

int main()
{
	try
	{
		setlocale(0, "");
		fCheck();
		map <string, int> M;
		while (!Input.eof())
		{
			string w;
			bool flComp(false);
			Input >> w;
			w = fToLower(w);
			map <string, int>::iterator i = M.begin();
			for (i; i != M.end(); i++)
				if (w == i->first)
				{
					flComp = true;
					break;
				}
			if (flComp == true)
				i->second++;
			else
				M.insert(make_pair(w, 1));
		}
		map <string, int>::iterator i = M.begin();
		Output << "��������� ������� ��� ���������:\n";
		for (i; i != M.end(); i++)
			Output << i->first << " - " << i->second << endl;
		cout << "��������� ��������� �������. ��������� ����� ������.\n";
		Input.close();
		Output.close();
		return 0;
	}
	catch (const char* Error)
	{
		cout << Error << endl;
		Input.close();
		Output.close();
	}
}