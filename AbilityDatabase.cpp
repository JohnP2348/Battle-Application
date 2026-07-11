#include "AbilityDatabase.h"
#include <algorithm>

using namespace std;

AbilityDatabase::AbilityDatabase() {
    InitializeAbilities();
}

void AbilityDatabase::InitializeAbilities() {
    // ===== OFFENSIVE ABILITIES =====

    // Shield Bash - Related to shields
    Ability shieldBash;
    shieldBash.id = 1;
    shieldBash.name = "Shield Bash";
    shieldBash.description = "Strike with your shield";
    shieldBash.type = Ability::AbilityType::OFFENSIVE;
    shieldBash.target = Ability::TargetType::SINGLE_ENEMY;
    shieldBash.basePower = 12.0f;
    shieldBash.fatigueCost = 5.0f;
    shieldBash.strengthScale = 0.7f;
    shieldBash.defenseScale = 0.3f;
    shieldBash.speedScale = 0.0f;
    shieldBash.healthScale = 0.0f;
    shieldBash.canCrit = true;
    shieldBash.canMiss = false;
    shieldBash.ignoreDefense = false;
    
    shieldBash.hasUnleash = true;
	// each unleash effect is tied to the related shield. We will check the shield equipped when using this ability to determine which unleash can trigger
	shieldBash.useUnleash = {};  // This ability can trigger unleash effects based on the equipped shield
    abilities.push_back(shieldBash);

    // Slash - Related to swords
    Ability slash;
    slash.id = 2;
    slash.name = "Slash";
    slash.description = "A quick slashing attack";
    slash.type = Ability::AbilityType::OFFENSIVE;
    slash.target = Ability::TargetType::SINGLE_ENEMY;
    slash.basePower = 10.0f;
    slash.fatigueCost = 4.0f;
    slash.strengthScale = 0.8f;
    slash.defenseScale = 0.0f;
    slash.speedScale = 0.2f;
    slash.healthScale = 0.0f;
    slash.canCrit = true;
    slash.canMiss = false;
    slash.ignoreDefense = false;
    slash.relatedWeaponId = 2;
    slash.hasUnleash = true;
	slash.useUnleash = {};  // This ability can trigger unleash effects based on the equipped sword
    abilities.push_back(slash);

    // Power Strike - Related to Excalibur
    Ability powerStrike;
    powerStrike.id = 3;
    powerStrike.name = "Power Strike";
    powerStrike.description = "A powerful overhead strike";
    powerStrike.type = Ability::AbilityType::OFFENSIVE;
    powerStrike.target = Ability::TargetType::SINGLE_ENEMY;
    powerStrike.basePower = 22.0f;
    powerStrike.fatigueCost = 15.0f;
    powerStrike.strengthScale = 1.2f;
    powerStrike.defenseScale = 0.0f;
    powerStrike.speedScale = 0.1f;
    powerStrike.healthScale = 0.0f;
    powerStrike.canCrit = true;
    powerStrike.canMiss = false;
    powerStrike.ignoreDefense = false;
    powerStrike.relatedWeaponId = 3;
    powerStrike.hasUnleash = true;
	powerStrike.useUnleash = {};  // This ability can trigger unleash effects based on the equipped sword (Excalibur)
   
    abilities.push_back(powerStrike);

    // ===== DEFENSIVE ABILITIES =====

    // Reinforce - Related to Golden Sun Shield
    Ability reinforce;
    reinforce.id = 4;
    reinforce.name = "Reinforce";
    reinforce.description = "Raise shield and protect nearby allies";
    reinforce.type =  Ability::AbilityType::DEFENSIVE;
    reinforce.target = Ability::TargetType::ADJACENT_ALLIES;
    reinforce.basePower = 0.0f;
    reinforce.fatigueCost = 8.0f;
    reinforce.strengthScale = 0.0f;
    reinforce.defenseScale = 1.0f;
    reinforce.speedScale = 0.0f;
    reinforce.healthScale = 0.2f;
    reinforce.canCrit = false;
    reinforce.canMiss = false;
    reinforce.ignoreDefense = false;
    reinforce.adjacentBuffModifier = 0.6f;
    reinforce.relatedShieldId = 4;
    reinforce.hasUnleash = true;
    reinforce.commonUnleash = {"Reinforce", "Shields up!", 3, 0.1f, 0.12f};
    reinforce.rareUnleash = {"Megiddo Stance", "A defensive golden stance!", 8, 0.4f, 0.22f};
    reinforce.mythicalUnleash = {"Divine Protection", "Protected by divine light!", 12, 0.6f, 0.32f};
    abilities.push_back(reinforce);

    // Parry - Related to Aegis Shield
    Ability parry;
    parry.id = 5;
    parry.name = "Parry";
    parry.description = "Prepare to dodge the next attack";
    parry.type = AbilityType::DEFENSIVE;
    parry.target = TargetType::SELF;
    parry.basePower = 0.0f;
    parry.fatigueCost = 3.0f;
    parry.strengthScale = 0.0f;
    parry.defenseScale = 0.8f;
    parry.speedScale = 0.2f;
    parry.healthScale = 0.0f;
    parry.canCrit = false;
    parry.canMiss = false;
    parry.ignoreDefense = false;
    parry.relatedShieldId = 5;
    parry.hasUnleash = true;
    parry.commonUnleash = {"Parry", "Ready stance", 2, 0.0f, 0.15f};
    parry.rareUnleash = {"Golden Counter", "Parry with golden light!", 5, 0.2f, 0.25f};
    parry.mythicalUnleash = {"Aegis Barrier", "An impenetrable barrier!", 10, 0.4f, 0.35f};
    abilities.push_back(parry);

    // ===== TACTICAL ABILITIES =====

    // Quick Strike - Related to Lightbringer
    Ability quickStrike;
    quickStrike.id = 6;
    quickStrike.name = "Quick Strike";
    quickStrike.description = "A fast attack";
    quickStrike.type = AbilityType::TACTICAL;
    quickStrike.target = TargetType::SINGLE_ENEMY;
    quickStrike.basePower = 8.0f;
    quickStrike.fatigueCost = 2.0f;
    quickStrike.strengthScale = 0.5f;
    quickStrike.defenseScale = 0.0f;
    quickStrike.speedScale = 0.9f;
    quickStrike.healthScale = 0.0f;
    quickStrike.canCrit = true;
    quickStrike.canMiss = true;
    quickStrike.ignoreDefense = false;
    quickStrike.relatedWeaponId = 2;
    quickStrike.hasUnleash = true;
    quickStrike.commonUnleash = {"Quick Strike", "A fast slash", 2, 0.0f, 0.18f};
    quickStrike.rareUnleash = {"Sonic Blade", "Speed becomes a weapon!", 8, 0.2f, 0.28f};
    quickStrike.mythicalUnleash = {"Twilight Assault", "Speed transcendent!", 15, 0.4f, 0.38f};
    abilities.push_back(quickStrike);

    // Reckless Attack - Related to Excalibur
    Ability recklessAttack;
    recklessAttack.id = 7;
    recklessAttack.name = "Reckless Attack";
    recklessAttack.description = "Attack with wild abandon";
    recklessAttack.type = AbilityType::OFFENSIVE;
    recklessAttack.target = TargetType::SINGLE_ENEMY;
    recklessAttack.basePower = 30.0f;
    recklessAttack.fatigueCost = 18.0f;
    recklessAttack.strengthScale = 1.5f;
    recklessAttack.defenseScale = -0.3f;
    recklessAttack.speedScale = 0.0f;
    recklessAttack.healthScale = 0.0f;
    recklessAttack.canCrit = true;
    recklessAttack.canMiss = false;
    recklessAttack.ignoreDefense = false;
    recklessAttack.relatedWeaponId = 3;
    recklessAttack.hasUnleash = true;
    recklessAttack.commonUnleash = {"Reckless Attack", "Chaotic power", 10, 0.0f, 0.08f};
    recklessAttack.rareUnleash = {"Infernal Rage", "Rage turns to flames!", 20, 0.3f, 0.15f};
    recklessAttack.mythicalUnleash = {"Chaos Unleashed", "Pure chaos incarnate!", 40, 0.5f, 0.25f};
    abilities.push_back(recklessAttack);
}

