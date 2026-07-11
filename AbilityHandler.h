#pragma once
#include <vector>
#include "Ability.h"
#include "Equipment.h"
#include "AbilityDatabase.h"
#include "PartyMember.h"
#include "Enemies.h"
#include "BattlePosition.h"

struct AbilityResult {
    bool success = false;
    bool unleashTriggered = false;
    std::string unleashName;
    int baseDamage = 0;
    int totalDamage = 0;
    std::string message;
    std::string unleashMessage;
    float fatigueUsed = 0.0f;
    float fatigueEfficiency = 1.0f;
};

class AbilityHandler {
private:
    AbilityDatabase abilityDatabase;
    std::vector<Equipment> equipmentDatabase;
    BattlePositionManager& positionManager;

    // Helper methods
    float CalculateFatigueEfficiency(float availableFatigue, float fatigueNeeded);
    int CalculateStatScaling(const Ability& ability, const PartyMember& user,
                             const Equipment* weapon = nullptr);
    int CalculateAbilityDamage(const Ability& ability, const PartyMember& user,
                               const RegularEnemy& target, float fatigueEfficiency,
                               const Equipment* weapon = nullptr);
    bool CheckUnleash(const Equipment* weapon, const Ability& ability,
                      float fatigueEfficiency);
    bool CheckNormalAttackUnleash(const Equipment* weapon);
    std::string GetUnleashName(const Equipment* weapon, const Ability& ability);
    int GetUnleashBonus(const Equipment* weapon, const Ability& ability);
    bool IsAbilityRelatedToEquipment(const Ability& ability, const Equipment* weapon);

public:
    AbilityHandler(BattlePositionManager& posMgr);

    // Initialize equipment
    void InitializeEquipment();

    // Execute normal attack
    AbilityResult ExecuteNormalAttack(PartyMember& user, RegularEnemy& target,
                                      const Equipment* weapon = nullptr);

    // Execute ability on enemy
    AbilityResult ExecuteAbility(const Ability& ability, PartyMember& user,
                                 RegularEnemy& target, const Equipment* weapon = nullptr);

    // Execute ability on ally
    AbilityResult ExecuteAbilityOnAlly(const Ability& ability, PartyMember& user,
                                       PartyMember& target, const Equipment* weapon = nullptr);

    // Execute proximity ability
    std::vector<AbilityResult> ExecuteAdjacentAbility(const Ability& ability,
                                                       PartyMember& user,
                                                       std::vector<PartyMember>& party,
                                                       const Equipment* weapon = nullptr);

    // Get ability by ID
    const Ability* GetAbility(int abilityId) const;

    // Get equipment by ID
    const Equipment* GetEquipment(int equipmentId) const;

    // Get abilities for character class
    std::vector<Ability> GetAbilitiesByClass(const std::string& className);
};