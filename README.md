# OOP-LABS

Detta repository är för Objektorienterad Programmering-kursens tre projekt.

Här samlas kod, rapporter och annat material relaterat till kursens projektuppgifter. Varje projektmap finns i sin egen katalog.


# Labb1 – Inventory System med Stacking

Denna labb är en implementation av ett enkelt inventory system där objekt kan lagras och hanteras. Systemet har stöd för stacking-funktionalitet, vilket innebär att flera exemplar av samma objekt kan staplas på en och samma plats i inventariet.


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


# Slutinlämning – Enhetshanteringssystem

Detta projekt är en slutinlämning i kursen Objektorienterad Programmering. Programmet är ett menybaserat system för hantering av virtuella enheter ("devices"), där användaren kan skapa, koppla, ta bort och visualisera enheter samt testa anslutningar mellan dem.

## Översikt – Vad programmet gör

- Programmet låter användaren skapa två typer av enheter: NetworkDevice och AudioDevice.
- Varje enhet får ett unikt namn (valideras) och kan kopplas ihop med andra enheter i en trädstruktur.
- Användaren kan:
  - Skapa nya enheter.
  - Ta bort en enhet (och dess "barnenheter" om sådana finns).
  - Koppla ihop två enheter (om reglerna tillåter och ingen cykel skapas).
  - Koppla isär två enheter.
  - Visa alla enheter och deras anslutningar i en trädliknande vy.
  - Skicka en "ping" till en enhet, vilket visar pingen för enheten och dess föräldrar upp till roten.
- Alla interaktioner sker via ett menybaserat gränssnitt i terminalen, där användaren väljer åtgärd och anger namn på enheter när det behövs.
- Systemet hanterar alla felaktiga inmatningar och otillåtna operationer med tydliga felmeddelanden.
- Programmet är byggt med objektorienterade principer: arv, polymorfism, inkapsling och korrekt minneshantering.

## Syfte

Projektet demonstrerar och tränar på:
- Objektorienterad design och implementation i C++
- Arv, polymorfism och inkapsling
- Hantering av dynamiska objekt och minne
- Strukturering och dokumentation av kod

---
