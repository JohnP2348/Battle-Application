#include "CharacterClass.h"
#include <vector>


std::vector<CharacterClass> classList = {
	// id, class, hp, mp, str, def, spd, abilitiesByLevel
		{1, "Warrior", 20, 0, 5, 5, 0, {{1, 1}, {2, 5}, {3, 10}}},
		{2, "Mage", 10, 20, 0, 3, 2, {{1, 1}, {2, 3}, {3, 8}}},
		{3, "Rogue", 15, 10, 4, 2, 5, {{1, 1}, {2, 4}, {3, 9}}},
		{4, "Cleric", 12, 15, 2, 4, 3, {{1, 1}, {2, 6}, {3, 11}}},
		{5, "Paladin", 18, 5, 6, 6, 1, {{1, 1}, {2, 7}, {3, 12}}}
		};