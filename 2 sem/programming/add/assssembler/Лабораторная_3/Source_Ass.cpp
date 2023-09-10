
#include <iostream>
#include <ctime>

/*

Волков Евгений, 10а группа

Лабораторная по Ассемблеру №3

Условие:
В упорядоченный массив включить новый эемент так, чтобы не нарушилась упорядоченность.
*/

/*
Возможно у меня не получилось сделать _fastcall или _cdecl, 
поэтому я вставил такой же код в эти функции, как и в _stdcall. Но вроде всё правильно
*/
using namespace std;

extern "C" void __stdcall InputElement(int*, int, int);
extern "C" void __cdecl InputElementCd(int*, int, int);
extern "C" void __fastcall InputElementFC(int*, int, int);

const int NMAX = 30;

int main() 
{
	srand(time(NULL));
	int Array[NMAX]; int N; int k;
	int Array1[NMAX], Array2[NMAX];

	//УПОРЯДОЧЕННЫЙ ПО ВОЗРАСТАНИЮ МАССИВ
	cout << "Vvedite kol-vo elementov v massive vozrastanija ";
	cin >> N;

	//создаём упорядоченный по возрастанию массив из N элементов
	for (int i = 0; i < N; i++)
	{
		Array[i] = N * (-2) + rand() % 4 + 4 * i;
		Array1[i] = Array[i];
		Array2[i] = Array[i];
	}

	cout << "MASSIV PO VOZRASTANIJU:\n";
	for (int i = 0; i < N; i++)
		cout << Array[i] << " ";
	cout  << endl;

	cout << "Vvedite chislo, kotoroje Vy hotite vstavit' v massiv vozrastanija ";
	cin >> k;

	InputElement(Array, N, k);
	cout << "\nSTDCALL:\n";
	for (int i = 0; i < N+1; i++)
		cout << Array[i] << " ";
	cout << endl;

	InputElementCd(Array1, N, k);
	cout << "\nCDECL:\n";
	for (int i = 0; i < N + 1; i++)
		cout << Array1[i] << " ";
	cout << endl;

	InputElementFC(Array2, N, k);
	cout << "\nFASTCALL:\n";
	for (int i = 0; i < N + 1; i++)
		cout << Array2[i] << " ";
	cout << endl;


	//УПОРЯДОЧЕННЫЙ ПО УБЫВАНИЮ МАССИВ
	cout << "Vvedite kol-vo elementov v massive ubyvanija ";
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		Array[i] = 2 * N + rand() % 4 - 4 * i;
		Array1[i] = Array[i];
		Array2[i] = Array[i];
	}

	cout << "MASSIV PO UBYVANIJU:\n";
	for (int i = 0; i < N; i++)
		cout << Array[i] << " ";
	cout << endl;

	cout << "Vvedite chislo, kotoroje Vy hotite vstavit' v massiv ubyvanija ";
	cin >> k;

	InputElement(Array, N, k);
	cout << "\nSTDCALL:\n";
	for (int i = 0; i < N + 1; i++)
		cout << Array[i] << " ";
	cout << endl;

	InputElementCd(Array1, N, k);
	cout << "\nCDECL:\n";
	for (int i = 0; i < N + 1; i++)
		cout << Array1[i] << " ";
	cout << endl;

	InputElementFC(Array2, N, k);
	cout << "\nFASTCALL:\n";
	for (int i = 0; i < N + 1; i++)
		cout << Array2[i] << " ";
	cout << endl << endl;
	return 0;
}