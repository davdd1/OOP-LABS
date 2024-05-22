#include <iostream>
#include <string>
#include <stdexcept>
#include "Move.h"
#include "Pokemon.h"

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

using namespace std;

Move::Move(const string& name, const Type type, const int power)
	: type(type), name(name), power(power) {
	if (power < 0)
	{
		throw runtime_error("Invalid move power.\n");
	}
	if (type < 0 || type > 16)
	{
		throw runtime_error("Invalid move type.\n");
	}
}

void Move::perform(Pokemon* attacker, Pokemon* defender) const {
	if (attacker->isParalyzed() == true && rand() % 4 == 1)
	{
		cout << RED << attacker->getName() << " is paralyzed and couldn't move!" << RESET << endl;
		return;
	}

	if (defender->getHealth() > 0)
		execute(attacker, defender);
	else
		cout << RED << defender->getName() << " is in a fainted state!" << RESET << endl;
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

	cout << endl << attacker->getTeamColor() << attacker->getName() << RESET << " used " << BLUE << name << RESET << "!" << endl;

	if (multiplier == 0)
		cout << YELLOW << "It had no effect!" << RESET << endl;
	else if (multiplier < 0.25)
		cout << YELLOW << "It's not very effective..." << RESET << endl;
	else if (multiplier < 0.5)
		cout << YELLOW << "It's not very effective..." << RESET << endl;
	else if (multiplier < 1.0)
		cout << YELLOW << "It's not very effective..." << RESET << endl;
	else if (multiplier < 1.5)
		cout << "";
	else if (multiplier >= 2.0)
		cout << GREEN << "It's super effective!" << RESET << endl;

	if (defender->getHealth() == 0)
		cout << RED << defender->getTeamColor() << defender->getName() << RESET << " fainted!" << RESET << endl << endl;
}

void SpecialMove::execute(Pokemon* attacker, Pokemon* defender) const {
	float baseDamage = 0.5 * (power * (static_cast<float>(attacker->getSpAttack()) / defender->getSpDefense()));
	float multiplier = defender->calculateDamageMultiplier(SpecialMove::type);
	int damage = baseDamage * multiplier;
	defender->reduceHealth(damage);

	cout << endl << attacker->getTeamColor() << attacker->getName() << RESET << " used " << BLUE << name << RESET << "!" << endl;

	if (multiplier == 0)
		cout << YELLOW << "It had no effect!" << RESET << endl;
	else if (multiplier < 0.25)
		cout << YELLOW << "It's not very effective..." << RESET << endl;
	else if (multiplier < 0.5)
		cout << YELLOW << "It's not very effective..." << RESET << endl;
	else if (multiplier < 1.0)
		cout << YELLOW << "It's not very effective..." << RESET << endl;
	else if (multiplier < 1.5)
		cout << "";
	else if (multiplier >= 2.0)
		cout << GREEN << "It's super effective!" << RESET << endl;

	if (defender->getHealth() == 0)
	{
		cout << RED << defender->getTeamColor() << defender->getName() << RESET << " fainted!" << RESET << endl << endl;
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
	cout << endl << attacker->getTeamColor() << attacker->getName() << RESET << " used " << BLUE << name << RESET << "!" << endl;
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
	cout << endl << attacker->getTeamColor() << attacker->getName() << RESET << " used " << BLUE << name << RESET << "!" << endl;

	if (multiplier == 0)
		cout << YELLOW << "It had no effect!" << RESET << endl;
	else if (multiplier < 0.25)
		cout << YELLOW << "It's not very effective..." << RESET << endl;
	else if (multiplier < 0.5)
		cout << YELLOW << "It's not very effective..." << RESET << endl;
	else if (multiplier < 1.0)
		cout << YELLOW << "It's not very effective..." << RESET << endl;
	else if (multiplier < 1.5)
		cout << "";
	else if (multiplier >= 2.0)
		cout << GREEN << "It's super effective!" << RESET << endl;


	if (defender->getHealth() == 0)
		cout << RED << defender->getTeamColor() << defender->getName() << RESET << " fainted!" << RESET << endl;

	attacker->setHealth(0);
	cout << RED << attacker->getTeamColor() << attacker->getName() << RESET << " fainted from his own blast!" << RESET << endl << endl;
}

ParalyzingMove::ParalyzingMove(const string& name, const Type type, const int power)
	: Move(name, type, power)
{
}

//har const för att den ej ska ändra på Move-objektet
void ParalyzingMove::execute(Pokemon* attacker, Pokemon* defender) const {
	cout << endl << attacker->getTeamColor() << attacker->getName() << RESET << " used " << BLUE << name << RESET << "!" << endl;

	if (defender->getHealth() == 0)
		cout << RED << defender->getTeamColor() << defender->getName() << RESET << " fainted!" << RESET << endl << endl;

	if (rand() % 10 < 9)            //90% chans att paralysera
	{
		defender->setParalyzed(true);
		cout << defender->getName() << " got paralyzed!" << endl;
	}
}