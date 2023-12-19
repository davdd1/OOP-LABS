#include "inventory.h"

void main() {
	try
	{	
		Inventory i1(256, 32);

		Item Dagger("Dagger", 2);
		Item Sword("Sword", 8);
		Item Axe("Axe", 10);
		Item Helmet("Helmet", 6);
		Item Boots("Boots", 4);
		
		errorHandler(i1.depositItem(Dagger));
		errorHandler(i1.depositItem(Dagger));
		errorHandler(i1.depositItem(Sword));
		errorHandler(i1.depositItem(Axe));
		errorHandler(i1.depositItem(Helmet));
		errorHandler(i1.depositItem(Boots));
		errorHandler(i1.depositItem(Boots));

		i1.withdrawItem("Sword");
		i1.withdrawItem("Boots");

		cout << "Current weight: " << i1.getCurrentWeight() << endl;
	}
	catch (const invalid_argument& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
}