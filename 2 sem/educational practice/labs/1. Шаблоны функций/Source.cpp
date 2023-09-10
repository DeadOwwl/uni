#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>
#pragma warning(disable:4996)

using namespace std;

bool flag(0);
int x[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int y[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };

template <typename T>
T MaxLocMin(int m, int n, T** Arr)
{
	T* Minimums = new T[m * n];
	unsigned l(0), p(0), count(0);
	for (unsigned i(0); i < m; i++)
		for (unsigned j(0); j < n; j++) 
		{
			for (unsigned k(0); k < 8; k++)
				if (i + x[k] >= 0 && i + x[k] < m && j + y[k] >= 0 && j + y[k] < n)
				{
					count++;
					if (Arr[i][j] < Arr[i + x[k]][j + y[k]])
						p++;
				}
			if (p == count)
				Minimums[l++] = Arr[i][j];
			p = 0;
			count = 0;
		}
	for (unsigned i(0); i < l; i++)
		for (unsigned j(i); j < l; j++)
			if (Minimums[i] < Minimums[j])
				swap(Minimums[i], Minimums[j]);
	if (Minimums[0] != Minimums[1])
		return Minimums[0];
	else
		return -9999;
}

char* MaxLocMin(int m, int n, char*** Arr)
{
	char** Minimums = new char*[m * n];
	unsigned l(0), p(0), count(0);
	for (unsigned i(0); i < m; i++)
		for (unsigned j(0); j < n; j++)
		{
			for (unsigned k(0); k < 8; k++)
				if (i + x[k] >= 0 && i + x[k] < m && j + y[k] >= 0 && j + y[k] < n)
				{
					count++;
					if (strcmp(Arr[i][j],Arr[i + x[k]][j + y[k]])<0)
						p++;
				}
			if (p == count)
				Minimums[l++] = Arr[i][j];
			p = 0;
			count = 0;
		}
	for (unsigned i(0); i < l; i++)
		for (unsigned j(i); j < l; j++)
			if (strcmp(Minimums[i],Minimums[j])<0)
				swap(Minimums[i], Minimums[j]);
	if (Minimums[0] == Minimums[1])
		flag = 1;
	return Minimums[0];
}

template <typename T>
void Print(int m, int n, T** Arr)
{
	for (unsigned i(0); i < m; i++)
	{
		for (unsigned j(0); j < n; j++)
			cout << setw(7) << Arr[i][j] ;
		cout << endl;
	}
}

void Print(int m, int n, char*** Arr)
{
	for (unsigned i(0); i < m; i++)
	{
		for (unsigned j(0); j < n; j++)
			cout << setw(10) << Arr[i][j];
		cout << endl;
	}
}

int main()
{
	try
	{
		setlocale(0, "");
		srand(time(NULL));
		int m(0), n(0);

		cout << "Целочисленные.\n";
		cout << "Введите размер матрицы: ";
		cin >> m >> n;
		int** ArrayInt = new int*[m];
		for (unsigned i(0); i < m; i++)
			ArrayInt[i] = new int[n];
		for (unsigned i(0); i < m; i++)
			for (unsigned j(0); j < n; j++)
				ArrayInt[i][j] = rand()%1000-500;
		Print(m, n, ArrayInt);
		if (MaxLocMin(m, n, ArrayInt) == -9999)
			cout << "Нет максимального из локальных минимумов.\n";
		else
			cout << "Максимальный из локальных минимумов: " << MaxLocMin(m, n, ArrayInt) << endl << endl;

		cout << "Вещественные.\n";
		cout << "Введите размер матрицы: ";
		cin >> m >> n;
		double** ArrayDouble = new double* [m];
		for (unsigned i(0); i < m; i++)
			ArrayDouble[i] = new double[n];
		for (unsigned i(0); i < m; i++)
			for (unsigned j(0); j < n; j++)
				ArrayDouble[i][j] =( rand() % 1000 - 500)*0.01;
		Print(m, n, ArrayDouble);
		if (MaxLocMin(m, n, ArrayInt) == -9999)
			cout << "Нет максимального из локальных минимумов.\n";
		else
			cout << "Максимальный из локальных минимумов: " << MaxLocMin(m, n, ArrayDouble) << endl << endl;

		cout << "Символьные.\n";
		cout << "Введите размер матрицы: ";
		cin >> m >> n;
		char*** ArraySymbol = new char** [m];
		for (unsigned i(0); i < m; i++)
			ArraySymbol[i] = new char*[n];
		for (unsigned i(0); i < m; i++)
			for (unsigned j(0); j < n; j++)
			{
				int l(0), k(rand() % 10);
				ArraySymbol[i][j] = new char[k+1];
				string Str;
				while (l != k) 
				{
					Str += static_cast<char>(rand() % (255 - 32 + 1) + 32);
					l++;
				}
				strcpy(ArraySymbol[i][j], Str.c_str());
			}
		Print(m, n, ArraySymbol);
		MaxLocMin(m, n, ArraySymbol);
		if (flag==1)
			cout << "Нет максимального из локальных минимумов.\n";
		else
			cout << "Максимальный из локальных минимумов: " << MaxLocMin(m, n, ArraySymbol) << endl << endl;
		return 0;
	}
	catch (const char* error)
	{
		cout << error << endl;
		return 0;
	}
}