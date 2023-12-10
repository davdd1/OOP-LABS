#include "Pokemon.h"
#include <iostream>
#include <ctime>

using namespace std;

Pokemon::Pokemon(string& name, Type type, Move* move1,
	Move* move2, Move* move3, Move* move4, int health,
	int attack, int spAttack, int defense, int spDefense, int speed, strategyFunc strategy)
	: name(name), type(type), move1(move1), move2(move2), move3(move3), move4(move4),
	health(health), attack(attack), spAttack(spAttack), defense(defense), spDefense(spDefense), speed(speed), strategy(strategy)
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
	if (speed <= 0) {
		throw exception("Speed cannot be less than or equal to 0");
	}
	if (move1 == nullptr || move2 == nullptr || move3 == nullptr || move4 == nullptr) {
		throw exception("Moves cannot be null");
	}
}

DualTypePokemon::DualTypePokemon(string& name, Type type1, Type type2, Move* move1,
	Move* move2, Move* move3, Move* move4, int health,
	int attack, int spAttack, int defense, int spDefense, int speed, strategyFunc strategy)
	: Pokemon(name, type1, move1, move2, move3, move4, health, attack, spAttack, defense, spDefense, speed, strategy), type2(type2)
{
	if (type1 == type2) {
		throw exception("Types cannot be the same");
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
//ska funka för dualtypepokemon
float Pokemon::calculateDamageMultiplier(Type damagetype) {
	return TypeChart::getDamageMultiplier(damagetype, type);
}



float DualTypePokemon::calculateDamageMultiplier(Type damagetype) {
	float multiplier = TypeChart::getDamageMultiplier(damagetype, type);
	float multiplier2 = TypeChart::getDamageMultiplier(damagetype, type2);
	return multiplier * multiplier2;
}

//returnera ett move
Move* Pokemon::getMove(int moveNumber) {
	switch (moveNumber)
	{
	case 1:
		return move1;
		break;
	case 2:
		return move2;
		break;
	case 3:
		return move3;
		break;
	case 4:
		return move4;
		break;
	default:
		throw exception("Move does not exist.");
		break;
	}
}

// lambdafunktion för att hitta bästa move


PokemonBuilder& PokemonBuilder::addType(Type type) {
	if (typeList.size() == 2)
		throw exception("Pokemon can only have two types");
	typeList.push_back(type);
	return *this;
}

PokemonBuilder& PokemonBuilder::addMove(Move* move) {
	if (moveList.size() == 4)
		throw exception("Pokemon can only have four moves");
	moveList.push_back(move);
	return *this;
}

PokemonBuilder& PokemonBuilder::setName(string name) {
	this->name = name;
	return *this;
}

PokemonBuilder& PokemonBuilder::setHealth(int health) {
	this->health = health;
	return *this;
}

PokemonBuilder& PokemonBuilder::setAttack(int attack) {
	this->attack = attack;
	return *this;
}

PokemonBuilder& PokemonBuilder::setSpAttack(int spAttack) {
	this->spAttack = spAttack;
	return *this;
}

PokemonBuilder& PokemonBuilder::setDefense(int defense) {
	this->defense = defense;
	return *this;
}

PokemonBuilder& PokemonBuilder::setSpDefense(int spDefense) {
	this->spDefense = spDefense;
	return *this;
}


PokemonBuilder& PokemonBuilder::setBothAttacks(int attack) {
	this->attack = attack;
	this->spAttack = attack;
	return *this;
}

PokemonBuilder& PokemonBuilder::setBothDefenses(int defense) {
	this->defense = defense;
	this->spDefense = defense;
	return *this;
}

PokemonBuilder& PokemonBuilder::setSpeed(int speed) {
	this->speed = speed;
	return *this;
}

PokemonBuilder& PokemonBuilder::setStrategy(strategyFunc strategy) {
	this->strategy = strategy;
	return *this;
}

Pokemon* PokemonBuilder::build() {
	if (typeList.size() == 1) {
		return new Pokemon(name, typeList[0], moveList[0], moveList[1], moveList[2], moveList[3], health, attack, spAttack, defense, spDefense, speed, strategy);
	}
	else if (typeList.size() == 2) {
		return new DualTypePokemon(name, typeList[0], typeList[1], moveList[0], moveList[1], moveList[2], moveList[3], health, attack, spAttack, defense, spDefense, speed, strategy);
	}
	else {
		throw exception("Pokemon must have at least one type");
	}
}

Battle& Battle::addPokemonToA(Pokemon* pokemon) {
	if (TeamAlpha.size() == 6)
		throw exception("Team A can only have six pokemon");
	TeamAlpha.push_back(pokemon);
	return *this;
}

Battle& Battle::addPokemonToB(Pokemon* pokemon) {
	if (TeamBravo.size() == 6)
		throw exception("Team B can only have six pokemon");
	TeamBravo.push_back(pokemon);
	return *this;
}

//hitta snabbaste av två pokemon
Pokemon* getFastest(Pokemon* pokemon1, Pokemon* pokemon2) {
	if (pokemon1->getSpeed() > pokemon2->getSpeed()) {
		return pokemon1;
	}
	else if (pokemon1->getSpeed() < pokemon2->getSpeed()) {
		return pokemon2;
	}
	else {
		int random = rand() % 2;
		if (random == 0) {
			return pokemon1;
		}
		else {
			return pokemon2;
		}
	}
}

void Battle::start() {
	while (TeamAlpha.size() > 0 && TeamBravo.size() > 0) {
		Pokemon* pokemonA = TeamAlpha.front();
		Pokemon* pokemonB = TeamBravo.front();

		Pokemon* fastest = getFastest(pokemonA, pokemonB);
		Pokemon* slowest = (fastest == pokemonA) ? pokemonB : pokemonA;

		Move* move = fastest->strategy(fastest, slowest);

		move->perform(fastest, slowest);
		if (slowest->health <= 0) {
			if (slowest == pokemonA) {
				TeamAlpha.erase(TeamAlpha.begin());
			}
			else if (slowest == pokemonB) {
				TeamBravo.erase(TeamBravo.begin());	
			}
		}
		move->perform(slowest, fastest);
		if (fastest->health <= 0) {
			if (fastest == pokemonA) {
				TeamAlpha.erase(TeamAlpha.begin());
			}
			else if (fastest == pokemonB) {
				TeamBravo.erase(TeamBravo.begin());
			}
		}

	}
	if (TeamBravo.size() == 0)
		cout << "Team A wins!" << endl;
	else
		cout << "Team B wins!" << endl;
}

void addHealth(Pokemon* pokemon, int health) {
	pokemon->health += health;
	if (pokemon->health > 100)
		pokemon->health = 100;
}
