#pragma once
#include <vector>
#include <string>

enum class ItemType {
	Consumable,
	Equipment,
	KeyItem
};
struct Item {
	int id;
	std::string name;
	ItemType type;
	int power;// for consumables, this could be health restored or damage done
	std::string effect;
};
extern std::vector<std::string> Items;
