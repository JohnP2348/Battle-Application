#include "AbilityHandler.h"
#include <cmath>
#include <random>
#include <algorithm>

using namespace std;

AbilityHandler::AbilityHandler(BattlePositionManager& posMgr)
    : positionManager(posMgr) {
    InitializeEquipment();
    // abilityDatabase is automatically initialized in its constructor
}

void AbilityHandler::InitializeEquipment() {
    // COMMON SWORD
    Equipment ironSword(1, "Iron Sword", "A standard sword",
                        EquipmentType::WEAPON, WeaponRarity::COMMON);
    ironSword.strengthBonus = 3;
    ironSword.abilityPowerMultiplier = 1.0f;
    ironSword.unleashChanceBonus = 0.0f;
    ironSword.canUnleashOnNormalAttack = true;
    ironSword.normalAttackUnleashName = "Quick Strike";
    ironSword.normalAttackUnleashBonus = 3;
    equipmentDatabase.push_back(ironSword);

    // RARE SWORD - Lightbringer
    Equipment lightbringer(2, "Lightbringer", "A swift blade of justice",
                           EquipmentType::WEAPON, WeaponRarity::RARE);
    lightbringer.strengthBonus = 8;
    lightbringer.speedBonus = 3;
    lightbringer.abilityPowerMultiplier = 1.15f;
    lightbringer.unleashChanceBonus = 0.12f;
    lightbringer.canUnleashOnNormalAttack = true;
    lightbringer.normalAttackUnleashName = "Flame Slash";
    lightbringer.normalAttackUnleashBonus = 8;
    equipmentDatabase.push_back(lightbringer);

    // MYTHICAL SWORD - Excalibur
    Equipment excalibur(3, "Excalibur", "A legendary blade of ultimate power",
                        EquipmentType::WEAPON, WeaponRarity::MYTHICAL);
    excalibur.strengthBonus = 12;
    excalibur.abilityPowerMultiplier = 1.3f;
    excalibur.unleashChanceBonus = 0.20f;
    excalibur.canUnleashOnNormalAttack = true;
    excalibur.normalAttackUnleashName = "Holy Judgment";
    excalibur.normalAttackUnleashBonus = 20;
    equipmentDatabase.push_back(excalibur);

    // RARE SHIELD - Golden Sun Shield
    Equipment goldenSunShield(4, "Golden Sun Shield", "A legendary shield with golden light",
                              EquipmentType::SHIELD, WeaponRarity::RARE);
    goldenSunShield.defenseBonus = 6;
    goldenSunShield.abilityPowerMultiplier = 1.15f;
    goldenSunShield.unleashChanceBonus = 0.15f;
    goldenSunShield.canUnleashOnNormalAttack = false;
    equipmentDatabase.push_back(goldenSunShield);

    // MYTHICAL SHIELD - Aegis Shield
    Equipment aegisShield(5, "Aegis Shield", "An ancient shield that protects all",
                          EquipmentType::SHIELD, WeaponRarity::MYTHICAL);
    aegisShield.defenseBonus = 10;
    aegisShield.abilityPowerMultiplier = 1.25f;
    aegisShield.unleashChanceBonus = 0.18f;
    aegisShield.canUnleashOnNormalAttack = false;
    equipmentDatabase.push_back(aegisShield);
}

// ... (rest of the implementation stays the same - all the helper methods)