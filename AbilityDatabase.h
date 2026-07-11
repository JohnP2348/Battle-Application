#pragma once
#include <vector>
#include "Ability.h"

class AbilityDatabase {
private:
    std::vector<Ability> abilities;

public:
    AbilityDatabase();

    // Initialize all abilities
    void InitializeAbilities();

    // Get ability by ID
    const Ability* GetAbility(int abilityId) const;

    // Get all abilities
    const std::vector<Ability>& GetAllAbilities() const;

    // Get abilities for a class
    std::vector<Ability> GetAbilitiesByClass(const std::string& className);
};