const Ability* AbilityDatabase::GetAbility(int abilityId) const {
    auto it = find_if(abilities.begin(), abilities.end(),
                     [abilityId](const Ability& a) { return a.id == abilityId; });
    return it != abilities.end() ? &(*it) : nullptr;
}

const vector<Ability>& AbilityDatabase::GetAllAbilities() const {
    return abilities;
}

vector<Ability> AbilityDatabase::GetAbilitiesByClass(const string& className) {
    vector<Ability> classAbilities;

    if (className == "Warrior") {
        classAbilities.push_back(abilities[0]);  // Shield Bash
        classAbilities.push_back(abilities[1]);  // Slash
        classAbilities.push_back(abilities[2]);  // Power Strike
        classAbilities.push_back(abilities[6]);  // Quick Strike
        classAbilities.push_back(abilities[7]);  // Reckless Attack
    }
    else if (className == "Paladin") {
        classAbilities.push_back(abilities[0]);  // Shield Bash
        classAbilities.push_back(abilities[1]);  // Slash
        classAbilities.push_back(abilities[3]);  // Reinforce
        classAbilities.push_back(abilities[4]);  // Parry
    }
    else if (className == "Rogue") {
        classAbilities.push_back(abilities[1]);  // Slash
        classAbilities.push_back(abilities[2]);  // Power Strike
        classAbilities.push_back(abilities[6]);  // Quick Strike
    }

    return classAbilities;
}