#ifndef __Character_defined__
#define __Character_defined__

#include <cstring>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

enum Race { human, gnom, elf, orc };
string WriteRace(Race race);

enum Gender { male, female };
string WriteGender(Gender gender);

enum State { normal, weak, ill, poisoned, dead };
string WriteState(State state);

class Character
{
private:
	const int ID;
	const char* Name;
	const Race RaceC;
	const Gender GenderC;
	State StateC;
	int Age;
	int Health;
	int MaxHealthC;
	int ExperienceC;
protected:
	Character();
	void Clone(const Character& c);
	static int NextID;
	void CheckState();
public:
	Character(const char* name, const Race race, const Gender gender, const State state, const int age, const int health, const int maxhealth, const int exp);
	explicit Character(const Character& c);
	void SetStateC(State s) { StateC = s; }
	void SetAge(int a) { Age = a; }
	void SetHealth(int h);
	void SetMaxHealthC(int m);
	void SetExperience(int e) { ExperienceC = e; }
	int GetID() const { return ID; }
	char* GetName(char* name);
	Race GetRaceC() const { return RaceC; }
	Gender GetGenderC() const { return GenderC; }
	State GetStateC() const { return StateC; }
	int GetAge() const { return Age; }
	int GetHealth() const { return Health; }
	int GetMaxHealthC() const { return MaxHealthC; }
	int GetExperience() const { return ExperienceC; }
	friend ostream& operator<<(ostream& O, Character& C);
	virtual ~Character();
	virtual Character& operator=(const Character& C);
};

class Mage : public Character
{
private:
	int Mana;
	int MaxMana;
	Mage();
public:
	Mage(const char* name, const Race race, const Gender gender, const State state, const int age, const int health, const int maxhealth, const int exp, const int mana, const int maxmana);
	explicit Mage(const Mage& m);
	void SetMana(int m);
	void SetMaxMana(int m);
	int GetMana() const { return Mana; }
	int GetMaxMana() const { return MaxMana; }
	bool AddHealth(Character& c, int h);
	friend ostream& operator<<(ostream& o, Mage& M);
	virtual Mage& operator=(const Mage& M);
};

#endif
