#include "Pokemon.h"
#include <iostream>
#include <ctime>

using namespace std;

//konstruktor för pokemon
Pokemon::Pokemon(const string& name, const Type type, const Move* move1,
	const Move* move2, const Move* move3, const Move* move4, int health,
	const int attack, const int spAttack, const int defense, const int spDefense, 
	int speed, const strategyFunc strategy, bool paralyzed)
	: name(name), type(type), move1(move1), move2(move2), move3(move3), move4(move4),
	health(health), attack(attack), spAttack(spAttack), defense(defense), spDefense(spDefense), speed(speed), strategy(strategy), paralyzed(paralyzed)
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

//constructor för dualtypepokemon
DualTypePokemon::DualTypePokemon(const string& name, const Type type1, const Type type2, const Move* move1,
	const Move* move2, const Move* move3, const Move* move4, int health, const int attack, const int spAttack, 
	const int defense, const int spDefense, int speed, const strategyFunc strategy, bool paralyzed)
	: Pokemon(name, type1, move1, move2, move3, move4, health, attack, spAttack, defense, spDefense, speed, strategy, paralyzed), type2(type2)
{
	if (type1 == type2) {
		throw exception("Types cannot be the same");
	}
}

// reducera health med damage
void Pokemon::reduceHealth(int damage) {
	health -= damage;
	if (health < 0)
		health = 0;
}

//sätter paralyzedstatus
void Pokemon::setParalyzed(bool status) {
	if (status == true) {
		paralyzed = true;
		speed = speed / 2;
	}
	else {
		paralyzed = false;
		speed = speed * 2;
	}
}

// returnera multiplicering för skada
float Pokemon::calculateDamageMultiplier(Type damagetype) {
	return TypeChart::getDamageMultiplier(damagetype, type);
}

// returnera multiplicering för skada för dualtypepokemon
float DualTypePokemon::calculateDamageMultiplier(Type damagetype) {
	float multiplier = TypeChart::getDamageMultiplier(damagetype, getType());
	float multiplier2 = TypeChart::getDamageMultiplier(damagetype, getType2());
	return multiplier * multiplier2;
}

