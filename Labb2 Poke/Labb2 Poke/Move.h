#pragma once

#include <iostream>
#include <string>
#include "Type.h"

using namespace std;

class Pokemon;

class Move
{
protected:      //protected så att subklasser kan komma åt dessa variabler
    string name;
    Type type;
    int power;

    virtual void execute(Pokemon* attacker, Pokemon* defender) const = 0;

public:
    Move(const string& name, const Type type, const int power);

    virtual ~Move() {};
    void perform(Pokemon* attacker, Pokemon* defender) const;
    string& getName() { return name; }
};

class PhysicalMove : public Move
{
public:
    PhysicalMove(const string& name, const Type type, const int power);
	void execute(Pokemon* attacker, Pokemon* defender) const override;
};

class SpecialMove : public Move
{
public:
    SpecialMove(const string& name, const Type type, const int power);
    void execute(Pokemon* attacker, Pokemon* defender) const override;
};

class HealingMove : public Move
{
public:
	HealingMove(const string& name, const Type type, const int power);
	void execute(Pokemon* attacker, Pokemon* defender) const override;
};

class selfDestructMove : public Move
{
public:
    selfDestructMove(const string& name, const Type type, const int power);
	void execute(Pokemon* attacker, Pokemon* defender) const override;
};

class ParalyzingMove : public Move
{
public:
	ParalyzingMove(const string& name, const Type type, const int power);
	void execute(Pokemon* attacker, Pokemon* defender) const override;
};