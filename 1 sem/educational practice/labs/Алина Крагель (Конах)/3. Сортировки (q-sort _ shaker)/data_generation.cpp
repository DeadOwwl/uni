#include <stdlib.h> 
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>
#pragma warning(disable:4996)

using namespace std;
extern long int s, p, search_time_1, search_time_2;
void kostyl(int*, int*, int);

void InputKey(void) {
	int length;
	ofstream input;
	ofstream output;
	input.open("C:\\Users\\aowl2\\source\\repos\\������������-������� ��\\input.txt");
	output.open("C:\\Users\\aowl2\\source\\repos\\������������-������� ��\\output.txt");
	cout << "������� ������ �������: ";
	cin >> length;
	int* arr = new int[length + 1];
	cout << "������� �������� �������: ";
	input << "�������������� ������: ";
	for (int i = 0; i < length; i++) {
		cin >> arr[i];
		input << arr[i] << " ";
	}
	int* a_shaker = new int[length + 1];
	int* a_qsort = new int[length + 1];
	for (int i = 0; i < length; i++)
		a_shaker[i] = arr[i];
	for (int i = 0; i < length; i++)
		a_qsort[i] = arr[i];
	kostyl(a_shaker, a_qsort, length);
	output << "����� ��������� ����������: \n";
	for (int i = 0; i < length; i++)
		output << a_shaker[i] << " ";
	output << endl << "����� ��c���� ����������: \n";
	for (int i = 0; i < length; i++)
		output << a_qsort[i] << " ";
	input.close();
	output.close();
	delete[] arr;
	delete[] a_shaker;
	delete[] a_qsort;
}

void RandGen(void) {
	srand(time(NULL));
	int a, b, length, bottom;
	ofstream input;
	ofstream output;
	input.open("D:\\alink\\bsu\\1 s\\sp\\������������-������� ��\\input.txt");
	output.open("D:\\alink\\bsu\\1 s\\sp\\������������-������� ��\\output.txt");
	cout << "������� ������ �������: ";
	cin >> length;

	int* arr = new int[length + 1];
	cout << "����� ������ ��������� �������, ��� 1 - �� �����������, 2 - �� ��������, 3 - ���������� �������: ";
	cin >> bottom;
	input << "�������������� ������: ";
	if (bottom == 1) for (int i = 0; i < length; i++) {
		arr[i] = i + 1;
		input << arr[i] << " ";
	}
	if (bottom == 2) for (int i = 0; i < length; i++) {
		arr[i] = length - i;
		input << arr[i] << " ";
	}
	if (bottom == 3) {
		cout << "������� �������� (�� ... �� ...): ";
		cin >> a >> b;
		if (a > b) swap(a, b);
		for (int i = 0; i < length; i++) {
			arr[i] = rand() % (b - a + 1) + a;
			input << arr[i] << " ";
		}
	}
	if (bottom != 1 && bottom != 2 && bottom != 3) {
		cout << "������� ���������� ��������. ";
		return;
	}
	int* a_shaker = new int[length + 1];
	int* a_qsort = new int[length + 1];
	for (int i = 0; i < length; i++)
		a_shaker[i] = arr[i];
	for (int i = 0; i < length; i++)
		a_qsort[i] = arr[i];
	kostyl(a_shaker, a_qsort, length);
	output << "����� ��������� ����������: \n";
	for (int i = 0; i < length; i++)
		output << a_shaker[i] << " ";
	output << endl << "����� ��c���� ����������: \n";
	for (int i = 0; i < length; i++)
		output << a_qsort[i] << " ";
	input.close();
	output.close();
	delete[] arr;
	delete[] a_shaker;
	delete[] a_qsort;
}

void FileGen(void) {
	int i = 0, length = 0, pos = 0, nach = 0, kon = 0;
	string str, slovo;
	ifstream input;
	ofstream output;
	input.open("C:\\Users\\aowl2\\source\\repos\\������������-������� ��\\input.txt");
	output.open("C:\\Users\\aowl2\\source\\repos\\������������-������� ��\\output.txt");
	if (input.is_open()) {
		getline(input, str);
		while (str.find_first_of(' ', pos) != 0 && pos != -1) {
			pos = str.find_first_of(' ', pos + 1);
			length += 1;
		}
		int* arr = new int[length + 1];
		char* s = new char[length + 1];
		while ((nach = str.find_first_not_of(" ", nach)) != -1) {
			kon = str.find_first_of(" ", nach);
			slovo = str.substr(nach, kon - nach);
			strcpy(s, slovo.c_str());
			arr[i] = atoi(s);
			strcpy(s, "");
			i++;
			nach = kon;
		}
		int* a_shaker = new int[length + 1];
		int* a_qsort = new int[length + 1];
		for (int i = 0; i < length; i++)
			a_shaker[i] = arr[i];
		for (int i = 0; i < length; i++)
			a_qsort[i] = arr[i];
		kostyl(a_shaker, a_qsort, length);
		output << "����� ��������� ����������: \n";
		for (int i = 0; i < length; i++)
			output << a_shaker[i] << " ";
		output << endl << "����� ������� ����������: \n";
		for (int i = 0; i < length; i++)
			output << a_qsort[i] << " ";
		input.close();
		output.close();
		delete[] s;
		delete[] arr;
		delete[] a_shaker;
		delete[] a_qsort;
	}
	else
		cout << "������ ��������" << std::endl;
}