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
}

SpecialMove::SpecialMove(const string& name, const Type type, const int power)
	: Move(name, type, power)
{
}

void PhysicalMove::execute(Pokemon* attacker, Pokemon* defender) const {
	float baseDamage = power * (float)(attacker->getAttack() / defender->getDefense());
	float multiplier = defender->calculateDamageMultiplier(PhysicalMove::type);
	float damage = baseDamage * multiplier;

	cout << endl << attacker->getName() << " used " << name << "!" << endl;

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

	defender->reduceHealth(damage);

	if (defender->health == 0)
	{
		cout << defender->name << " fainted!" << endl << endl;
	}
}

void SpecialMove::execute(Pokemon* attacker, Pokemon* defender) const {
	float baseDamage = power * (float)(attacker->getSpAttack() / defender->getSpDefense());
	float multiplier = defender->calculateDamageMultiplier(SpecialMove::type);
	float damage = baseDamage * multiplier;

	cout << endl << attacker->getName() << " used " << name << "!" << endl;

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

	defender->reduceHealth(damage);

	if (defender->health == 0)
	{
		cout << defender->name << " fainted!" << endl << endl;
	}
}

void Pokemon::addHealth(int healing) {
		health += healing;
}

HealingMove::HealingMove(const string& name, const Type type, const int power)
	: Move(name, type, power)
{
}

void HealingMove::execute(Pokemon* attacker, Pokemon* defender) const {
	float baseHealing = power * (float)(attacker->getSpAttack() / defender->getSpDefense());
	int healing = baseHealing;

	cout << endl << attacker->getName() << " used " << name << "!" << endl;

	attacker->addHealth(healing);
}

selfDestructMove::selfDestructMove(const string& name, const Type type, const int power)
	: Move(name, type, power)
{
}

void selfDestructMove::execute(Pokemon* attacker, Pokemon* defender) const {
	float baseDamage = power * (float)(attacker->getAttack() / defender->getDefense());
	float multiplier = defender->calculateDamageMultiplier(selfDestructMove::type);
	float damage = baseDamage * multiplier;

	cout << endl << attacker->getName() << " used " << name << "!" << endl;

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

	defender->reduceHealth(damage);

	if (defender->health == 0)
	{
		cout << defender->name << " fainted!" << endl << endl;
	}

	attacker->reduceHealth(1000);
}



