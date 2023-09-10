#include <iostream>
#include <string.h>
#pragma warning (disable: 4996)
using namespace std;

bool IsDigit(char* str) {
	char digit[11] = "0123456789";
	size_t a = strspn(str, digit);
	return a == strlen(str) ? true : false;
}

void Delete(char* p, size_t len) {
	int t = 0;
	while (*(p + len + t)) {
		*(p + t) = *(p + len + t);
		t++;
	}
	*(p + t) = '\0';
}

void Insert_m(char* s, int len, int len_str, const char* p) {
	for (int j = len_str + len + 1; j > len; j--) {
		*(s + j) = *(s + j - len - 1);
	}
	for (int j = 0; j < len; j++) {
		*(s + j) = *(p + j);
	}
	*(s + len) = ' ';
}

int main() {
	setlocale(LC_ALL, ".1251");
	const int max = 100;
	char* s = new char[max];
	char seps[2] = " ";
	cout << "Введите строку, состоящую из 2 слов и более, исключая пробелы перед первым и после последнего слов, по одному пробелу между словами: " << endl;
	cin.get(s, max);
	int p(0);
	char* a = new char[strlen(s) + 1];
	strcpy(a, s);
	char* token;
	token = strtok(a, seps);
	while (token) {
		if (IsDigit(token)) {
			p++;
		}
		token = strtok(NULL, seps);
	}
	if (p == 0) {
		cout << "Кажись Вы забыли про цифры:)" << endl;
		cout << s << endl;
		return 0;
	}
	for (int j = p; j > 0; --j) {
		char* a = new char[301];
		strcpy(a, s);
		token = strtok(a, seps);
		int k = 1;
		int l = -1;
		while (token) {
			if (IsDigit(token)) {
				if (k == p) {
					char* buf = new char[strlen(token + 1)];
					strcpy(buf, token);
					size_t tt = strlen(token);
					Delete((s + l), tt + 1);
					Insert_m(s, (int)tt, (int)strlen(s), buf);
				}
				k++;
			}
			l += strlen(token) + 1;
			token = strtok(NULL, seps);
		}
	}
	cout << s << endl;
	return 0;
}