#pragma once
#include <vector>
#include <string>

struct Ability {
	int id;
	std::string name;
	int power;
	std::string element;
	int cost;
};
extern std::vector<Ability> abilities;

