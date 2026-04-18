#pragma once
#include <vector>
#include <string>
#include "PartyMember.h"
#include "Enemies.h"

struct BattleAction {
    int actorIndex;          // Index of who's performing the action
    int actionType;          // 0=Attack, 1=Ability, 2=Magic, 3=Item, 4=Defend
    int targetIndex;         // Index of the target
    std::string actionName;
};

struct BattleTurn {
    std::vector<BattleAction> partyActions;
    std::vector<BattleAction> enemyActions;
};

class BattleHandler {
private:
    std::vector<PartyMember>& party;
    std::vector<RegularEnemy>& enemies;
    std::vector<BattleAction> turnActions;

    // Private helper method
    void ExecuteAttack(const BattleAction& action);

public:
    // Constructor
    BattleHandler(std::vector<PartyMember>& playerParty, std::vector<RegularEnemy>& enemyParty);

    // Get player actions
    void GetPlayerActions();

    // Get enemy AI actions
    void GetEnemyActions();

    // Execute all actions for the current turn
    void ExecuteTurn();

    // Check if battle is over
    bool IsBattleOver() const;

    // Check if player won
    bool HasPlayerWon() const;

    // Check if enemies won
    bool HaveEnemiesWon() const;

    // Display battle state
    void DisplayBattleState() const;

    // Run full battle loop
    void RunBattle();
};