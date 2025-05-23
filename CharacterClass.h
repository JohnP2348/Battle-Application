#pragma once
#include <string>
#include <vector>

struct CharacterClass {
	int id;
	std::string className;
	int healthModifier;
	int manaModifier;
	int strengthModifier;
	int defenseModifier;
	int speedModifier;
	// Abilities unlocked at certain class levels paired with their level
	std::vector<std::pair<int, int>> abilitiesByLevel;
};
extern std::vector<CharacterClass> classList;