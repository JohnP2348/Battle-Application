#include <iostream>
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
        
        std::cout << "\n";
    }
    
    SetConsoleColor(YELLOW);
    std::cout << "==================================\n";
    ResetConsoleColor();
}