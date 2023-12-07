#pragma once

#include <iostream>
#include <string>
#include "Type.h"
#include "Move.h"

using namespace std;

class Pokemon
{
private:

    const Move* move1;
    const Move* move2;
    const Move* move3;
    const Move* move4;

protected:
    const Type type;

public:
    // dessa borde förmodligen inte vara public
    const string name;
    int health;
    int attack;
    int spAttack;
    int defense;
    int spDefense;

    Pokemon(const string& name, const Type type, const Move* move1, const Move* move2,
        const Move* move3, const Move* move4, const int health, const int attack, const int spAttack,
        const int defense, const int spDefense);

    virtual ~Pokemon() {
    	delete move1;
		delete move2;
		delete move3;
		delete move4;
        cout << "Pokemon " << name << " has been deleted" << endl;
    }

    void executeMove1(Pokemon* target);

    void executeMove2(Pokemon* target);

    void executeMove3(Pokemon* target);

    void executeMove4(Pokemon* target);

    void reduceHealth(int);

    virtual float calculateDamageMultiplier(Type damagetype);

    int getAttack() { return attack; }  //returnerar attack
    int getDefense() { return defense; } //returnerar defense
    Type getType() { return type; } //returnerar type
    int getSpAttack() { return spAttack; } //returnerar spAttack
    int getSpDefense() { return spDefense; } //returnerar spDefense
    int getHealth() { return health; } //returnerar health
    string getName() { return name; } //returnerar name
};