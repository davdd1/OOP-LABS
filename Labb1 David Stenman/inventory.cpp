#include "inventory.h"

using namespace std;

Item::Item(const string name, const float weight)
{
	if (weight > 0) {
		itemName = name;
		itemWeight = weight;
	}
	else
		throw invalid_argument("Invalid weight for item.");
}

Inventory::Inventory(const float maxWeight, const int maxItems)
	: currentWeight(0)
{
	if (maxWeight >= 0)
		weightCap = maxWeight;
	else
		throw invalid_argument("Invalid weight capacity.");
	if (maxItems % 8 == 0 && maxItems >= 0)
		itemCap = maxItems;
	else
		throw invalid_argument("Invalid item capacity.");
}

optional<Item> Inventory::withdrawItem(string name) {
	//iterera genom alla vektorer tills jag hittar rätt föremål för att ta bort
	for (int i = 0; i < itemVector.size(); i++) {
		//iterera genom 'staplarna' av stacks
		for (int j = 0; j < itemVector[i].size(); j++) //BEHÖVS EJ
		{
			//om stacken har färre än 64
			if (itemVector[i][0].getName() == name && itemVector[i].size() < 64) 
			{
				Item tempItem = itemVector[i].back();
				currentWeight -= tempItem.getWeight();
				itemVector[i].pop_back();
				if (itemVector[i].empty())	//ifall en inre vektor blir tom så ska den tas bort helt
				{
					itemVector.erase(itemVector.begin() + i);
				}
				return tempItem;
			}
		}
		for (int j = 0; j < itemVector[i].size(); j++)
		{
			//om stacken är 64
			if (itemVector[i][0].getName() == name && itemVector[i].size() == 64) 
			{
				Item tempItem = itemVector[i].back();
				currentWeight -= tempItem.getWeight();
				itemVector[i].pop_back();
				return tempItem;
			}
		}
	}
	return nullopt;		//finns då ej med i inventory
}

int Inventory::depositItem(Item& newItem) {
	const float weight = newItem.getWeight();
	const float newWeight = Inventory::currentWeight + weight;

	//pre-conditions
	if (newWeight > weightCap && !(Inventory::itemVector.size() > Inventory::itemCap))
		//Går över viktgränsen
		return 1;
	if (Inventory::itemVector.size() > Inventory::itemCap && !(newWeight > weightCap))
		//Går över item-gränsen
		return 2;
	if (newWeight > weightCap && Inventory::itemVector.size() > Inventory::itemCap)
		//Går över både gränser
		return 3;

	//kolla om det medskickade föremålet är stackable, isåfall lägg till i stacken
	//itererar genom varje stack
	for (int i = 0; i < itemVector.size(); i++) {
		if (itemVector[i].size() < 64 && itemVector[i][0].getName() == newItem.getName())
		{
			itemVector[i].push_back(newItem);
			currentWeight += weight;
			return 4;
		}
	}

	//lägger annars bara till föremålet vanligt i en ny vektor
	itemVector.push_back({ newItem });
	currentWeight += weight;
	return 0;
}

//skapar en kopia av hela föremålsvektorn och returnerar
vector< vector<Item> > Inventory::getItems() {
	vector< vector<Item> > tempVec(itemVector);
	return tempVec;
}

//returnerar nuvarande vikten { O(1) }
float Inventory::getCurrentWeight() {
	return currentWeight;
}

//en sorts hjälpfunktion med olika case för error-hantering
void errorHandler(int code) {
	switch (code)
	{
	case 0:
		cout << "Item successfully deposited!\n";
		break;
	case 1:
		cout << "Item deposit failed. Would exceed weight capacity.\n";
		break;
	case 2:
		cout << "Item deposit failed. Would exceed item limit.\n";
		break;
	case 3:
		cout << "Item deposit failed. Would exceed weight and item limit.\n";
		break;
	case 4:
		cout << "Item stacked successfully!\n";
		break;
	default:
		break;
	}
}