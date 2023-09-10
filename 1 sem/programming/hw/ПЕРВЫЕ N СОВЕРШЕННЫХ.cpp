#include <iostream>
using namespace std;
int main()
{
	int n, cnt = 0, i = 1, a = 2, sum = 0;
	cin >> n;
	while (cnt != 0)
	{
		while (a == sum)
		{ 
			if (a % i == 0)
			{
				sum = sum + i;
				i++;
			}
			a++;
			cnt = cnt + 1;
			sum = sum;
		}
	}
	
  return 0;
}