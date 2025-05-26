#pragma once
#include <string> 
#include <vector>

struct PartyMember {
	std::string name;
	std::string charClass;
	int maxHealth;
	int health;
	int maxMana;
	int mana;
	int strength;
	int defense;
	int speed;
	int level;
	int experience;
};
extern std::vector<PartyMember> party;