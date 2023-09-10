#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;
int main()
{
	int m;
	cin >> m;
	struct List {
		int Salary;
		string LastName;
		string Nationality;
	};
	List* PlayersFootballTeam = new List[m];
	for (int i = 0; i < m; i++) {
		cin >> PlayersFootballTeam[i].Salary;
		gets(PlayersFootballTeam[i].LastName);
	}
	return 0;
}