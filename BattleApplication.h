#pragma once
#include <vector>
#include "PartyMember.h"
#include "Enemies.h"

// Forward declarations
extern std::vector<PartyMember> party;
extern std::vector<RegularEnemy> enemies;

// Game initialization and main loop
void InitializeGame();
void RunGameLoop();