#include <iostream>
using namespace std;
int main()
{
	const char* s = "���� ������";
	int n = 0;
	while (*s++) ++n;
	cout << n;
}