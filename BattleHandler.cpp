#include "BattleHandler.h"
#include "DisplayUI.h"
#include <iostream>
#include <random>

using namespace std;

BattleHandler::BattleHandler(std::vector<PartyMember>& playerParty, std::vector<RegularEnemy>& enemyParty)
    : party(playerParty), enemies(enemyParty) {}

void BattleHandler::GetPlayerActions() {
    vector<string> commands = { "Attack", "Ability", "Magic", "Item", "Defend" };

    for (size_t i = 0; i < party.size(); i++) {
        bool actionSelected = false;

        while (!actionSelected) {
            int choice = DisplayMenuSelector(commands, party, enemies,
                                              party[i].name + "'s turn - Choose an action:");

            // If they chose Attack, have them select a target
            if (choice == 0) {  // Attack
                int targetIndex = DisplayEnemyTargetSelector(enemies, party, party[i].name);

                BattleAction action;
                action.actorIndex = static_cast<int>(i);
                action.actionType = 0;  // Attack
                action.targetIndex = targetIndex;
                action.actionName = "Attack";

                turnActions.push_back(action);

                system("cls");
                cout << party[i].name << " will attack " << enemies[targetIndex].name << "!\n";
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

    for (size_t i = 0; i < enemies.size(); i++) {
        // Simple AI: enemies always attack random party members
        uniform_int_distribution<> targetDist(0, static_cast<int>(party.size()) - 1);
        int target = targetDist(gen);

        BattleAction action;
        action.actorIndex = static_cast<int>(i);
        action.actionType = 0;  // Attack
        action.targetIndex = target;
        action.actionName = "Attack";

        turnActions.push_back(action);
    }
}

void BattleHandler::ExecuteAttack(const BattleAction& action) {
    if (action.actionType == 0) {  // Attack
        if (action.actorIndex < static_cast<int>(party.size())) {
            // Party member attacking enemy
            if (action.targetIndex >= 0 && action.targetIndex < static_cast<int>(enemies.size())) {
                int damage = party[action.actorIndex].strength - (enemies[action.targetIndex].defense / 2);
                damage = (damage < 1) ? 1 : damage;

                enemies[action.targetIndex].health -= damage;

                system("cls");
                cout << party[action.actorIndex].name << " attacks " << enemies[action.targetIndex].name
                     << " for " << damage << " damage!\n";
                cout << enemies[action.targetIndex].name << " HP: " << enemies[action.targetIndex].health << "/"
                     << enemies[action.targetIndex].maxHealth << "\n";
                cout << "\nPress ENTER to continue...\n";
                cin.get();
            }
        }
        else {
            // Enemy attacking party member
            int enemyIndex = action.actorIndex - static_cast<int>(party.size());
            if (enemyIndex >= 0 && enemyIndex < static_cast<int>(enemies.size())) {
                if (action.targetIndex >= 0 && action.targetIndex < static_cast<int>(party.size())) {
                    int damage = enemies[enemyIndex].attack - (party[action.targetIndex].defense / 2);
                    damage = (damage < 1) ? 1 : damage;

                    party[action.targetIndex].health -= damage;

                    system("cls");
                    cout << enemies[enemyIndex].name << " attacks " << party[action.targetIndex].name
                         << " for " << damage << " damage!\n";
                    cout << party[action.targetIndex].name << " HP: " << party[action.targetIndex].health << "/"
                         << party[action.targetIndex].maxHealth << "\n";
                    cout << "\nPress ENTER to continue...\n";
                    cin.get();
                }
            }
        }
    }
}

void BattleHandler::ExecuteTurn() {
    // Execute all collected actions
    for (const auto& action : turnActions) {
        ExecuteAttack(action);
    }

    // Clear actions for next turn
    turnActions.clear();
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

void BattleHandler::RunBattle() {
    cout << "Battle started!\n";
    for (size_t i = 0; i < enemies.size(); i++) {
        cout << enemies[i].name << " appeared!\n";
    }
    cout << "\nPress ENTER to begin...\n";
    cin.get();

    while (!IsBattleOver()) {
        // Get actions from all combatants
        GetPlayerActions();
        GetEnemyActions();

        // Display battle summary
        system("cls");
        cout << "=== BATTLE ROUND SUMMARY ===\n\n";
        for (const auto& action : turnActions) {
            if (action.actorIndex < static_cast<int>(party.size())) {
                cout << party[action.actorIndex].name << " will " << action.actionName;
                if (action.targetIndex != -1 && action.targetIndex < static_cast<int>(enemies.size())) {
                    cout << " on " << enemies[action.targetIndex].name;
                }
            }
            else {
                int enemyIndex = action.actorIndex - static_cast<int>(party.size());
                if (enemyIndex >= 0 && enemyIndex < static_cast<int>(enemies.size())) {
                    cout << enemies[enemyIndex].name << " will " << action.actionName;
                    if (action.targetIndex >= 0 && action.targetIndex < static_cast<int>(party.size())) {
                        cout << " on " << party[action.targetIndex].name;
                    }
                }
            }
            cout << "\n";
        }
        cout << "\nPress ENTER to execute actions...\n";
        cin.get();

        // Execute the turn
        ExecuteTurn();
    }

    // Battle end
    system("cls");
    if (HasPlayerWon()) {
        cout << "=== VICTORY! ===\n";
        cout << "You defeated all enemies!\n";
    }
    else {
        cout << "=== DEFEAT! ===\n";
        cout << "Your party was defeated!\n";
    }
    cout << "\nPress ENTER to continue...\n";
    cin.get();
}