#pragma once

#include <iostream>
#include <string>
#include "Type.h"

using namespace std;

class Pokemon;

class Move
{
protected:
    const string name;
    const Type type;
    const int power;

    virtual void execute(Pokemon* attacker, Pokemon* defender) const = 0;

public:
    Move(const string& name, const Type type, const int power);

    virtual ~Move() {};
    void perform(Pokemon* attacker, Pokemon* defender) const;
    const string& getName() const { return name; }
};

class PhysicalMove : public Move
{
public:
    PhysicalMove(const string& name, const Type type, const int power);
	void execute(Pokemon* attacker, Pokemon* defender) const override;
    virtual ~PhysicalMove() { cout << "Deleted physical move" << endl; }
};

class SpecialMove : public Move
{
public:
    SpecialMove(const string& name, const Type type, const int power);
    void execute(Pokemon* attacker, Pokemon* defender) const override;
    virtual ~SpecialMove() { cout << "Deleted special move" << endl; }
};

void effectiveness(float multiplier);