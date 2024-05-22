#include "Pokemon.h"
#include <iostream>
#include <ctime>
#include <stdexcept>

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define ORANGE "\033[38;5;208m"

#define RAINBOW1 "\033[38;5;196m"
#define RAINBOW2 "\033[38;5;202m"
#define RAINBOW3 "\033[38;5;220m"
#define RAINBOW4 "\033[38;5;118m"
#define RAINBOW5 "\033[38;5;45m"
#define RAINBOW6 "\033[38;5;129m"

using namespace std;

void printRainbowDivider() {
    cout << RAINBOW1 << "----" << RAINBOW2 << "----" << RAINBOW3 << "----" << RAINBOW4 << "----" << RAINBOW5 << "----" << RAINBOW6 << "----" << RESET << endl;
}

//konstruktor f�r pokemon
Pokemon::Pokemon(const string& name, const Type type, const Move* move1,
	const Move* move2, const Move* move3, const Move* move4, int health,
	const int attack, const int spAttack, const int defense, const int spDefense, 
	int speed, const strategyFunc strategy, bool paralyzed, const int team)
	: name(name), type(type), move1(move1), move2(move2), move3(move3), move4(move4),
	health(health), attack(attack), spAttack(spAttack), defense(defense), spDefense(spDefense), speed(speed), strategy(strategy), paralyzed(paralyzed), team(team)
{
	if (name.empty()) {
		throw runtime_error("Name cannot be empty");
	}
	if (health <= 0) {
		throw runtime_error("Health cannot be less than or equal to 0");
	}
	if (attack <= 0) {
		throw runtime_error("Attack cannot be less than or equal to 0");
	}
	if (spAttack <= 0) {
		throw runtime_error("Special attack cannot be less than or equal to 0");
	}
	if (defense <= 0) {
		throw runtime_error("Defense cannot be less than or equal to 0");
	}
	if (spDefense <= 0) {
		throw runtime_error("Special defense cannot be less than or equal to 0");
	}
	if (speed <= 0) {
		throw runtime_error("Speed cannot be less than or equal to 0");
	}
	if (move1 == nullptr || move2 == nullptr || move3 == nullptr || move4 == nullptr) {
		throw runtime_error("Moves cannot be null");
	}
	if (team != 1 && team != 2) {
		throw runtime_error("Team must be 1 or 2");
	}
}

//constructor f�r dualtypepokemon
DualTypePokemon::DualTypePokemon(const string& name, const Type type1, const Type type2, const Move* move1,
	const Move* move2, const Move* move3, const Move* move4, int health, const int attack, const int spAttack, 
	const int defense, const int spDefense, int speed, const strategyFunc strategy, bool paralyzed, const int team)
	: Pokemon(name, type1, move1, move2, move3, move4, health, attack, spAttack, defense, spDefense, speed, strategy, paralyzed, team), type2(type2)
{
	if (type1 == type2) {
		throw runtime_error("Types cannot be the same");
	}
}

// reducera health med damage
void Pokemon::reduceHealth(int damage) {
	health -= damage;
	if (health < 0)
		health = 0;
}

//s�tter paralyzedstatus
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

// returnera multiplicering f�r skada
float Pokemon::calculateDamageMultiplier(Type damagetype) {
	return TypeChart::getDamageMultiplier(damagetype, type);
}

// returnera multiplicering f�r skada f�r dualtypepokemon
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
		throw runtime_error("Move does not exist.");
		break;
	}
}

//returnera f�rgkod f�r teamf�rg
const string Pokemon::getTeamColor() {
	if (team == 1)
		return BLUE;
	else if (team == 2)
		return ORANGE;
	else
		return RESET;
}

// funktioner f�r att l�gga till stats med hj�lp av buildern
PokemonBuilder& PokemonBuilder::addType(Type type) {
	if (typeList.size() == 2)
		throw runtime_error("Pokemon can only have two types");
	typeList.push_back(type);
	return *this;
}