//returnera ett move
const Move* Pokemon::getMove(int moveNumber) const {
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

// funktioner för att lägga till stats med hjälp av buildern
PokemonBuilder& PokemonBuilder::addType(Type type) {
	if (typeList.size() == 2)
		throw exception("Pokemon can only have two types");
	typeList.push_back(type);
	return *this;
}

PokemonBuilder& PokemonBuilder::addMove(const Move* move) {
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

//bygg pokemon med dessa stats
Pokemon* PokemonBuilder::build() {
	if (moveList.size() != 4)
		throw exception("Pokemon must have four moves");
	if (typeList.size() == 1) {
		return new Pokemon(name, typeList[0], moveList[0], moveList[1], moveList[2], moveList[3], health, attack, spAttack, defense, spDefense, speed, strategy, paralyzed);
	}
	else if (typeList.size() == 2) {
		return new DualTypePokemon(name, typeList[0], typeList[1], moveList[0], moveList[1], moveList[2], moveList[3], health, attack, spAttack, defense, spDefense, speed, strategy, paralyzed);
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
	else {								//om samma speed, random
		int random = rand() % 2;
		if (random == 0) {
			return pokemon1;
		}
		else {
			return pokemon2;
		}
	}
}

//starta battle
void Battle::start() {
	if (TeamAlpha.empty() || TeamBravo.empty())
		throw exception("Teams cant be empty.");
	cout << "Battle starting!" << endl << endl;
	cout << "Team Alpha sent out " << TeamAlpha.front()->getName() << "!" << endl;
	cout << "Team Bravo sent out " << TeamBravo.front()->getName() << "!" << endl;
	int indexA = 0;
	int indexB = 0;
	while (indexA < TeamAlpha.size() && indexB < TeamBravo.size()) {

		Pokemon* pokemonA = TeamAlpha[indexA];
		Pokemon* pokemonB = TeamBravo[indexB];

		cout << "----------------------------------------" << endl;
		cout << pokemonA->getName() << " health: " << pokemonA->getHealth() << endl;
		cout << pokemonB->getName() << " health: " << pokemonB->getHealth() << endl;

		Pokemon* fastest = getFastest(pokemonA, pokemonB);
		Pokemon* slowest = (fastest == pokemonA) ? pokemonB : pokemonA;

		//snabbare pokemonen attackerar
		const Move* firstMove = fastest->strategy(fastest, slowest);
		firstMove->perform(fastest, slowest);
		//kolla om försvarande pokemon blev fainted av attackerande pokemon
		if (slowest->getHealth() <= 0) {
			if (slowest == pokemonA) {
				indexA++;
				if (indexA < TeamAlpha.size())
					cout << "Team Alpha sent out " << TeamAlpha[indexA]->getName() << "!" << endl;
			}
			else if (slowest == pokemonB) {
				indexB++;
				if (indexB < TeamBravo.size())
					cout << "Team Bravo sent out " << TeamBravo[indexB]->getName() << "!" << endl;
			}
		}
		//kolla om attackerande pokemon blev fainted av egen skada
		if (fastest->getHealth() <= 0) {
			if (fastest == pokemonA) {
				indexA++;
				if (indexA < TeamAlpha.size())
					cout << "Team Alpha sent out " << TeamAlpha.front()->getName() << "!" << endl;
				continue;
			}
			else if (fastest == pokemonB) {
				indexB++;
				if (indexB < TeamBravo.size())
					cout << "Team Bravo sent out " << TeamBravo.front()->getName() << "!" << endl;
				continue;
			}
		}
		//hoppar över så att inte en fainted pokemon attackerar
		else if (slowest->getHealth() <= 0)
			continue;

		//sluta ifall något lag inte har några pokemon kvar
		if (indexA >= TeamAlpha.size() || indexB >= TeamBravo.size())
			break;

		//långsammare pokemonen attackerar
		const Move* secondMove = slowest->strategy(slowest, fastest);
		secondMove->perform(slowest, fastest);

		//kolla om försvarande pokemon blev fainted av attackerande pokemon
		if (fastest->getHealth() <= 0) {
			if (fastest == pokemonA) {
				indexA++;
				if (indexA < TeamAlpha.size())
					cout << "Team Alpha sent out " << TeamAlpha.front()->getName() << "!" << endl;
			}
			else if (fastest == pokemonB) {
				indexB++;
				if (indexB < TeamBravo.size())
					cout << "Team Bravo sent out " << TeamBravo.front()->getName() << "!" << endl;
			}
		}
		//kolla om attackerande pokemon blev fainted av egen skada
		if (slowest->getHealth() <= 0) {
			if (slowest == pokemonA) {
				indexA++;
				if (indexA < TeamAlpha.size())
					cout << "Team Alpha sent out " << TeamAlpha.front()->getName() << "!" << endl;
			}
			else if (slowest == pokemonB) {
				indexB++;
				if (indexB < TeamBravo.size())
					cout << "Team Bravo sent out " << TeamBravo.front()->getName() << "!" << endl;
			}
		}
	}
	cout << "----------------------------------------" << endl;
	if (indexB >= TeamBravo.size()) {
		cout << "Team Bravo ran out of usable Pokemon!" << endl << endl << "Team Alpha wins!" << endl;
		cout << "Team Alpha: ";
		for (auto pokemon : TeamAlpha)
			cout << pokemon->getName() << ": " << pokemon->getHealth() << " HP, ";
		cout << endl;
	}
	else {
		cout << "Team Alpha ran out of usable Pokemon!" << endl << endl << "Team Bravo wins!" << endl;
		cout << "Team Bravo: ";
		for (auto pokemon : TeamBravo)
			cout << pokemon->getName() << ": " << pokemon->getHealth() << " HP, ";
		
	}
	cout << endl << "----------------------------------------" << endl;
}