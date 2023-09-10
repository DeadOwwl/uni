#ifndef __Persons_defined__
#define __Persons_defined__

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

class Person
{
private:
	char* Name;
	const int ID;
	static int next_ID;
public:
	Person(const char* name = "Имя не указакано.");
	virtual ~Person();
	void SetName(const char* n);
	char* GetName(char* name) const;
	virtual void Print() const;
	virtual int GetID() { return ID; }
};

class Student : public Person
{
private:
	int Course;
	int Group;
public:
	Student(const char*, const int, const int);
	void SetCourse(const int cr){ Course = cr; }
	int GetCourse() const { return Course; }
	void SetGroup(const int gr) { Group = gr;}
	int GetGroup()const { return Group; }
	void Print() const;
};

class Professor : public Person
{
private:
	char* Caf;
public:
	Professor(const char*, const char*);
	~Professor();
	void SetCaf(const char* c);
	char* GetCaf(char* c) const;
	void Print() const;
};

#endif