PokemonBuilder& PokemonBuilder::addMove(const Move* move) {
	if (moveList.size() == 4)
		throw runtime_error("Pokemon can only have four moves");
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

PokemonBuilder& PokemonBuilder::setTeam(int team) {
	this->team = team;
	return *this;
}

//bygg pokemon med dessa stats
Pokemon* PokemonBuilder::build() {
	if (moveList.size() != 4)
		throw runtime_error("Pokemon must have four moves");
	if (typeList.size() == 1) {
		return new Pokemon(name, typeList[0], moveList[0], moveList[1], moveList[2], moveList[3], health, attack, spAttack, defense, spDefense, speed, strategy, paralyzed, team);
	}
	else if (typeList.size() == 2) {
		return new DualTypePokemon(name, typeList[0], typeList[1], moveList[0], moveList[1], moveList[2], moveList[3], health, attack, spAttack, defense, spDefense, speed, strategy, paralyzed, team);
	}
	else {
		throw runtime_error("Pokemon must have at least one type");
	}
}

Battle& Battle::addPokemonToA(Pokemon* pokemon) {
	if (TeamAlpha.size() == 6)
		throw runtime_error("Team A can only have six pokemon");
	TeamAlpha.push_back(pokemon);
	return *this;
}

Battle& Battle::addPokemonToB(Pokemon* pokemon) {
	if (TeamBravo.size() == 6)
		throw runtime_error("Team B can only have six pokemon");
	TeamBravo.push_back(pokemon);
	return *this;
}

//hitta snabbaste av tv� pokemon
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
		throw runtime_error("Teams cant be empty.");
	cout << endl << GREEN << "Battle starting!" << RESET << endl << endl;
	cout << BLUE << "Team Alpha" << RESET << " sent out " << BLUE << TeamAlpha.front()->getName() << "!" << RESET << endl;
	cout << ORANGE << "Team Bravo" << RESET << " sent out " << ORANGE << TeamBravo.front()->getName() << "!" << RESET << endl;
	int indexA = 0;
	int indexB = 0;
	while (indexA < TeamAlpha.size() && indexB < TeamBravo.size()) {

		Pokemon* pokemonA = TeamAlpha[indexA];
		Pokemon* pokemonB = TeamBravo[indexB];

		cout << "----------------------------------------" << endl;
		cout << BLUE << pokemonA->getName() << RESET << " health: " << RED << pokemonA->getHealth() << RESET << endl;
		cout << ORANGE << pokemonB->getName() << RESET << " health: " << RED << pokemonB->getHealth() << RESET << endl;

		Pokemon* fastest = getFastest(pokemonA, pokemonB);
		Pokemon* slowest = (fastest == pokemonA) ? pokemonB : pokemonA;

		//snabbare pokemonen attackerar
		const Move* firstMove = fastest->strategy(fastest, slowest);
		firstMove->perform(fastest, slowest);
		//kolla om f�rsvarande pokemon blev fainted av attackerande pokemon
		if (slowest->getHealth() <= 0) {
			if (slowest == pokemonA) {
				indexA++;
				if (indexA < TeamAlpha.size())
					cout << BLUE << "Team Alpha" << RESET << " sent out " << BLUE << TeamAlpha.front()->getName() << "!" << RESET << endl;
			}
			else if (slowest == pokemonB) {
				indexB++;
				if (indexB < TeamBravo.size())
					cout << ORANGE << "Team Bravo" << RESET << " sent out " << ORANGE << TeamBravo.front()->getName() << "!" << RESET << endl;
			}
		}
		//kolla om attackerande pokemon blev fainted av egen skada
		if (fastest->getHealth() <= 0) {
			if (fastest == pokemonA) {
				indexA++;
				if (indexA < TeamAlpha.size())
					cout << BLUE << "Team Alpha" << RESET << " sent out " << BLUE << TeamAlpha.front()->getName() << "!" << RESET << endl;
				continue;
			}
			else if (fastest == pokemonB) {
				indexB++;
				if (indexB < TeamBravo.size())
					cout << ORANGE << "Team Bravo" << RESET << " sent out " << ORANGE << TeamBravo.front()->getName() << "!" << RESET << endl;
				continue;
			}
		}
		//hoppar �ver s� att inte en fainted pokemon attackerar
		else if (slowest->getHealth() <= 0)
			continue;

		//sluta ifall n�got lag inte har n�gra pokemon kvar
		if (indexA >= TeamAlpha.size() || indexB >= TeamBravo.size())
			break;

		//l�ngsammare pokemonen attackerar
		const Move* secondMove = slowest->strategy(slowest, fastest);
		secondMove->perform(slowest, fastest);

		//kolla om f�rsvarande pokemon blev fainted av attackerande pokemon
		if (fastest->getHealth() <= 0) {
			if (fastest == pokemonA) {
				indexA++;
				if (indexA < TeamAlpha.size())
					cout << BLUE << "Team Alpha" << RESET << " sent out " << BLUE << TeamAlpha.front()->getName() << "!" << RESET << endl;
			}
			else if (fastest == pokemonB) {
				indexB++;
				if (indexB < TeamBravo.size())
					cout << ORANGE << "Team Bravo" << RESET << " sent out " << ORANGE << TeamBravo.front()->getName() << "!" << RESET << endl;
			}
		}
		//kolla om attackerande pokemon blev fainted av egen skada
		if (slowest->getHealth() <= 0) {
			if (slowest == pokemonA) {
				indexA++;
				if (indexA < TeamAlpha.size())
					cout << BLUE << "Team Alpha" << RESET << " sent out " << BLUE << TeamAlpha.front()->getName() << "!" << RESET << endl;
			}
			else if (slowest == pokemonB) {
				indexB++;
				if (indexB < TeamBravo.size())
					cout << ORANGE << "Team Bravo" << RESET << " sent out " << ORANGE << TeamBravo.front()->getName() << "!" << RESET << endl;
			}
		}
	}
	printRainbowDivider();
	if (indexB >= TeamBravo.size()) {
		cout << ORANGE << "Team Bravo" << RESET << " ran out of usable Pokemon!" << endl << endl << BLUE << "Team Alpha" << GREEN << " wins!" << RESET << endl;
		cout << BLUE << "Team Alpha: " << RESET;
		for (auto pokemon : TeamAlpha)
			cout << GREEN << pokemon->getName() << ": " << RED << pokemon->getHealth() << " HP, " << RESET;
		cout << endl;
	}
	else {
		cout << BLUE << "Team Alpha" << RESET << " ran out of usable Pokemon!" << endl << endl << ORANGE << "Team Bravo" << GREEN << " wins!" << RESET << endl;
		cout << ORANGE << "Team Bravo: " << RESET;
		for (auto pokemon : TeamBravo)
			cout << GREEN << pokemon->getName() << ": " << RED << pokemon->getHealth() << " HP, " << RESET;
		
	}
	cout << endl;
	printRainbowDivider();
}