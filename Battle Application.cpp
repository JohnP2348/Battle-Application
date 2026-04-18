#include <iostream>
#include <string>
#include <vector>
#include "PartyMember.h"
#include "Enemies.h"
#include "BattleHandler.h"
#include "DisplayUI.h"
#include <random>

using namespace std;

vector<RegularEnemy> SpawnEnemyParty() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> partySizeDist(1, 100);
    int roll = partySizeDist(gen);
    int numEnemies;
    if (roll <= 40) numEnemies = 2;
    else if (roll <= 70) numEnemies = 1;
    else if (roll <= 90) numEnemies = 3;
    else numEnemies = 4;

    vector<RegularEnemy> enemies;
    uniform_int_distribution<> enemyDist(0, static_cast<int>(regularEnemies.size()) - 1);
    for (int i = 0; i < numEnemies; i++) {
        enemies.push_back(regularEnemies[enemyDist(gen)]);
    }
    return enemies;
}

int main() {
    vector<RegularEnemy> enemies = SpawnEnemyParty();

    // Main battle menu
    vector<string> battleMenu = { "Fight", "Flee", "Status" };
    int battleChoice = DisplayMenuSelector(battleMenu, party, enemies, "=== BATTLE ===");

    if (battleChoice == 0) {  // Fight
        // Create battle handler and run the battle
        BattleHandler battleHandler(party, enemies);
        battleHandler.RunBattle();
    }
    else if (battleChoice == 1) {  // Flee
        cout << "Party attempts to escape!\n";
        bool escapeSuccess = false;

        if (escapeSuccess == true) {
            cout << "Successfully fled from battle!\n";
            return 0;
        }
        else {
            cout << "Escape failed! The enemy attacks!\n";
            BattleHandler battleHandler(party, enemies);
            battleHandler.RunBattle();
        }
    }
    else if (battleChoice == 2) {  // Status
        system("cls");
        DisplayPartyBars(party);
        DisplayEnemyBars(enemies);
        cout << "\nPress ENTER to return to battle...\n";
        cin.get();
    }

    return 0;
}