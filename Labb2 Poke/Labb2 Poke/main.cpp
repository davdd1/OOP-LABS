#include <iostream>
#include "Pokemon.h"

using namespace std;

const Move* simpleStrategy(const Pokemon* self, const Pokemon* target) {
	return self->getMove(1);	
}

const Move* randomStrategy(const Pokemon* self, const Pokemon* target) {
	int random = rand() % 4 + 1;
	return self->getMove(random);
}

void main()
{
	try
	{
		srand(time(0));

		PhysicalMove Tackle("Tackle", NORMAL, 50);
		SpecialMove Flamethrower("Flamethrower", FIRE, 90);
		SpecialMove DragonClaw("Dragon Claw", DRAGON, 80);
		PhysicalMove Earthquake("Earthquake", GROUND, 100);
		SpecialMove SolarBeam("Solar Beam", GRASS, 120);
		SpecialMove Poison("Poison", POISON, 50);
		PhysicalMove Bite("Bite", DARK, 60);
		SpecialMove Thunderbolt("Thunderbolt", ELECTRIC, 90);
		SpecialMove Thunder("Thunder", ELECTRIC, 110);
		PhysicalMove BodySlam("Body Slam", NORMAL, 85);
		selfDestructMove SelfDestruct("Self Destruct", NORMAL, 200);
		HealingMove Recover("Recover", NORMAL, 100);
		PhysicalMove LowKick("Low Kick", FIGHTING, 50);
		ParalyzingMove ThunderWave("Thunder Wave", ELECTRIC, 0);

		Pokemon* Charizard = PokemonBuilder()
			.setName("Charizard")
			.addMove(&Flamethrower)
			.addMove(&Tackle)
			.addMove(&DragonClaw)
			.addMove(&Earthquake)
			.addType(FIRE)
			.addType(FLYING)
			.setHealth(120)
			.setAttack(85)
			.setDefense(70)
			.setSpAttack(90)
			.setSpDefense(55)
			.setSpeed(100)
			.setStrategy(&randomStrategy)
			.build();

		Pokemon* Venusaur = PokemonBuilder()
			.setName("Venusaur")
			.addMove(&Tackle)
			.addMove(&Poison)
			.addMove(&Bite)
			.addMove(&SolarBeam)
			.addType(GRASS)
			.addType(POISON)
			.setHealth(105)
			.setAttack(75)
			.setDefense(80)
			.setSpAttack(60)
			.setSpDefense(50)
			.setSpeed(80)
			.setStrategy(&randomStrategy)
			.build();

		Pokemon* Blastoise = PokemonBuilder()
			.setName("Blastoise")
			.addMove(&Tackle)
			.addMove(&Poison)
			.addMove(&Bite)
			.addMove(&SolarBeam)
			.addType(WATER)
			.setHealth(105)
			.setAttack(75)
			.setDefense(75)
			.setSpAttack(60)
			.setSpDefense(80)
			.setSpeed(80)
			.setStrategy(&randomStrategy)
			.build();

		Pokemon* Electrode = PokemonBuilder()
			.setName("Electrode")
			.addMove(&SelfDestruct)
			.addMove(&Thunderbolt)
			.addMove(&Thunder)
			.addMove(&ThunderWave)
			.addType(ELECTRIC)
			.setHealth(100)
			.setBothAttacks(75)
			.setDefense(65)
			.setSpDefense(80)
			.setSpeed(150)
			.setStrategy(&randomStrategy)
			.build();

		Pokemon* Snorlax = PokemonBuilder()
			.setName("Snorlax")
			.addMove(&Tackle)
			.addMove(&ThunderWave)
			.addMove(&Recover)
			.addMove(&BodySlam)
			.addType(NORMAL)
			.setHealth(160)
			.setAttack(100)
			.setDefense(65)
			.setSpAttack(65)
			.setSpDefense(110)
			.setSpeed(30)
			.setStrategy(&randomStrategy)
			.build();

		Pokemon* Machamp = PokemonBuilder()
			.setName("Machamp")
			.addMove(&Tackle)
			.addMove(&LowKick)
			.addMove(&Recover)
			.addMove(&BodySlam)
			.addType(FIGHTING)
			.setHealth(100)
			.setAttack(100)
			.setDefense(60)
			.setSpAttack(60)
			.setSpDefense(90)
			.setSpeed(35)
			.setStrategy(&randomStrategy)
			.build();

		Pokemon* Alakazam = PokemonBuilder()
			.setName("Alakazam")
			.addMove(&Tackle)
			.addMove(&LowKick)
			.addMove(&Recover)
			.addMove(&BodySlam)
			.addType(PSYCHIC)
			.setHealth(100)
			.setAttack(100)
			.setDefense(60)
			.setSpAttack(60)
			.setSpDefense(90)
			.setSpeed(60)
			.setStrategy(&randomStrategy)
			.build();

		Pokemon* Raichu = PokemonBuilder()
			.setName("Raichu")
			.addMove(&ThunderWave)
			.addMove(&LowKick)
			.addMove(&Recover)
			.addMove(&BodySlam)
			.addType(ELECTRIC)
			.setHealth(90)
			.setAttack(100)
			.setDefense(60)
			.setSpAttack(60)
			.setSpDefense(90)
			.setSpeed(130)
			.setStrategy(&randomStrategy)
			.build();

		Battle()
			.addPokemonToA(Charizard)
			.addPokemonToA(Blastoise)
			.addPokemonToA(Snorlax)
			.addPokemonToA(Alakazam)

			.addPokemonToB(Venusaur)
			.addPokemonToB(Electrode)
			.addPokemonToB(Machamp)
			.addPokemonToB(Raichu)

			.start();
	}
	catch (const exception& e)
	{
		cout << "Error: " << e.what() << endl;
	}
}