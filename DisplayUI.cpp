#include <iostream>
#include <conio.h>  // For _getch() to read keyboard input
#include "DisplayUI.h"

void SetConsoleColor(ConsoleColor color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ResetConsoleColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

std::string CreateHPBar(int current, int max, int barWidth) {
    if (max <= 0) return std::string(barWidth, '_');
    
    // Calculate percentage of HP remaining (0.0 to 1.0)
    double percentage = static_cast<double>(current) / static_cast<double>(max);
    
    // Each 10% = 1 "=", so 10 "=" max for 100%
    // If bar width is 10, then: 100% = 10 "=", 90% = 9 "=", etc.
    int filledBars = static_cast<int>(percentage * barWidth);
    filledBars = (filledBars < 0) ? 0 : (filledBars > barWidth) ? barWidth : filledBars;
    
    std::string bar = "[";
    
    // Add filled bars (blue for healthy)
    SetConsoleColor(BLUE);
    for (int i = 0; i < filledBars; i++) {
        bar += '=';
    }
    ResetConsoleColor();
    
    // Add empty bars (underscores)
    for (int i = filledBars; i < barWidth; i++) {
        bar += '_';
    }
    
    bar += "]";
    
    return bar;
}

std::string CreateManaBar(int current, int max, int barWidth) {
    if (max <= 0) return std::string(barWidth, '_');
    
    // Calculate percentage of Mana remaining
    double percentage = static_cast<double>(current) / static_cast<double>(max);
    int filledBars = static_cast<int>(percentage * barWidth);
    filledBars = (filledBars < 0) ? 0 : (filledBars > barWidth) ? barWidth : filledBars;
    
    std::string bar = "[";
    
    SetConsoleColor(GREEN);
    for (int i = 0; i < filledBars; i++) {
        bar += '=';
    }
    ResetConsoleColor();
    
    for (int i = filledBars; i < barWidth; i++) {
        bar += '_';
    }
    
    bar += "]";
    
    return bar;
}

void DisplayPartyBars(const std::vector<PartyMember>& party) {
    SetConsoleColor(YELLOW);
    std::cout << "========== PARTY STATUS ==========\n";
    ResetConsoleColor();
    
    for (const auto& member : party) {
        if (member.health > 0) {
            std::cout << member.name << " (Lv " << member.level << ")\n";
            
            std::cout << "  HP:   " << member.health << "/" << member.maxHealth << " ";
            std::cout << CreateHPBar(member.health, member.maxHealth) << "\n";
            
            std::cout << "  Mana: " << member.mana << "/" << member.maxMana << " ";
            std::cout << CreateManaBar(member.mana, member.maxMana) << "\n";
        }
        else {
            SetConsoleColor(RED);
            std::cout << member.name << " - DOWNED\n";
            ResetConsoleColor();
        }
    }
    
    SetConsoleColor(YELLOW);
    std::cout << "==================================\n";
    ResetConsoleColor();
}

// Display enemies with HP bars
void DisplayEnemyBars(const std::vector<RegularEnemy>& enemies) {
    SetConsoleColor(RED);
    std::cout << "========== ENEMIES ==========\n";
    ResetConsoleColor();

    for (size_t i = 0; i < enemies.size(); i++) {
        // Only display alive enemies
        if (enemies[i].health > 0) {
            std::cout << "[" << i + 1 << "] " << enemies[i].name << " (Lv " << enemies[i].level << ")\n";
            std::cout << "     HP: " << enemies[i].health << "/" << enemies[i].maxHealth << " ";
            std::cout << CreateHPBar(enemies[i].health, enemies[i].maxHealth) << "\n";
        }
    }
    SetConsoleColor(RED);
    std::cout << "=============================\n";
    ResetConsoleColor();
}

// Side-by-side display of party and enemy bars for battle screen
void DisplayBattleField(const std::vector<PartyMember>& party,
                        const std::vector<RegularEnemy>& enemies) {
    system("cls");

    SetConsoleColor(YELLOW);
    std::cout << "========== PARTY STATUS ==========\n";
    ResetConsoleColor();
    for (const auto& member : party) {
        if (member.health > 0) {
            std::cout << member.name << " (Lv " << member.level << ")\n";
            std::cout << "  HP:   " << member.health << "/" << member.maxHealth << "  ";
            std::cout << CreateHPBar(member.health, member.maxHealth) << "\n";
            std::cout << "  Mana: " << member.mana << "/" << member.maxMana << " ";
            std::cout << CreateManaBar(member.mana, member.maxMana) << "\n";
        }
        else {
            SetConsoleColor(RED);
            std::cout << member.name << " - DOWNED\n";
            ResetConsoleColor();
        }
    }
    SetConsoleColor(RED);
    std::cout << "========== ENEMIES ==========\n";
    ResetConsoleColor();

    for (size_t i = 0; i < enemies.size(); i++) {
        // Only display alive enemies
        if (enemies[i].health > 0) {
            std::cout << "[" << i + 1 << "] " << enemies[i].name << " (Lv " << enemies[i].level << ")\n";
            std::cout << "     HP: " << enemies[i].health << "/" << enemies[i].maxHealth << " ";
            std::cout << CreateHPBar(enemies[i].health, enemies[i].maxHealth) << "\n";
        }
    }

    std::cout << "\n";
}

// Menu selector with arrow navigation and party status display
int DisplayMenuSelector(const std::vector<std::string>& options, 
                        const std::vector<PartyMember>& party,
                        const std::vector<RegularEnemy>& enemies,
                        const std::string& menuTitle) {
    if (options.empty()) return -1;
    
    int selectedIndex = 0;
    bool selecting = true;
    
    while (selecting) {
        DisplayBattleField(party, enemies);
        
        // Display menu title if provided
        if (!menuTitle.empty()) {
            SetConsoleColor(YELLOW);
            std::cout << "\n" << menuTitle << "\n";
            ResetConsoleColor();
            std::cout << "================================\n\n";
        }
        
        // Display all options with arrow selector
        for (size_t i = 0; i < options.size(); i++) {
            if (i == selectedIndex) {
                SetConsoleColor(GREEN);
                std::cout << " --> " << options[i] << "\n";
                ResetConsoleColor();
            }
            else {
                std::cout << "     " << options[i] << "\n";
            }
        }
        
        std::cout << "\n================================\n";
        std::cout << "Use UP/DOWN arrows to select, ENTER to confirm\n";
        
        // Get keyboard input
        int key = _getch();
        
        // Handle arrow keys (extended keys start with 224)
        if (key == 224) {
            int arrowKey = _getch();
            
            if (arrowKey == 72) {  // UP arrow
                selectedIndex = (selectedIndex - 1 + static_cast<int>(options.size())) % options.size();
            }
            else if (arrowKey == 80) {  // DOWN arrow
                selectedIndex = (selectedIndex + 1) % options.size();
            }
        }
        else if (key == 13) {  // ENTER key
            selecting = false;
        }
    }
    
    return selectedIndex;
}

// Target selector for choosing an enemy
int DisplayEnemyTargetSelector(const std::vector<RegularEnemy>& enemies,
                               const std::vector<PartyMember>& party,
                               const std::string& characterName) {
    if (enemies.empty()) return -1;
    
    int selectedIndex = 0;
    bool selecting = true;
    
    while (selecting) {
        system("cls");

        DisplayBattleField(party, enemies);

        SetConsoleColor(YELLOW);
        std::cout << "Select a target for " << characterName << ":\n";
        ResetConsoleColor();
        std::cout << "================================\n\n";

        // Display only alive enemies with selector
        int displayCount = 0;
        for (size_t i = 0; i < enemies.size(); i++) {
            if (enemies[i].health > 0) {  // Only show alive enemies
                if (displayCount == selectedIndex) {
                    SetConsoleColor(GREEN);
                    std::cout << " --> [" << i + 1 << "] " << enemies[i].name;
                    std::cout << " - HP: " << enemies[i].health << "/" << enemies[i].maxHealth << "\n";
                    ResetConsoleColor();
                }
                else {
                    std::cout << "     [" << i + 1 << "] " << enemies[i].name;
                    std::cout << " - HP: " << enemies[i].health << "/" << enemies[i].maxHealth << "\n";
                }
                displayCount++;
            }
        }

        std::cout << "\n================================\n";
        std::cout << "Use UP/DOWN arrows to select, ENTER to confirm\n";

        // Get keyboard input
        int key = _getch();

        // Handle arrow keys (extended keys start with 224)
        if (key == 224) {
            int arrowKey = _getch();

            // Count alive enemies
            int aliveCount = 0;
            for (const auto& enemy : enemies) {
                if (enemy.health > 0) aliveCount++;
            }

            if (arrowKey == 72) {  // UP arrow
                selectedIndex = (selectedIndex - 1 + aliveCount) % aliveCount;
            }
            else if (arrowKey == 80) {  // DOWN arrow
                selectedIndex = (selectedIndex + 1) % aliveCount;
            }
        }
        else if (key == 13) {  // ENTER key
            selecting = false;
        }
    }

    // Convert display index back to actual enemy index
    int displayCount = 0;
    for (size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i].health > 0) {
            if (displayCount == selectedIndex) {
                return static_cast<int>(i);
            }
            displayCount++;
        }
    }

    return 0;  // Fallback
}

