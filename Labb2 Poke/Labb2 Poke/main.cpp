#include <iostream>
#include "Pokemon.h"

using namespace std;

void main()
{
	try
	{	
		PhysicalMove Tackle("Tackle", ROCK, 50);
		SpecialMove Flamethrower("Flamethrower", FIRE, 90);
		SpecialMove DragonClaw("Dragon Claw", DRAGON, 80);
		PhysicalMove Earthquake("Earthquake", GROUND, 100);
		SpecialMove SolarBeam("Solar Beam", GRASS, 120);
		SpecialMove Poison("Poison", POISON, 50);
		PhysicalMove Bite("Bite", DARK, 60);

		Pokemon* Charizard = new Pokemon("Charizard", FIRE, &Tackle, &Flamethrower, &DragonClaw, &Earthquake, 250, 100, 125, 50, 100);
		Pokemon* Ivysaur = new Pokemon("Bulbasaur", GRASS, &Bite, &Poison, &Bite, &SolarBeam, 150, 75, 100, 60, 80);
		
		Ivysaur->executeMove1(Charizard);
		Charizard->executeMove2(Ivysaur);
		Ivysaur->executeMove4(Charizard);
		Charizard->executeMove3(Ivysaur);
		Ivysaur->executeMove2(Charizard);
		Charizard->executeMove1(Ivysaur);
		Ivysaur->executeMove3(Charizard);
		Charizard->executeMove4(Ivysaur);

		//delete(Charizard);
		//delete(Ivysaur);

	}
	catch (const exception& e)
	{
		cout << "Error: " << e.what() << endl;
	}
}