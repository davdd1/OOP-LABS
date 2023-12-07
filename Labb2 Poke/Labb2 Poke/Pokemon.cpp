#include "Pokemon.h"
#include <iostream>

using namespace std;

Pokemon::Pokemon(const string& name, const Type type, const Move* move1,
	const Move* move2, const Move* move3, const Move* move4, const int health,
	const int attack, const int spAttack, const int defense, const int spDefense)
	: name(name), type(type), move1(move1), move2(move2), move3(move3), move4(move4),
	health(health), attack(attack), spAttack(spAttack), defense(defense), spDefense(spDefense)
{
	if (name.empty()) {
		throw exception("Name cannot be empty");
	}
	if (health <= 0) {
		throw exception("Health cannot be less than or equal to 0");
	}
	if (attack <= 0) {
		throw exception("Attack cannot be less than or equal to 0");
	}
	if (spAttack <= 0) {
		throw exception("Special attack cannot be less than or equal to 0");
	}
	if (defense <= 0) {
		throw exception("Defense cannot be less than or equal to 0");
	}
	if (spDefense <= 0) {
		throw exception("Special defense cannot be less than or equal to 0");
	}
	if (move1 == nullptr || move2 == nullptr || move3 == nullptr || move4 == nullptr) {
		throw exception("Moves cannot be null");
	}
}

// köra moves
void Pokemon::executeMove1(Pokemon* target) {
	if (target->health <= 0) {
		cout << name << " tried to use " << move1->getName() << " but it failed." << endl;
		cout << target->name << " has already fainted." << endl << endl;
		return;
	}
	else if (health <= 0) {
		cout << name << " tried to use " << move1->getName() << " but it failed." << endl;
		cout << name << " has fainted." << endl << endl;
		return;
	}
	move1->perform(this, target);
}

void Pokemon::executeMove2(Pokemon* target) {
	if (target->health <= 0) {
		cout << name << " tried to use " << move2->getName() << " but it failed." << endl;
		cout << target->name << " has already fainted." << endl << endl;
		return;
	}
	else if (health <= 0) {
		cout << name << " tried to use " << move2->getName() << " but it failed." << endl;
		cout << name << " has fainted." << endl << endl;
		return;
	}
	move2->perform(this, target);
}

void Pokemon::executeMove3(Pokemon* target) {
	if (target->health <= 0) {
		cout << name << " tried to use " << move3->getName() << " but it failed." << endl;
		cout << target->name << " has already fainted." << endl << endl;
		return;
	}
	else if (health <= 0) {
		cout << name << " tried to use " << move3->getName() << " but it failed." << endl;
		cout << name << " has fainted." << endl << endl;
		return;
	}
	move3->perform(this, target);
}

void Pokemon::executeMove4(Pokemon* target) {
	if (target->health <= 0) {
		cout << name << " tried to use " << move4->getName() << " but it failed." << endl;
		cout << target->name << " has already fainted." << endl << endl;
		return;
	}
	else if (health <= 0) {
		cout << name << " tried to use " << move4->getName() << " but it failed." << endl;
		cout << name << " has fainted." << endl << endl;
		return;
	}
	move4->perform(this, target);
}

// reducera health med damage
void Pokemon::reduceHealth(int damage) {
	health -= damage;
	if (health < 0)
		health = 0;
}

// returnera multiplicering för skada
float Pokemon::calculateDamageMultiplier(Type damagetype) {
	return TypeChart::getDamageMultiplier(damagetype, type);
}