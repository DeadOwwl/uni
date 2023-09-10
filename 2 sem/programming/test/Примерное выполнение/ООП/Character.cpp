#include "Character.h"
#pragma warning (disable: 4996)

int Character::NextID = 0;

string WriteRace(Race race)
{
	switch (race)
	{
	case human: return "Human";
	case gnom: return "Gnom";
	case elf: return "Elf";
	case orc: return "Orc";
	default: return "Error of initialization";
	}
}

string WriteGender(Gender gender)
{
	switch (gender)
	{
	case male: return "Male";
	case female: return "Female";
	default:return "Error of initialization";
	}
}

string WriteState(State state)
{
	switch (state)
	{
	case normal: return "Normal";
	case weak: return "Weak";
	case ill: return "Ill";
	case poisoned: return "Poisoned";
	case dead: return "Dead";
	}
}

Character::Character() : ID(++NextID), RaceC(human), GenderC(female), StateC(normal), Age(18), Health(50), MaxHealthC(100), ExperienceC(0) {};

void Character::Clone(const Character& C)
{
	StateC = C.StateC;
	Age = C.Age;
	Health = C.Health;
	MaxHealthC = C.MaxHealthC;
	ExperienceC = C.ExperienceC;
}

void Character::CheckState()
{
	if (Health < 0)
	{
		Health = 0;
		StateC = dead;
	}
	else
		if (StateC == normal && Health < MaxHealthC * 0.1)
			StateC = weak;
		else
			if (StateC == weak && Health >= MaxHealthC * 0.1)
				StateC = normal;
}

Character::Character(const char* name, const Race race, const Gender gender, const State state, const int age, const int health, const int maxhealth, const int exp) :
	ID(++NextID), RaceC(race), GenderC(gender), StateC(state), Age(age), Health(health), MaxHealthC(maxhealth), ExperienceC(exp)
{
	Name = new char[strlen(name) + 1];
	strcpy(const_cast<char*>(Name), name);
	if (this->Health > this->MaxHealthC || this->Health < 0)
		Health = MaxHealthC;
	CheckState();
}

Character::Character(const Character& C): ID(++NextID), RaceC(C.RaceC), GenderC(C.GenderC)
{
	Clone(C);
	Name = new char [strlen(C.Name) + 1];
	strcpy(const_cast<char*>(Name), C.Name);
}

void Character::SetHealth(int h)
{
	if (h > MaxHealthC)
		Health = MaxHealthC;
	else
		Health = h;
	CheckState();
}

void Character::SetMaxHealthC(int m)
{
	MaxHealthC = m;
	if (MaxHealthC < Health)
		Health = MaxHealthC;
	CheckState();
}

char* Character::GetName(char* name)
{
	strcpy(name, Name);
	return name;
}

Character& Character:: operator=(const Character& C)
{
	if (this == &C)
		return *this;
	Clone(C);
	return *this;
}

ostream& operator<<(ostream& O, Character& C)
{
	O << "ID: " << C.ID << endl;
	O << "Name: " << C.Name << endl;
	O << "Age: " << C.Age << endl;
	O << "Race: " << WriteRace(C.RaceC) << endl;
	O << "Gender: " << WriteGender(C.GenderC) << endl;
	O << "Health: " << C.Health << endl;
	O << "MaxHealth: " << C.MaxHealthC << endl;
	O << "Experience: " << C.ExperienceC << endl;
	O << "State: " << WriteState(C.StateC) << endl;
	return O;
}

Character::~Character()
{
	delete[] Name;
}

//____________________________________________________________________________

Mage::Mage() : Character(), Mana(0), MaxMana(0) {};

Mage::Mage(const char* name, const Race race, const Gender gender, const State state, const int age, const int health, const int maxhealth, const int exp, const int mana, const int maxmana) : 
   Character(name, race, gender, state, age, health, maxhealth, exp),
   MaxMana(maxmana) 
{
	if (mana > MaxMana)
		Mana = MaxMana;
	else
		Mana = mana;
};

Mage::Mage(const Mage& m): Character(m), Mana(m.Mana), MaxMana(m.MaxMana) {};

void Mage::SetMana(int m)
{
	if (m > MaxMana)
		Mana = MaxMana;
	else
		Mana = m;
}

void Mage::SetMaxMana(int m)
{
	MaxMana = m;
	if (Mana > MaxMana)
		Mana = MaxMana;
}

bool Mage::AddHealth(Character& C, int h)
{
	if (Mana < 2 * h)
		return false;
	if (C.GetHealth() + h > C.GetMaxHealthC())
		h = C.GetMaxHealthC() - C.GetHealth();
	C.SetHealth(C.GetHealth() + h);
	SetMana(Mana - 2 * h);
	return true;
}

ostream& operator<<(ostream& O, Mage& M)
{
	O << (Character&)M;
	O << "Mana: " << M.Mana << endl; 
	O << "MaxMana: " << M.MaxMana << endl;
	return O;
}

Mage& Mage:: operator=(const Mage& M)
{
	if (this == &M)
		return *this;
	Clone(M);
	Mana = M.Mana;
	MaxMana = M.MaxMana;
	return *this;
}