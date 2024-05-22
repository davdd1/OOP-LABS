#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "Type.h"
#include "Move.h"

using namespace std;
using strategyFunc = function<const Move* (const Pokemon*, const Pokemon*)>;

class Pokemon
{
	//private så att endast denna klass kan komma åt dessa variabler direkt
	//getters och setters används för att komma åt dessa variabler utanför klassen
private:
	const Move* move1;
	const Move* move2;
	const Move* move3;
	const Move* move4;
	const string name;
	const Type type;
	int health;
	const int attack;
	const int spAttack;
	const int defense;
	const int spDefense;
	int speed;
	bool paralyzed = false;
	const int team;

public:
	Pokemon(const string& name, const Type type, const Move* move1, const Move* move2,
		const Move* move3, const Move* move4, int health, const int attack, const int spAttack,
		const int defense, const int spDefense, int speed, const strategyFunc strategy, bool paralyzed, const int team);

	virtual ~Pokemon() {
		cout << endl << "Pokemon " << name << " has been deleted";
	}

	const strategyFunc strategy;
	virtual float calculateDamageMultiplier(Type damagetype);

	const int getAttack() { return attack; }  //returnerar attack
	const int getDefense() { return defense; } //returnerar defense
	const Type getType() { return type; } //returnerar type
	const Type getType2() { return type; } //returnerar type2
	const int getSpAttack() { return spAttack; } //returnerar spAttack
	const int getSpDefense() { return spDefense; } //returnerar spDefense
	const int getHealth() { return health; } //returnerar health
	const int getSpeed() { return speed; } //returnerar speed
	const string getName() { return name; } //returnerar name
	const Move* getMove(int moveNumber) const; //returnerar move)
	const strategyFunc getStrategy() { return strategy; } //returnerar strategy
	const bool isParalyzed() { return paralyzed; } //returnerar paralyzed
	const int getTeam() { return team; }  //returnerar vilket team
	const string getTeamColor();   //returnerar färgkod för teamfärg

	void setParalyzed(bool status); //sätter paralyzedstatus
	void setHealth(int newHealth) { health = newHealth; } //sätter health
	void addHealth(int health); //adderar health
	void reduceHealth(int damage); //reducerar health med damage
};

class DualTypePokemon : public Pokemon
{
private:			//private för att endast denna klass behöver komma åt type2
	const Type type2;
public:
	DualTypePokemon(const string& name, const Type type1, const Type type2, const Move* move1, const Move* move2,
		const Move* move3, const Move* move4, int health, const int attack, const int spAttack,
		const int defense, const int spDefense, int speed, const strategyFunc strategy, bool paralyzed, const int team);
	float calculateDamageMultiplier(Type damagetype) override;
};

class PokemonBuilder {
private:
	vector<Type> typeList;
	vector<const Move*> moveList;
	string name;
	int health;
	int attack;
	int defense;
	int spAttack;
	int spDefense;
	int speed;
	bool paralyzed = false;
	strategyFunc strategy;
	int team;

public:
	PokemonBuilder() {};
	PokemonBuilder& addType(Type type);
	PokemonBuilder& addMove(const Move* move);
	PokemonBuilder& setName(string name);
	PokemonBuilder& setHealth(int health);
	PokemonBuilder& setAttack(int attack);
	PokemonBuilder& setDefense(int defense);
	PokemonBuilder& setSpAttack(int spAttack);
	PokemonBuilder& setSpDefense(int spDefense);
	PokemonBuilder& setBothAttacks(int attack);
	PokemonBuilder& setBothDefenses(int defense);
	PokemonBuilder& setSpeed(int speed);
	PokemonBuilder& setStrategy(strategyFunc strategy);
	PokemonBuilder& setTeam(int team);
	Pokemon* build();
};

class Battle {
private:
	vector<Pokemon*> TeamAlpha;
	vector<Pokemon*> TeamBravo;
public:
	Battle() {};

	//deletar alla pokemon från vectorerna
	~Battle() {
		for (int i = 0; i < TeamAlpha.size(); i++) {
			delete TeamAlpha[i];
		}
		for (int i = 0; i < TeamBravo.size(); i++) {
			delete TeamBravo[i];
		}
	};
	Battle& addPokemonToA(Pokemon* pokemon); //lägger till pokemon i vectorn Alpha
	Battle& addPokemonToB(Pokemon* pokemon); //lägger till pokemon i vectorn Bravo
	void start(); //startar battle
};