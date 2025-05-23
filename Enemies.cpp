#include "Enemies.h"
#include <iostream>
#include <string>
#include <vector>
//standard enemy encounters

std::vector<RegularEnemy> regularEnemies = {
	{1, "Slime", 30, 30, 8, 3, 5, "Water", 1, {/*put ability ID here*/}},
	{ 2, "Wolf", 50, 50, 12, 5, 7, "Earth", 1,{/*put ability ID here*/}},
	{ 3, "Goblin", 40, 40, 10, 4, 6, "Fire", 1,{/*put ability ID here*/}},
	{ 4, "Skeleton", 60, 60, 15, 6, 8, "Dark", 1,{/*put ability ID here*/}},
	{ 5, "Orc", 80, 80, 20, 8, 9, "Earth", 2,{/*put ability ID here*/}}

};
std::vector<BossEnemy> bossEnemies = {
	{ 1, "Dragon", 200, 200, 30, 10, 15, { "Fire Breath", "Tail Swipe" } },
	{ 2, "Giant", 250, 250, 35, 12, 12, { "Ground Slam", "Rock Throw" } },
	{ 3, "Vampire", 180, 180, 25, 8, 14, { "Blood Drain", "Shadow Strike" } }
};

std::vector<Familiar> familiars = {
	{ 1, "Fire Sprite", 40, 40, 10, 2, 5, "Fire", false },
	{ 2, "Water Spirit", 50, 50, 8, 3, 6, "Water", false },
	{ 3, "Earth Golem", 60, 60, 12, 4, 7, "Earth", false }
};

