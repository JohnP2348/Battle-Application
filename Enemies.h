#pragma once
#include <vector>
#include <string>

struct Enemy {
	int id;
	std::string name;
	int maxHealth;
	int health;
	int attack;
	int defense;
	int speed; 
};
struct RegularEnemy : public Enemy {
	std::string element;
	int level;
	std::vector<int> abilityIDs;

	// Constructor for RegularEnemy
	RegularEnemy(int id, const std::string& name, int maxHealth, int health, int attack, int defense, int speed,
		const std::string& element, int level, const std::vector<int>& abilityIDs)
		: Enemy{ id, name, maxHealth, health, attack, defense, speed },
		element(element), level(level), abilityIDs(abilityIDs) {}
};
struct BossEnemy : public Enemy {
	std::vector<int> abilityIDs;

	// Constructor for BossEnemy
	BossEnemy(int id, const std::string& name, int maxHealth, int health, int attack, int defense, int speed,
		 const std::vector<int>& abilityIDs)
		: Enemy{ id, name, maxHealth, health, attack, defense, speed },
		 abilityIDs(abilityIDs)
	{}
};

struct Familiar : public Enemy {
	std::string element;
	std::vector<int> abilityIDs;
	bool isCaptured = false;

	Familiar(int id, const std::string& name, int maxHealth, int health, int attack, int defense, int speed,
		const std:: string& element, const std::vector<int>& abilityIDs, bool isCaptured = false)
		: Enemy{ id, name, maxHealth, health, attack, defense, speed },
		element(element), abilityIDs(abilityIDs), isCaptured(isCaptured) {}
};


extern std::vector<RegularEnemy> regularEnemies;
extern std::vector<BossEnemy> bossEnemies;
extern std::vector<Familiar> familiars;