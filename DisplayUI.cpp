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
    if (max <= 0) return std::string(barWidth, '-');
    
    int filledWidth = static_cast<int>((static_cast<double>(current) / max) * barWidth);
    filledWidth = (filledWidth < 0) ? 0 : (filledWidth > barWidth) ? barWidth : filledWidth;
    
    std::string bar = "[";
    
    SetConsoleColor(BLUE);
    bar += std::string(filledWidth, '=');
    
    SetConsoleColor(RED);
    bar += std::string(barWidth - filledWidth, '=');
    
    ResetConsoleColor();
    bar += "]";
    
    return bar;
}

std::string CreateManaBar(int current, int max, int barWidth) {
    if (max <= 0) return std::string(barWidth, '-');
    
    int filledWidth = static_cast<int>((static_cast<double>(current) / max) * barWidth);
    filledWidth = (filledWidth < 0) ? 0 : (filledWidth > barWidth) ? barWidth : filledWidth;
    
    std::string bar = "[";
    
    SetConsoleColor(GREEN);
    bar += std::string(filledWidth, '=');
    
    SetConsoleColor(GRAY);
    bar += std::string(barWidth - filledWidth, '=');
    
    ResetConsoleColor();
    bar += "]";
    
    return bar;
}

void DisplayPartyBars(const std::vector<PartyMember>& party) {
    SetConsoleColor(YELLOW);
    std::cout << "\n========== PARTY STATUS ==========\n";
    ResetConsoleColor();
    
    for (const auto& member : party) {
        std::cout << member.name << " (Lv " << member.level << ")\n";
        
        std::cout << "  HP:   " << member.health << "/" << member.maxHealth << " ";
        std::cout << CreateHPBar(member.health, member.maxHealth) << "\n";
        
        std::cout << "  Mana: " << member.mana << "/" << member.maxMana << " ";
        std::cout << CreateManaBar(member.mana, member.maxMana) << "\n";
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
        std::cout << "[" << i + 1 << "] " << enemies[i].name << " (Lv " << enemies[i].level << ")\n";
        std::cout << "     HP: " << enemies[i].health << "/" << enemies[i].maxHealth << " ";
        std::cout << CreateHPBar(enemies[i].health, enemies[i].maxHealth) << "\n";
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
        std::cout << member.name << " (Lv " << member.level << ")\n";
        std::cout << "  HP:   " << member.health << "/" << member.maxHealth << "  ";
        std::cout << CreateHPBar(member.health, member.maxHealth) << "\n";
        std::cout << "  Mana: " << member.mana << "/" << member.maxMana << " ";
        std::cout << CreateManaBar(member.mana, member.maxMana) << "\n";
    }
    SetConsoleColor(RED);
    std::cout << "========== ENEMIES ==========\n";
    ResetConsoleColor();

    for (size_t i = 0; i < enemies.size(); i++) {
        std::cout << "[" << i + 1 << "] " << enemies[i].name << " (Lv " << enemies[i].level << ")\n";
        std::cout << "     HP: " << enemies[i].health << "/" << enemies[i].maxHealth << " ";
        std::cout << CreateHPBar(enemies[i].health, enemies[i].maxHealth) << "\n";
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

        // Display enemies with selector
        for (size_t i = 0; i < enemies.size(); i++) {
            if (i == selectedIndex) {
                SetConsoleColor(GREEN);
                std::cout << " --> [" << i + 1 << "] " << enemies[i].name;
                std::cout << " - HP: " << enemies[i].health << "/" << enemies[i].maxHealth << "\n";
                ResetConsoleColor();
            }
            else {
                std::cout << "     [" << i + 1 << "] " << enemies[i].name;
                std::cout << " - HP: " << enemies[i].health << "/" << enemies[i].maxHealth << "\n";
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
                selectedIndex = (selectedIndex - 1 + static_cast<int>(enemies.size())) % static_cast<int>(enemies.size());
            }
            else if (arrowKey == 80) {  // DOWN arrow
                selectedIndex = (selectedIndex + 1) % static_cast<int>(enemies.size());
            }
        }
        else if (key == 13) {  // ENTER key
            selecting = false;
        }
    }

    return selectedIndex;
}

