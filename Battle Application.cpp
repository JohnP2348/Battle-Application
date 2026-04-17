#include <iostream>
#include <string>
#include <vector>
#include "PartyMember.h"
#include "Enemies.h"
#include <random>
#include <algorithm>
#include "DisplayUI.h"
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
    
    cout << "Battle started!\n";
    for (size_t i = 0; i < enemies.size(); i++) {
        cout << enemies[i].name << " appeared!\n";
    }
    cout << "\n";
    
    // Main battle menu with selector - now shows party and enemies
    vector<string> battleMenu = { "Fight", "Flee", "Status" };
    int battleChoice = DisplayMenuSelector(battleMenu, party, enemies, "=== BATTLE ===");
    
    if (battleChoice == 0) {  // Fight
        cout << "You have chosen to fight!\n";
        
        vector<string> commands = { "Attack", "Ability", "Magic", "Item", "Defend" };
        vector<int> chosenCommands(party.size());
        vector<int> chosenTargets(party.size(), -1);  // Store target for each party member
        
        for (size_t i = 0; i < party.size(); i++) {
            bool actionSelected = false;
            
            while (!actionSelected) {
                int choice = DisplayMenuSelector(commands, party, enemies,
                                                  party[i].name + "'s turn - Choose an action:");
                chosenCommands[i] = choice;
                
                // If they chose Attack, have them select a target
                if (choice == 0) {  // Attack
                    int targetIndex = DisplayEnemyTargetSelector(enemies, party, party[i].name);
                    chosenTargets[i] = targetIndex;
                    
                    system("cls");
                    cout << party[i].name << " will attack " << enemies[targetIndex].name << "!\n";
                    cout << "Press ENTER to continue...\n";
                    cin.get();
                    
                    actionSelected = true;
                }
                else {
                    // For other actions, just confirm the choice
                    system("cls");
                    cout << party[i].name << " will use " << commands[choice] << "!\n";
                    cout << "Press ENTER to continue...\n";
                    cin.get();
                    
                    actionSelected = true;
                }
            }
        }
        
        // Battle round summary
        system("cls");
        cout << "=== BATTLE ROUND SUMMARY ===\n\n";
        for (size_t i = 0; i < party.size(); i++) {
            cout << party[i].name << " will use: " << commands[chosenCommands[i]];
            if (chosenCommands[i] == 0 && chosenTargets[i] != -1) {
                cout << " on " << enemies[chosenTargets[i]].name;
            }
            cout << "\n";
        }
        cout << "\nPress ENTER to begin the round...\n";
        cin.get();
    }
    else if (battleChoice == 1) {  // Flee
        cout << "Party attempts to escape!\n";
        bool escapeSuccess = false;
        
        if (escapeSuccess == true) {
            return 0;
        }
        else {
            cout << "Escape failed! The enemy attacks!\n";
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