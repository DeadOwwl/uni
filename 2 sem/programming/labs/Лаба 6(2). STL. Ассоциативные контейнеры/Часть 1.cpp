#include <iostream>
#include <numeric>
#include <functional>
#include <iterator>
#include <set>

using namespace std;

int main()
{
	setlocale(0, "");
	cout << "Введите число, меньше которого необходимо найти простые числа: ";
	int N(0);
	cin >> N;
	set <int> Set;
	for (int i(2); i <= N; i++)
		Set.insert(i);
	set <int> ::iterator i(Set.begin());
	set <int> ::iterator j(Set.begin());
	for (i; i != Set.end(); i++)
	{
		for (int k(*i* (*i)); k <= N; k += *i)
		{
			j = Set.find(k);
			if (j != Set.end())
				Set.erase(j);
		}
	}
	if (Set.size() == 0)
		cout << "Простых чисел нет.\n";
	else
	{
		cout << "Все простые числа, меньше " << N << ": ";
		copy(Set.begin(), Set.end(), ostream_iterator<int>(cout, " "));
	}
	return 0;
}