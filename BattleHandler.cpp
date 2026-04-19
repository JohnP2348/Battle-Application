#include "BattleHandler.h"
#include "DisplayUI.h"
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

BattleHandler::BattleHandler(std::vector<PartyMember>& playerParty, std::vector<RegularEnemy>& enemyParty)
    : party(playerParty), enemies(enemyParty) {
    partyDefending.resize(party.size(), false);
    enemiesDefending.resize(enemies.size(), false);
}

// Get list of alive enemy indices
std::vector<int> BattleHandler::GetAliveEnemyIndices() const {
    std::vector<int> aliveEnemies;
    for (size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i].health > 0) {
            aliveEnemies.push_back(static_cast<int>(i));
        }
    }
    return aliveEnemies;
}

void BattleHandler::GetPlayerActions() {
    vector<string> commands = { "Attack", "Ability", "Magic", "Item", "Defend" };
    
    // Reset defending flags for this turn
    fill(partyDefending.begin(), partyDefending.end(), false);

    for (size_t i = 0; i < party.size(); i++) {
        // Skip dead party members
        if (party[i].health <= 0) continue;

        bool actionSelected = false;

        while (!actionSelected) {
            int choice = DisplayMenuSelector(commands, party, enemies,
                                              party[i].name + "'s turn - Choose an action:");

            // If they chose Attack, have them select a target
            if (choice == 0) {  // Attack
                std::vector<int> aliveEnemies = GetAliveEnemyIndices();
                
                if (aliveEnemies.empty()) {
                    cout << "No alive enemies to attack!\n";
                    cout << "Press ENTER to continue...\n";
                    cin.get();
                    continue;
                }

                int targetIndex = DisplayEnemyTargetSelector(enemies, party, party[i].name);
                
                // If target died before this character acts, defend instead
                if (enemies[targetIndex].health <= 0) {
                    BattleAction action;
                    action.actorIndex = static_cast<int>(i);
                    action.actionType = 4;  // Defend
                    action.targetIndex = -1;
                    action.actionName = "Defend";
                    action.isDefending = true;

                    turnActions.push_back(action);
                    partyDefending[i] = true;

                    system("cls");
                    cout << party[i].name << " will defend this turn!\n";
                    cout << "Press ENTER to continue...\n";
                    cin.get();

                    actionSelected = true;
                    continue;
                }

                BattleAction action;
                action.actorIndex = static_cast<int>(i);
                action.actionType = 0;  // Attack
                action.targetIndex = targetIndex;
                action.actionName = "Attack";
                action.isDefending = false;

                turnActions.push_back(action);

                system("cls");
                cout << party[i].name << " will attack " << enemies[targetIndex].name << "!\n";
                cout << "Press ENTER to continue...\n";
                cin.get();

                actionSelected = true;
            }
            else if (choice == 4) {  // Defend
                BattleAction action;
                action.actorIndex = static_cast<int>(i);
                action.actionType = 4;  // Defend
                action.targetIndex = -1;
                action.actionName = "Defend";
                action.isDefending = true;

                turnActions.push_back(action);
                partyDefending[i] = true;

                system("cls");
                cout << party[i].name << " will defend this turn!\n";
                cout << "Press ENTER to continue...\n";
                cin.get();

                actionSelected = true;
            }
            else {
                // For other actions, store the action
                BattleAction action;
                action.actorIndex = static_cast<int>(i);
                action.actionType = choice;
                action.targetIndex = -1;  // No specific target for now
                action.actionName = commands[choice];
                action.isDefending = false;

                turnActions.push_back(action);

                system("cls");
                cout << party[i].name << " will use " << commands[choice] << "!\n";
                cout << "Press ENTER to continue...\n";
                cin.get();

                actionSelected = true;
            }
        }
    }
}

void BattleHandler::GetEnemyActions() {
    random_device rd;
    mt19937 gen(rd());
    
    // Reset defending flags for this turn
    fill(enemiesDefending.begin(), enemiesDefending.end(), false);

    for (size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i].health <= 0) continue;  // Skip dead enemies

        // Simple AI: 80% chance to attack, 20% chance to defend
        uniform_int_distribution<> aiDist(0, 100);
        int aiRoll = aiDist(gen);

        if (aiRoll <= 80) {
            // Attack
            uniform_int_distribution<> targetDist(0, static_cast<int>(party.size()) - 1);
            int target = targetDist(gen);

            // Skip if target is dead
            while (target < static_cast<int>(party.size()) && party[target].health <= 0) {
                target = targetDist(gen);
            }

            BattleAction action;
            action.actorIndex = static_cast<int>(party.size()) + static_cast<int>(i);
            action.actionType = 0;  // Attack
            action.targetIndex = target;
            action.actionName = "Attack";
            action.isDefending = false;

            turnActions.push_back(action);
        }
        else {
            // Defend
            BattleAction action;
            action.actorIndex = static_cast<int>(party.size()) + static_cast<int>(i);
            action.actionType = 4;  // Defend
            action.targetIndex = -1;
            action.actionName = "Defend";
            action.isDefending = true;

            turnActions.push_back(action);
            enemiesDefending[i] = true;
        }
    }
}

void BattleHandler::ApplyDamage(int& targetHealth, int maxHealth, int damage, bool isDefending) {
    if (isDefending) {
        damage = damage / 2;  // Defending halves damage
    }
    damage = (damage < 1) ? 1 : damage;
    targetHealth -= damage;
    targetHealth = max(0, targetHealth);
}

bool BattleHandler::IsValidTarget(int targetIndex) {
    if (targetIndex < 0 || targetIndex >= static_cast<int>(enemies.size())) {
        return false;
    }
    return enemies[targetIndex].health > 0;
}

