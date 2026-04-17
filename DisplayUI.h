#pragma once
#include <string>
#include <vector>
#include <windows.h>
#include "PartyMember.h"
#include "Enemies.h"

// Color codes for Windows console
enum ConsoleColor {
    BLUE = 9,      // bright blue
    RED = 12,      // bright red
    GREEN = 10,    // bright green
    YELLOW = 14,   // bright yellow
    WHITE = 15,    // white
    GRAY = 8       // dark gray
};

// Function declarations (not implementations)
void SetConsoleColor(ConsoleColor color);
void ResetConsoleColor();
std::string CreateHPBar(int current, int max, int barWidth = 15);
std::string CreateManaBar(int current, int max, int barWidth = 15);
void DisplayPartyBars(const std::vector<PartyMember>& party);

// Display enemies with HP bars
void DisplayEnemyBars(const std::vector<RegularEnemy>& enemies);

// Display battlefield with party on left and enemies on right
void DisplayBattleField(const std::vector<PartyMember>& party, 
                        const std::vector<RegularEnemy>& enemies);

// Menu selector function - displays party and enemies with menu
// Returns the index (0-based) of the selected menu option
int DisplayMenuSelector(const std::vector<std::string>& options, 
                        const std::vector<PartyMember>& party,
                        const std::vector<RegularEnemy>& enemies,
                        const std::string& menuTitle = "");

// Target selector for choosing an enemy
// Returns the index of the selected enemy
int DisplayEnemyTargetSelector(const std::vector<RegularEnemy>& enemies,
                               const std::vector<PartyMember>& party,
                               const std::string& characterName = "");