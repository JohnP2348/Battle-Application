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
        // Skip downed party members completely - don't even ask them
        if (party[i].health <= 0) {
            party[i].health = 0;  // Clamp to 0 if negative
            continue;
        }

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
                
                // Ensure target is valid and alive
                if (targetIndex < 0 || targetIndex >= static_cast<int>(enemies.size())) {
                    cout << "Invalid target!\n";
                    cout << "Press ENTER to continue...\n";
                    cin.get();
                    continue;
                }

                // If target died before this character acts, auto-defend (silently add action)
                if (enemies[targetIndex].health <= 0) {
                    enemies[targetIndex].health = 0;  // Clamp to 0
                    
                    BattleAction action;
                    action.actorIndex = static_cast<int>(i);
                    action.actionType = 4;  // Defend
                    action.targetIndex = -1;
                    action.actionName = "Defend";
                    action.isDefending = true;

                    turnActions.push_back(action);
                    partyDefending[i] = true;

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
                cout << party[i].name << " is defending this turn!\n";
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
        // Skip downed enemies - don't even ask for actions
        if (enemies[i].health <= 0) {
            enemies[i].health = 0;  // Clamp to 0 if negative
            continue;
        }

        // Simple AI: 80% chance to attack, 20% chance to defend
        uniform_int_distribution<> aiDist(0, 100);
        int aiRoll = aiDist(gen);

        if (aiRoll <= 80) {
            // Attack - find alive party member
            vector<int> aliveParty;
            for (size_t j = 0; j < party.size(); j++) {
                if (party[j].health > 0) {
                    aliveParty.push_back(static_cast<int>(j));
                }
            }

            if (aliveParty.empty()) continue;  // No alive targets

            uniform_int_distribution<> targetDist(0, static_cast<int>(aliveParty.size()) - 1);
            int targetIndex = aliveParty[targetDist(gen)];

            BattleAction action;
            action.actorIndex = static_cast<int>(party.size()) + static_cast<int>(i);
            action.actionType = 0;  // Attack
            action.targetIndex = targetIndex;
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
    
    // CLAMP to 0 - never allow negative HP
    if (targetHealth < 0) {
        targetHealth = 0;
    }
}

bool BattleHandler::IsValidTarget(int targetIndex) {
    if (targetIndex < 0 || targetIndex >= static_cast<int>(enemies.size())) {
        return false;
    }
    return enemies[targetIndex].health > 0;
}

void BattleHandler::ExecuteAction(const BattleAction& action) {
    if (action.actionType == 4) {  // Defend - show message and display updated bars
        if (action.actorIndex < static_cast<int>(party.size())) {
            // Party member defending
            system("cls");
            DisplayBattleField(party, enemies);
            cout << party[action.actorIndex].name << " defends!\n";
            cout << "\nPress ENTER to continue...\n";
            cin.get();
        }
        else {
            // Enemy defending
            int enemyIndex = action.actorIndex - static_cast<int>(party.size());
            if (enemyIndex >= 0 && enemyIndex < static_cast<int>(enemies.size())) {
                system("cls");
                DisplayBattleField(party, enemies);
                cout << enemies[enemyIndex].name << " defends!\n";
                cout << "\nPress ENTER to continue...\n";
                cin.get();
            }
        }
        return;
    }

    if (action.actionType == 0) {  // Attack
        if (action.actorIndex < static_cast<int>(party.size())) {
            // Party member attacking enemy
            if (action.targetIndex >= 0 && action.targetIndex < static_cast<int>(enemies.size())) {
                // Skip if enemy is dead
                if (enemies[action.targetIndex].health <= 0) {
                    enemies[action.targetIndex].health = 0;  // Clamp to 0
                    return;  // Silently skip - no message
                }

                int damage = party[action.actorIndex].strength - (enemies[action.targetIndex].defense / 2);
                damage = (damage < 1) ? 1 : damage;

                bool isEnemyDefending = enemiesDefending[action.targetIndex];
                ApplyDamage(enemies[action.targetIndex].health, enemies[action.targetIndex].maxHealth, damage, isEnemyDefending);

                system("cls");
                DisplayBattleField(party, enemies);
                cout << party[action.actorIndex].name << " does " << damage << " damage to " << enemies[action.targetIndex].name << "!\n";
                
                if (enemies[action.targetIndex].health <= 0) {
                    enemies[action.targetIndex].health = 0;  // Clamp to 0
                    cout << enemies[action.targetIndex].name << " is downed!\n";
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
                    enemies[enemyIndex].health = 0;  // Clamp to 0
                    return;  // Silently skip - no message
                }

                if (action.targetIndex >= 0 && action.targetIndex < static_cast<int>(party.size())) {
                    // Skip if target is dead
                    if (party[action.targetIndex].health <= 0) {
                        party[action.targetIndex].health = 0;  // Clamp to 0
                        return;  // Silently skip - no message
                    }

                    int damage = enemies[enemyIndex].attack - (party[action.targetIndex].defense / 2);
                    damage = (damage < 1) ? 1 : damage;

                    bool isPartyDefending = partyDefending[action.targetIndex];
                    ApplyDamage(party[action.targetIndex].health, party[action.targetIndex].maxHealth, damage, isPartyDefending);

                    system("cls");
                    DisplayBattleField(party, enemies);
                    cout << enemies[enemyIndex].name << " does " << damage << " damage to " << party[action.targetIndex].name << "!\n";
                    
                    if (party[action.targetIndex].health <= 0) {
                        party[action.targetIndex].health = 0;  // Clamp to 0
                        cout << party[action.targetIndex].name << " is downed!\n";
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

void BattleHandler::ExecuteEnemyAttacks() {
    // Execute all collected actions (should only be enemy actions)
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

