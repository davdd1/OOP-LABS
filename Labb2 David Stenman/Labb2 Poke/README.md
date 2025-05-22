# Labb2 – Pokémon-projekt

Detta projekt är en del av kursen Objektorienterad Programmering och är det andra labbmomentet. Projektet syftar till att fördjupa förståelsen för objektorienterade principer i C++ med hjälp av ett Pokémon-inspirerat spelsystem.

## Syfte

Projektet tränar på:
- Objektorienterad design och implementation i C++
- Arv, polymorfism och inkapsling
- Hantering av dynamiska objekt och minne

## Översikt

Labb2-projektet simulerar grundläggande Pokémon-strider 6v6. Du kan skapa olika Pokémon-objekt (med olika egenskaper och attacker), låta dem slåss mot varandra och följa deras status under stridens gång.

### Funktioner

- **Skapa Pokémon:** Flera olika Pokémon-klasser finns, med olika attribut (t.ex. namn, HP, attackstyrka, typ).
- **Stridssystem:** Pokémon kan attackera varandra, ta skada och förlora HP tills en vinnare utses.
- **Arv och polymorfism:** Olika Pokémon ärver från en gemensam basklass och kan ha olika attacker eller specialegenskaper.
- **Användarinteraktion:** Programmet kan köras i terminalen, där användaren kan välja Pokémon och starta en strid.

## Exempel på kod (utdrag)

```cpp
Pokemon* p1 = new FirePokemon("Charmander", 100, 20);
Pokemon* p2 = new WaterPokemon("Squirtle", 110, 18);

p1->attack(p2);
p2->attack(p1);
```
