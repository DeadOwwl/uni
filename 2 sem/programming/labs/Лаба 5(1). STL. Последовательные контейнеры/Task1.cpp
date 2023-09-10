#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <string>
#include <functional>

using namespace std;

vector <int> V;
int a(-1), b(-1), intSum(0);

void fInput()
{
	cout << "������� ������� �����!\n��� ������ ������ ������� ������������� �������� ��� �������. ���� ����������� �����������.\n��� ��������� ����� ������� \"End\".\n��������� ��������:\n";
	string Input(" ");
	while (cin)
	{
		getline(cin, Input, '\n');
		if (Input == "End")
			break;
		else
			if (Input.find_first_not_of("0123456789") != -1)
				continue;
			else
				V.push_back(stoi(Input));
	}
}

int fPlus(int& element)
{
	element += intSum;
	return element;
}

bool fEven(int& element)
{
	return (abs(element) % 2 == 0);
}

int main()
{
	try 
	{
		setlocale(LC_ALL, "rus");

		fInput();
		
		cout << "����� ��������� �������: " << accumulate(V.begin(), V.end(), 0) << endl;

		cout << "����� ���������� ����� �������: " << V.size() << endl;

		int iNum(0);
		cout << "������� ����� ��� ��������� � ��� ��������� �������: ";
		cin >> iNum;
		cout << "���������� �����, ������ ���������: " << count(V.begin(), V.end(), iNum) << endl;

		cout << "������� �����-������� ��� �������� ���������� ��������� �������, ������ ���: ";
		cin >> iNum;
		cout << "���������� ����� ������� ������ ���������: " << count_if(V.begin(), V.end(), bind2nd(greater<int>(), iNum)) << endl;

		cout << "������ �� ������ 0 �� ������� �������������� ��������� �������: ";
		copy(V.begin(), V.end(), ostream_iterator<int>(cout, "  "));
		cout << endl;
		replace(V.begin(), V.end(), 0, (int)(accumulate(V.begin(), V.end(), 0) / V.size()));
		cout << "������ ����� ������ 0 �� ������� �������������� ��������� �������: ";
		copy(V.begin(), V.end(), ostream_iterator<int>(cout, "  "));
		cout << endl;

		cout << "������� �������� ������� ��� ���������� ����� ��� �����.\n���������� ������� ������ ������� ���������: ";
		while (a < 0 || a > V.size() || a > b || b < 0 || b > V.size())
			cin >> a >> b;
		intSum = accumulate(V.begin() + a, V.begin() + b, 0);
		for_each(V.begin(), V.end(), fPlus);
		cout << "������ ����� ���������� � ������� �������� ������� ����� ����� �� ��������� ���������: ";
		copy(V.begin(), V.end(), ostream_iterator<int>(cout, " "));
		cout << endl;

		replace_if(V.begin(), V.end(), fEven, *max_element(V.begin(), V.end()) - *min_element(V.begin(), V.end()));
		cout << "������ ����� ������ ���� ������ ����� �� �������� ������������� � ������������ ���������: ";
		copy(V.begin(), V.end(), ostream_iterator<int>(cout, " "));
		cout << endl;

		for (vector <int>::iterator i = V.begin(); i != V.end(); i++)
		{
			for (vector <int>::iterator j = i + 1; j != V.end();)
			{
				if (*i == *j)
					j = V.erase(j);
				else
					j++;
			}
		}
		cout << "������ ����� �������� ������ �� ������ ���������: ";
		copy(V.begin(), V.end(), ostream_iterator<int>(cout, " "));

		return 0;
	}
	catch (const char* Error)
	{
		cout << Error << endl;
		return 0;
	}
}