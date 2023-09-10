#pragma once
#include <iostream>
#include <string>
using namespace std;

class FractExc : public exception {
private:
	string error;
public:
	FractExc(string err) : error(err) {};
	const string what() {
		return error;
	}
};