#include <iostream>
#include "Pokemon.h"

using namespace std;

Move* simpleStrategy(Pokemon* self, Pokemon* target) {
	return self->getMove(1);
}

void main()
{
	try
	{
		//auto strategy1 = [](Pokemon* attacker, Pokemon* defender)
		//	{
		//	};
		//auto strategy2 = [](Pokemon* attacker, Pokemon* defender)
		//	{

		//	};

		////iterera genom alla moves och returnera den som har högst damage
		//auto strategy3 = [](const Pokemon* attacker, const Pokemon* defender) {
		//	const Move* moves[] =
		//	{
		//		attacker*->getMove(1) , attacker->getMove(2), attacker->getMove(3), attacker->getMove(4)
		//	};
		//	const Move* bestMove = nullptr;
		//	for (auto move : moves)
		//	{
		//		if (bestMove == nullptr)
		//		{
		//			bestMove = move; continue;
		//		} 
		//		if (defender->calculateDamageMultiplier(move->getType()) > defender->calculateDamageMultiplier(bestMove->getType())) 
		//		{ 
		//			bestMove = move; 
		//		}
		//	} 
		//	return bestMove; 
		//};


		PhysicalMove Tackle("Tackle", ROCK, 50);
		SpecialMove Flamethrower("Flamethrower", FIRE, 90);
		SpecialMove DragonClaw("Dragon Claw", DRAGON, 80);
		PhysicalMove Earthquake("Earthquake", GROUND, 100);
		SpecialMove SolarBeam("Solar Beam", GRASS, 120);
		SpecialMove Poison("Poison", POISON, 50);
		PhysicalMove Bite("Bite", DARK, 60);

	///*	DualTypePokemon* Charizard = new DualTypePokemon("Charizard", FIRE, FLYING, &Tackle, &Flamethrower, &DragonClaw, &Earthquake, 400, 100, 125, 50, 100, 50);
	//		DualTypePokemon* Venusaur = new DualTypePokemon("Venusaur", GRASS, POISON, &Bite, &Poison, &Bite, &SolarBeam, 300, 75, 100, 60, 80, 50);*/

		Pokemon* p1 = PokemonBuilder()
			.setName("Charizard")
			.addMove(&Tackle)
			.addMove(&Flamethrower)
			.addMove(&DragonClaw)
			.addMove(&Earthquake)
			.addType(FIRE)
			.addType(FLYING)
			.setHealth(400)
			.setAttack(100)
			.setDefense(125)
			.setSpAttack(50)
			.setSpDefense(100)
			.setSpeed(50)
			.setStrategy(&simpleStrategy)
			.build();

		Pokemon* p2 = PokemonBuilder()
			.setName("Venusaur")
			.addMove(&Bite)
			.addMove(&Poison)
			.addMove(&Bite)
			.addMove(&SolarBeam)
			.addType(GRASS)
			.addType(POISON)
			.setHealth(300)
			.setAttack(75)
			.setDefense(100)
			.setSpAttack(60)
			.setSpDefense(80)
			.setSpeed(50)
			.setStrategy(&simpleStrategy)
			.build();

		Battle()
			.addPokemonToA(p1)
			.addPokemonToB(p2)
			.start();

	//	Venusaur->executeMove1(Charizard);
	//	Charizard->executeMove2(Venusaur);
	//	Venusaur->executeMove4(Charizard);
	//	Charizard->executeMove3(Venusaur);
	//	Venusaur->executeMove2(Charizard);
	//	Charizard->executeMove1(Venusaur);
	//	Venusaur->executeMove3(Charizard);
	//	Charizard->executeMove4(Venusaur);

	//	delete Charizard;
	//	delete Venusaur;
	}
	catch (const exception& e)
	{
		cout << "Error: " << e.what() << endl;
	}
}