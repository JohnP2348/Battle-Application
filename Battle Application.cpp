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
    
    cout << "Battle started!\n";
    for (size_t i = 0; i < enemies.size(); i++) {
        cout << enemies[i].name << " appeared!\n";
    }
    cout << "\nPress ENTER to begin...\n";
    cin.get();
    
    BattleHandler battleHandler(party, enemies);
    bool battleInProgress = true;

    while (battleInProgress) {
        // Main battle menu - shown after each round
        vector<string> battleMenu = { "Fight", "Flee", "Status" };
        int battleChoice = DisplayMenuSelector(battleMenu, party, enemies, "=== BATTLE ===");

        if (battleChoice == 0) {  // Fight - Execute one round
            battleHandler.ExecuteRound();
            
            // Check if battle is over after this round
            if (battleHandler.IsBattleOver()) {
                system("cls");
                if (battleHandler.HasPlayerWon()) {
                    cout << "=== VICTORY! ===\n";
                    cout << "You defeated all enemies!\n";
                }
                else {
                    cout << "=== DEFEAT! ===\n";
                    cout << "Your party was defeated!\n";
                }
                cout << "Press ENTER to continue...\n";
                cin.get();
                battleInProgress = false;
            }
        }
        else if (battleChoice == 1) {  // Flee
            system("cls");
            cout << "Party attempts to escape!\n";
            
            // Simple escape logic based on average party speed vs enemy speed
            int partySpeed = 0, enemySpeed = 0;
            for (const auto& member : party) {
                if (member.health > 0) partySpeed += member.speed;
            }
            for (const auto& enemy : enemies) {
                if (enemy.health > 0) enemySpeed += enemy.speed;
            }
            
            bool escapeSuccess = partySpeed > enemySpeed;
            
            if (escapeSuccess) {
                cout << "Successfully fled from battle!\n";
                cout << "Press ENTER to continue...\n";
                cin.get();
                battleInProgress = false;
            }
            else {
                cout << "Escape failed! The enemy blocks your path!\n";
                cout << "Press ENTER to continue...\n";
                cin.get();
                
                // ENEMY COUNTER-ATTACK after failed escape
                // Only enemies attack, not party
                cout << "\nThe enemy counter-attacks!\n";
                cout << "Press ENTER to continue...\n";
                cin.get();
                
                battleHandler.GetEnemyActions();
                
                // Display enemy attack summary
                system("cls");
                cout << "=== ENEMY COUNTER-ATTACK ===\n\n";
                cout << "The enemies are attacking!\n";
                cout << "\nPress ENTER to execute...\n";
                cin.get();

                // Execute only the enemy actions (not a full round)
                system("cls");
                DisplayBattleField(party, enemies);
                cout << "=== COUNTER-ATTACK ===\n";
                cout << "\nPress ENTER to see the attacks...\n";
                cin.get();
                
                // Execute enemy attacks by calling a helper that processes just enemy actions
                battleHandler.ExecuteEnemyAttacks();
                
                // Check if battle is over
                if (battleHandler.IsBattleOver()) {
                    system("cls");
                    if (battleHandler.HasPlayerWon()) {
                        cout << "=== VICTORY! ===\n";
                        cout << "You defeated all enemies!\n";
                    }
                    else {
                        cout << "=== DEFEAT! ===\n";
                        cout << "Your party was defeated!\n";
                    }
                    cout << "Press ENTER to continue...\n";
                    cin.get();
                    battleInProgress = false;
                }
            }
        }
        else if (battleChoice == 2) {  // Status
            system("cls");
            DisplayBattleField(party, enemies);
            cout << "\n=== DETAILED STATUS ===\n\n";
            
            cout << "PARTY:\n";
            for (const auto& member : party) {
                cout << "\n" << member.name << " (Lv " << member.level << " - " << member.charClass << ")\n";
                cout << "HP: " << member.health << "/" << member.maxHealth << "\n";
                cout << "Mana: " << member.mana << "/" << member.maxMana << "\n";
                cout << "Strength: " << member.strength << " | Defense: " << member.defense << "\n";
                cout << "Speed: " << member.speed << " | Experience: " << member.experience << "\n";
            }
            
            cout << "\n\nENEMIES:\n";
            for (size_t i = 0; i < enemies.size(); i++) {
                if (enemies[i].health > 0) {
                    cout << "\n[" << i + 1 << "] " << enemies[i].name << " (Lv " << enemies[i].level << ")\n";
                    cout << "HP: " << enemies[i].health << "/" << enemies[i].maxHealth << "\n";
                    cout << "Attack: " << enemies[i].attack << " | Defense: " << enemies[i].defense << "\n";
                    cout << "Speed: " << enemies[i].speed << "\n";
                }
                else {
                    cout << "\n[" << i + 1 << "] " << enemies[i].name << " - DOWNED\n";
                }
            }
            
            cout << "\nPress ENTER to return to battle menu...\n";
            cin.get();
        }
    }

    return 0;
}