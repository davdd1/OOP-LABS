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