void BattleHandler::ExecuteAction(const BattleAction& action) {
    if (action.actionType == 4) {  // Defend - no visual output needed here
        return;
    }

    if (action.actionType == 0) {  // Attack
        if (action.actorIndex < static_cast<int>(party.size())) {
            // Party member attacking enemy
            if (action.targetIndex >= 0 && action.targetIndex < static_cast<int>(enemies.size())) {
                // Skip if enemy is dead
                if (enemies[action.targetIndex].health <= 0) {
                    cout << party[action.actorIndex].name << " tries to attack, but " 
                         << enemies[action.targetIndex].name << " is already defeated!\n";
                    cout << "Press ENTER to continue...\n";
                    cin.get();
                    return;
                }

                int damage = party[action.actorIndex].strength - (enemies[action.targetIndex].defense / 2);
                damage = (damage < 1) ? 1 : damage;

                bool isEnemyDefending = enemiesDefending[action.targetIndex];
                ApplyDamage(enemies[action.targetIndex].health, enemies[action.targetIndex].maxHealth, damage, isEnemyDefending);

                system("cls");
                cout << party[action.actorIndex].name << " attacks " << enemies[action.targetIndex].name;
                
                if (isEnemyDefending) {
                    cout << " (who was defending)";
                }
                
                cout << " for " << damage << " damage!\n";
                cout << enemies[action.targetIndex].name << " HP: " << enemies[action.targetIndex].health << "/"
                     << enemies[action.targetIndex].maxHealth << "\n";
                
                if (enemies[action.targetIndex].health <= 0) {
                    cout << enemies[action.targetIndex].name << " has been defeated!\n";
                }
                
                cout << "\nPress ENTER to continue...\n";
                cin.get();
            }
        }
        else {
            // Enemy attacking party member
            int enemyIndex = action.actorIndex - static_cast<int>(party.size());
            if (enemyIndex >= 0 && enemyIndex < static_cast<int>(enemies.size())) {
                // Skip if attacker is dead
                if (enemies[enemyIndex].health <= 0) {
                    cout << enemies[enemyIndex].name << " tries to attack, but is already defeated!\n";
                    cout << "Press ENTER to continue...\n";
                    cin.get();
                    return;
                }

                if (action.targetIndex >= 0 && action.targetIndex < static_cast<int>(party.size())) {
                    // Skip if target is dead
                    if (party[action.targetIndex].health <= 0) {
                        cout << enemies[enemyIndex].name << " tries to attack, but " 
                             << party[action.targetIndex].name << " is already defeated!\n";
                        cout << "Press ENTER to continue...\n";
                        cin.get();
                        return;
                    }

                    int damage = enemies[enemyIndex].attack - (party[action.targetIndex].defense / 2);
                    damage = (damage < 1) ? 1 : damage;

                    bool isPartyDefending = partyDefending[action.targetIndex];
                    ApplyDamage(party[action.targetIndex].health, party[action.targetIndex].maxHealth, damage, isPartyDefending);

                    system("cls");
                    cout << enemies[enemyIndex].name << " attacks " << party[action.targetIndex].name;
                    
                    if (isPartyDefending) {
                        cout << " (who was defending)";
                    }
                    
                    cout << " for " << damage << " damage!\n";
                    cout << party[action.targetIndex].name << " HP: " << party[action.targetIndex].health << "/"
                         << party[action.targetIndex].maxHealth << "\n";
                    
                    if (party[action.targetIndex].health <= 0) {
                        cout << party[action.targetIndex].name << " has been defeated!\n";
                    }
                    
                    cout << "\nPress ENTER to continue...\n";
                    cin.get();
                }
            }
        }
    }
}

void BattleHandler::ExecuteRound() {
    // Get actions from all combatants
    GetPlayerActions();
    GetEnemyActions();

    // Display battle summary
    system("cls");
    cout << "=== BATTLE ROUND SUMMARY ===\n\n";
    for (const auto& action : turnActions) {
        if (action.actorIndex < static_cast<int>(party.size())) {
            if (party[action.actorIndex].health > 0) {
                cout << party[action.actorIndex].name << " will " << action.actionName;
                if (action.targetIndex != -1 && action.targetIndex < static_cast<int>(enemies.size())) {
                    cout << " on " << enemies[action.targetIndex].name;
                }
                cout << "\n";
            }
        }
        else {
            int enemyIndex = action.actorIndex - static_cast<int>(party.size());
            if (enemyIndex >= 0 && enemyIndex < static_cast<int>(enemies.size())) {
                if (enemies[enemyIndex].health > 0) {
                    cout << enemies[enemyIndex].name << " will " << action.actionName;
                    if (action.targetIndex >= 0 && action.targetIndex < static_cast<int>(party.size())) {
                        cout << " on " << party[action.targetIndex].name;
                    }
                    cout << "\n";
                }
            }
        }
    }
    cout << "\nPress ENTER to execute actions...\n";
    cin.get();

    // Execute all actions
    for (const auto& action : turnActions) {
        ExecuteAction(action);
    }

    // Clear actions for next turn
    turnActions.clear();
    
    // Reset defending flags
    fill(partyDefending.begin(), partyDefending.end(), false);
    fill(enemiesDefending.begin(), enemiesDefending.end(), false);
}

bool BattleHandler::IsBattleOver() const {
    return HasPlayerWon() || HaveEnemiesWon();
}

bool BattleHandler::HasPlayerWon() const {
    for (const auto& enemy : enemies) {
        if (enemy.health > 0) {
            return false;
        }
    }
    return true;
}

bool BattleHandler::HaveEnemiesWon() const {
    for (const auto& member : party) {
        if (member.health > 0) {
            return false;
        }
    }
    return true;
}

void BattleHandler::DisplayBattleState() const {
    system("cls");
    DisplayBattleField(party, enemies);
}

