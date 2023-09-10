#include <iostream>
using namespace std;
int main()
{
	const char* s = "Ваша работа";
	int n = 0;
	while (*s++) ++n;
	cout << n;
}