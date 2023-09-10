#include <iostream>
using namespace std;
int main()
{
	long long int m;
	cin >> m;
	int ch = m % 4, d = m % 9, od = m % 11;
	if (ch != 0 && d != 0 && od != 0) cout << "1";
	if (ch == 0 && d != 0 && od != 0) cout << "2";
	if (ch != 0 && d == 0 && od != 0) cout << "3";
	if (ch != 0 && d != 0 && od == 0) cout << "4";
	if (ch == 0 && d == 0 && od != 0) cout << "5";
	if (ch == 0 && d != 0 && od == 0) cout << "6";
	if (ch != 0 && d == 0 && od == 0) cout << "7";
	if (ch == 0 && d == 0 && od == 0) cout << "8";
	return 0;
}