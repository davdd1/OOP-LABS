#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "Type.h"
#include "Move.h"

using namespace std;
using strategyFunc = function<Move*(Pokemon*, Pokemon*)>;

class Pokemon
{
private:

	Move* move1;
	Move* move2;
	Move* move3;
	Move* move4;

protected:
	Type type;

public:
	string name;
	int health;
	int attack;
	int spAttack;
	int defense;
	int spDefense;
	int speed;
	strategyFunc strategy;

	Pokemon(string& name, Type type, Move* move1, Move* move2,
		Move* move3, Move* move4, int health, int attack, int spAttack,
		int defense, int spDefense, int speed, strategyFunc strategy);

	virtual ~Pokemon() {
		cout << endl << "Pokemon " << name << " has been deleted" << endl;
	}

	void executeMove1(Pokemon* target);

	void executeMove2(Pokemon* target);

	void executeMove3(Pokemon* target);

	void executeMove4(Pokemon* target);

	void reduceHealth(int damage);

	void addHealth(int health);

	virtual float calculateDamageMultiplier(Type damagetype);

	int getAttack() { return attack; }  //returnerar attack
	int getDefense() { return defense; } //returnerar defense
	Type getType() { return type; } //returnerar type
	int getSpAttack() { return spAttack; } //returnerar spAttack
	int getSpDefense() { return spDefense; } //returnerar spDefense
	int getHealth() { return health; } //returnerar health
	int getSpeed() { return speed; } //returnerar speed
	string getName() { return name; } //returnerar name
	Move* getMove(int moveNumber); //returnerar move)
	strategyFunc getStrategy() { return strategy; } //returnerar strategy
};

class DualTypePokemon : public Pokemon
{
private:
	Type type2;
public:
	DualTypePokemon(string& name, Type type1, Type type2, Move* move1, Move* move2,
		Move* move3, Move* move4, int health, int attack, int spAttack,
		int defense, int spDefense, int speed, strategyFunc strategy);
	float calculateDamageMultiplier(Type damagetype) override;
};

class PokemonBuilder {
private:
	vector<Type> typeList;
	vector<Move*> moveList;
	string name;
	int health;
	int attack;
	int defense;
	int spAttack;
	int spDefense;
	int speed;
	strategyFunc strategy;
	
public:
	PokemonBuilder() {};
	PokemonBuilder& addType(Type type);
	PokemonBuilder& addMove(Move* move);
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
	Pokemon* build();
};

class Battle {
private:
	vector<Pokemon*> TeamAlpha;
	vector<Pokemon*> TeamBravo;
public:
	Battle() {};
	~Battle() {};	//deletar alla pokemon från vectorerna
	Battle& addPokemonToA(Pokemon* pokemon); //lägger till pokemon i vectorn Alpha
	Battle& addPokemonToB(Pokemon* pokemon); //lägger till pokemon i vectorn Bravo
	void start(); //startar battle
};