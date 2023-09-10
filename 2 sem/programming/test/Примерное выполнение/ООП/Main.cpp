#include "Character.h"

int main()
{
	setlocale(0, "");
	Character Witch("Owwl", elf, female, normal, 17, 99, 100, 1000);
	cout << Witch;
	Character W(Witch);
	cout << W;
	Mage WitchMage("Greatest Owwl", elf, female, normal, 17, 99, 100, 1000, 580, 550);
	cout << WitchMage;
	Mage WR(WitchMage);
	cout << WR;
	return 0;
}