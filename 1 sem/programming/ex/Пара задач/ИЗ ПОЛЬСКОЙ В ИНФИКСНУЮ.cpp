#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#pragma warning (disable: 4996)

using namespace std;

ifstream Input("C:\\Users\\aowl2\\source\\repos\\ААААААА из  ПИЗ в инфиксную\\in.txt");

void CheckFile()
{
	if (!Input.is_open())
		throw "Ошибка открытия файла";
	if (Input.peek() == EOF)
		throw "Файл пуст";
}

// Структуры данных
enum Optype { power = 3, devide = 2, multiply = 2, min = 1, pl = 1, null = 0 }; // приоритеты операций

struct stack {
	char val[100]; // непосредственно значение элемента
	Optype type; // приоритет операции, необходим для правильного расставления  скобок
	stack* next;
} *head;

// Функции работы со стеком
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
	stack* h1, * h2; // переменные для хранения первых двух элементов стека
	Optype type;
	head = NULL;
	while (*input) { // пока есть символы строке
		c = (*input);
		if (c >= '0' && c <= '9' || c == '.') { //если текущий символ часть числа
			temp[p_temp++] = c; //то добавляем его во временную строку
			temp[p_temp] = '\0';
		}
		else if (c == ' ') {
			if (p_temp != 0) {
				push(temp, null); // добавляем число в стек
				p_temp = 0;
			}
			temp[0] = '\0'; // опустошаем временную строку
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') { //если читаем знак операции
			h1 = pop(); // выталкиваем первый элемент
			h2 = pop(); // выталкиваем второй элемент
						// находим приоритет операции
			if (c == '+') type = pl;
			else if (c == '-') type = min;
			else if (c == '*') type = multiply;
			else if (c == '/') type = devide;
			else if (c == '^') type = power;
			if (h2->type != null && h2->type < type) { // если приоритет для 1-го элемента меньше
				temp[0] = '('; temp[1] = '\0'; // берем выражение в скобки
				h2->val[strlen(h2->val) + 2] = '\0';
				h2->val[strlen(h2->val) + 1] = c; // приписываем знак операции
				h2->val[strlen(h2->val)] = ')';
			}
			else {
				h2->val[strlen(h2->val) + 1] = '\0';
				h2->val[strlen(h2->val)] = c;
			}
			strcat(temp, h2->val);
			if (h1->type != null && h1->type < type) {  // если приоритет для 2-го элемента меньше
				strcat(temp, "(");
				h1->val[strlen(h1->val) + 1] = '\0';
				h1->val[strlen(h1->val)] = ')'; // берем выражение в скобки
			}
			strcat(temp, h1->val);
			strcpy(h2->val, temp); // что бы не выделять память под новый элемент, копируем полученное выражение во второй элемент
			delete h1; // удаляем первый элемент
			h2->type = type; // устанавливаем новый приоритет операции
			push(h2); // добавляем новый элемент в стек
		}
		input++;
	}
	strcpy(output, (pop())->val); // копируем выражение из вершины стека в строку результата
}

int main() {
	try {
		setlocale(LC_ALL, ".1251");
		char infix[100], postfix[100]; // входная и выходная строка
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