#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#pragma warning (disable: 4996)

using namespace std;

ifstream Input("C:\\Users\\aowl2\\source\\repos\\������� ��  ��� � ���������\\in.txt");

void CheckFile()
{
	if (!Input.is_open())
		throw "������ �������� �����";
	if (Input.peek() == EOF)
		throw "���� ����";
}

// ��������� ������
enum Optype { power = 3, devide = 2, multiply = 2, min = 1, pl = 1, null = 0 }; // ���������� ��������

struct stack {
	char val[100]; // ��������������� �������� ��������
	Optype type; // ��������� ��������, ��������� ��� ����������� ������������  ������
	stack* next;
} *head;

// ������� ������ �� ������
void push(stack* t) {
	t->next = head;
	head = t;
}

void push(char str[], Optype type) {
	stack* t;
	t = new stack;
	strcpy(t->val, str);
	t->type = type;
	t->next = head;
	head = t;
}

stack* pop() {
	stack* t;
	if (head == NULL) return NULL;
	t = head;
	head = t->next;
	return t;
}

void fromRPN(char* input, char* output) {
	char c, temp[100];
	int p_temp = 0;
	stack* h1, * h2; // ���������� ��� �������� ������ ���� ��������� �����
	Optype type;
	head = NULL;
	while (*input) { // ���� ���� ������� ������
		c = (*input);
		if (c >= '0' && c <= '9' || c == '.') { //���� ������� ������ ����� �����
			temp[p_temp++] = c; //�� ��������� ��� �� ��������� ������
			temp[p_temp] = '\0';
		}
		else if (c == ' ') {
			if (p_temp != 0) {
				push(temp, null); // ��������� ����� � ����
				p_temp = 0;
			}
			temp[0] = '\0'; // ���������� ��������� ������
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') { //���� ������ ���� ��������
			h1 = pop(); // ����������� ������ �������
			h2 = pop(); // ����������� ������ �������
						// ������� ��������� ��������
			if (c == '+') type = pl;
			else if (c == '-') type = min;
			else if (c == '*') type = multiply;
			else if (c == '/') type = devide;
			else if (c == '^') type = power;
			if (h2->type != null && h2->type < type) { // ���� ��������� ��� 1-�� �������� ������
				temp[0] = '('; temp[1] = '\0'; // ����� ��������� � ������
				h2->val[strlen(h2->val) + 2] = '\0';
				h2->val[strlen(h2->val) + 1] = c; // ����������� ���� ��������
				h2->val[strlen(h2->val)] = ')';
			}
			else {
				h2->val[strlen(h2->val) + 1] = '\0';
				h2->val[strlen(h2->val)] = c;
			}
			strcat(temp, h2->val);
			if (h1->type != null && h1->type < type) {  // ���� ��������� ��� 2-�� �������� ������
				strcat(temp, "(");
				h1->val[strlen(h1->val) + 1] = '\0';
				h1->val[strlen(h1->val)] = ')'; // ����� ��������� � ������
			}
			strcat(temp, h1->val);
			strcpy(h2->val, temp); // ��� �� �� �������� ������ ��� ����� �������, �������� ���������� ��������� �� ������ �������
			delete h1; // ������� ������ �������
			h2->type = type; // ������������� ����� ��������� ��������
			push(h2); // ��������� ����� ������� � ����
		}
		input++;
	}
	strcpy(output, (pop())->val); // �������� ��������� �� ������� ����� � ������ ����������
}

int main() {
	try {
		setlocale(LC_ALL, ".1251");
		char infix[100], postfix[100]; // ������� � �������� ������
		Input.getline(infix, 255);
		fromRPN(infix, postfix);
		cout<<postfix;
	}
	catch (const char* Error) {
		cout << Error;
		return 0;
	}
	system("PAUSE");
	return 0;
}