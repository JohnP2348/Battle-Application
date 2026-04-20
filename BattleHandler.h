#pragma once
#include <vector>
#include <string>
#include "PartyMember.h"
#include "Enemies.h"

struct BattleAction {
    int actorIndex;          // Index of who's performing the action
    int actionType;          // 0=Attack, 1=Ability, 2=Magic, 3=Item, 4=Defend
    int targetIndex;         // Index of the target (-1 for defend)
    std::string actionName;
    bool isDefending;        // Track if character is defending
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
    std::vector<bool> partyDefending;  // Track who's defending
    std::vector<bool> enemiesDefending;  // Track which enemies are defending

    // Private helper methods
    void ExecuteAction(const BattleAction& action);
    void ApplyDamage(int& targetHealth, int maxHealth, int damage, bool isDefending);
    bool IsValidTarget(int targetIndex);

public:
    // Constructor
    BattleHandler(std::vector<PartyMember>& playerParty, std::vector<RegularEnemy>& enemyParty);

    // Get player actions
    void GetPlayerActions();

    // Get enemy AI actions
    void GetEnemyActions();

    // Execute a single round of combat (get actions and resolve them)
    void ExecuteRound();

    // Execute only enemy attacks (for counter-attacks when escape fails)
    void ExecuteEnemyAttacks();

    // Check if battle is over
    bool IsBattleOver() const;

    // Check if player won
    bool HasPlayerWon() const;

    // Check if enemies won
    bool HaveEnemiesWon() const;

    // Display battle state
    void DisplayBattleState() const;
    
    // Get list of alive enemies for targeting
    std::vector<int> GetAliveEnemyIndices() const;
};