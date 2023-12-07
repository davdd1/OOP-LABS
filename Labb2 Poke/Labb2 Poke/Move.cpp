#include <iostream>
#include <string>
#include "Move.h"
#include "Pokemon.h"

using namespace std;

Move::Move(const string& name, const Type type, const int power)
	: type(type), name(name), power(power) {
	if (power < 0)
	{
		throw exception("Invalid move power.\n");
	}
	if (type < 0 || type > 16)
	{
		throw exception("Invalid move type.\n");
	}
}

void Move::perform(Pokemon* attacker, Pokemon* defender) const {
	if (defender->getHealth() > 0)
		execute(attacker, defender);
	else
		cout << defender->getName() << " is in a fainted state!" << endl;
}

PhysicalMove::PhysicalMove(const string& name, const Type type, const int power)
	: Move(name, type, power)
{
	cout << "Physical move created" << endl;
}

SpecialMove::SpecialMove(const string& name, const Type type, const int power)
	: Move(name, type, power)
{
	cout << "Special move created" << endl;
}

void PhysicalMove::execute(Pokemon* attacker, Pokemon* defender) const {
	defender->reduceHealth(power * (attacker->getAttack() / defender->getDefense())
		* defender->calculateDamageMultiplier(PhysicalMove::type));
	cout << endl << attacker->getName() << " used " << name << "!" << endl;
	effectiveness(defender->calculateDamageMultiplier(PhysicalMove::type));
	if (defender->health == 0)
	{
		cout << defender->name << " fainted!" << endl << endl;
	}
}


void SpecialMove::execute(Pokemon* attacker, Pokemon* defender) const {
	defender->reduceHealth(power * (attacker->getSpAttack() / defender->getSpDefense()) 
		* defender->calculateDamageMultiplier(SpecialMove::type));
	cout << endl << attacker->getName() << " used " << name << "!" << endl;
	effectiveness(defender->calculateDamageMultiplier(SpecialMove::type));
	if (defender->health == 0)
	{
		cout << defender->name << " fainted!" << endl << endl;
	}
}

// Skriver ut hur effektivt en attack blir är
void effectiveness(float multiplier) { 
	if (multiplier == 0)
		cout << "It had no effect!" << endl;
	else if (multiplier < 0.25)
		cout << "It's not very effective..." << endl;
	else if (multiplier < 0.5)
		cout << "It's not very effective..." << endl;
	else if (multiplier < 1.0)
		cout << "It's not very effective..." << endl;
	else if (multiplier < 1.5)
		cout << "";
	else if (multiplier >= 2.0)
		cout << "It's super effective!" << endl;
}

