#include<stdlib.h> 
#include<stdio.h>
#include<iostream>
#include <ratio>
#include <chrono>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>
#include "Header.h"
#pragma warning(disable:4996)
using namespace std;
extern long int p = 0, s = 0, search_time_1 = 0, search_time_2 = 0;

void kostyl(int* a_shaker, int* a_qsort, int n) {
	unsigned int start_time_1 = clock();
	shaker(a_shaker, n);
	unsigned int end_time_1 = clock();
	unsigned int search_time_1 = end_time_1 - start_time_1;
	cout << "��������� ����������: " << endl << "\t ���������: " << s << endl << "\t �����������: " << p << endl << "\t ����� ����������: " << search_time_1 << " ��" << endl;
	s = 0;
	p = 0;
	unsigned int start_time_2 = clock();
	q_sort(a_qsort, 0, n - 1);
	unsigned int end_time_2 = clock();
	unsigned int search_time_2 = end_time_2 - start_time_2;
	cout << "������� ����������: " << endl << "\t ���������: " << s << endl << "\t �����������: " << p << endl << "\t ����� ����������: " << search_time_2 << " ��" << endl;
}

void main()
{
	setlocale(0, "");
	int n = 0, bottom;
	cout << "����� ������ ��������� �������, ��� 1 - � ����������, 2 - �������������, 3 - �� �����: ";
	cin >> bottom;

	if (bottom == 1)
		InputKey();
	if (bottom == 2)
		RandGen();
	if (bottom == 3)
		FileGen();
	if (bottom != 1 && bottom != 2 && bottom != 3) cout << "��������� �������� �����������. ����������� ��������������� �������� ������ ����� � ��������� ��������� ������." << endl;
	system("pause");
}