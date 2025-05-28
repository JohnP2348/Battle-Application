#include "Magic.h"

std::vector<Magic> magics = {
	// id, name, power, school, manaCost, effect
	{1, "Decay", 8, AlchemySchool::Nigredo, 3, "lowers a random stat of the target by 10%"},
	{2, "Purification", 10, AlchemySchool::Albedo, 5, "heals a random party member by 15%"},
	{3, "Enlightenment", 12, AlchemySchool::Citrinitas, 7, "increases a random stat of the target by 15%"},
	{4, "Transmutation", 0, AlchemySchool::Rubedo, 15, "Allows caster to pick party member or enemy and change their type, 30% chance on enemy, 100% chance on ally."}
};