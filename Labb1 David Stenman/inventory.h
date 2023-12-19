#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <stdexcept>
#include <optional>

using namespace std;

class Item{
private:
	string itemName;
	float itemWeight;
public:
	Item(const string name, const float weight);
	float getWeight() { return itemWeight; }
	string getName() { return itemName; }
};

class Inventory{
private:
	float weightCap;
	int itemCap;
	vector< vector<Item> > itemVector;
	float currentWeight;
public:
	Inventory(const float maxWeight, const int maxItems);
	optional<Item> withdrawItem(string name);
	int depositItem(Item& newItem);
	vector< vector<Item>> getItems();
	float getCurrentWeight();
};

void errorHandler(int code);