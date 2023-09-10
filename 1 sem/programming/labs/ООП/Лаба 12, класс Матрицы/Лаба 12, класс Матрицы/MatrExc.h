#pragma once
#include <iostream>
#include <string>

using namespace std;

class MatrExc :public exception {
private:
	string error;
public:
	MatrExc(string err) :error(err) {};
	const string what() {
		return error;
	}
};
