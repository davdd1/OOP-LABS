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
	if (attacker->isParalyzed() == true && rand() % 4 == 1)
	{
		cout << attacker->getName() << " is paralyzed and couldn't move!" << endl;
		return;
	}

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
	float baseDamage = 0.5 * (power * (static_cast<float>(attacker->getAttack()) / defender->getDefense()));
	float multiplier = defender->calculateDamageMultiplier(PhysicalMove::type);
	int damage = baseDamage * multiplier;
	defender->reduceHealth(damage);

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

	if (defender->getHealth() == 0)
		cout << defender->getName() << " fainted!" << endl << endl;
}

void SpecialMove::execute(Pokemon* attacker, Pokemon* defender) const {
	float baseDamage = 0.5 * (power * (static_cast<float>(attacker->getSpAttack()) / defender->getSpDefense()));
	float multiplier = defender->calculateDamageMultiplier(SpecialMove::type);
	int damage = baseDamage * multiplier;
	defender->reduceHealth(damage);

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

	if (defender->getHealth() == 0)
	{
		cout << defender->getName() << " fainted!" << endl << endl;
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
	int healing = power * 0.75;

	attacker->addHealth(healing);
	cout << endl << attacker->getName() << " used " << name << "!" << endl;
}

selfDestructMove::selfDestructMove(const string& name, const Type type, const int power)
	: Move(name, type, power)
{
}

void selfDestructMove::execute(Pokemon* attacker, Pokemon* defender) const {
	float baseDamage = 0.66 * (power * static_cast<float>(attacker->getAttack() / (defender->getDefense() / 1.5)));
	float multiplier = defender->calculateDamageMultiplier(selfDestructMove::type);
	int damage = baseDamage * multiplier;

	defender->reduceHealth(damage);
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


	if (defender->getHealth() == 0)
		cout << defender->getName() << " fainted!" << endl;

	attacker->setHealth(0);
	cout << attacker->getName() << " fainted from his own blast!" << endl << endl;
}

ParalyzingMove::ParalyzingMove(const string& name, const Type type, const int power)
	: Move(name, type, power)
{
}

//har const för att den ej ska ändra på Move-objektet
void ParalyzingMove::execute(Pokemon* attacker, Pokemon* defender) const {
	cout << endl << attacker->getName() << " used " << name << "!" << endl;

	if (defender->getHealth() == 0)
		cout << defender->getName() << " fainted!" << endl << endl;

	if (rand() % 10 < 9)			//90% chans att paralysera
	{
		defender->setParalyzed(true);
		cout << defender->getName() << " got paralyzed!" << endl;
	}
}