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
	std::vector<std::string> abilities;
};
struct BossEnemy : public Enemy {
	std::vector<std::string> specialAbilities;
};

struct Familiar : public Enemy {
	std::string element;
	bool isCaptured = false;
};


extern std::vector<Enemy> regularEnemies;
extern std::vector<BossEnemy> bossEnemies;
extern std::vector<Familiar> familiars;