#pragma once
#include <string>
#include <vector>

enum class AlchemySchool {
	Nigredo,
	Albedo,
	Citrinitas,
	Rubedo
};
struct Magic {
	int id;
	std::string name;
	int power;
	AlchemySchool school;
	int manaCost;
	std::string effect;
};

extern std::vector<Magic> magics;