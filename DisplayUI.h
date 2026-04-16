#pragma once
#include <string>
#include <vector>
#include <windows.h>
#include "PartyMember.h"

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
