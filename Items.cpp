#include "Items.h"
#include <vector>
#include <string>

std::vector<Item> items = {
	{1, "potion", ItemType::Consumable, 35, "restores 25% health to a party member"},
	{2, "herb", ItemType::Consumable, 15, "restores 15% health to a party member"},
	{3, "fatigue potion", ItemType::Consumable, 20, "restores 20% health to a party member"},
	{4, "elixir", ItemType::Consumable, 0, "removes all negative status effects from party member"},
	{5, "antidote", ItemType::Consumable, 0, "cures poison status effect from party member"},
	{6, "smelling salts", ItemType::Consumable, 0, "cures knocked out status effect from party member"},
	{7, "revive", ItemType::Consumable, 0, "revives a party member with 25% health"},
	{8, "mana potion", ItemType::Consumable, 30, "restores 30% mana to a party member"},
	{9, "bomb", ItemType::Consumable, 50, "deals 50 damage to all enemies in battle"},
	{10, "grenade", ItemType::Consumable, 75, "deals 75 damage to all enemies in battle"},
	{11, "trap", ItemType::Consumable, 100, "sets a trap that deals 100 damage when the enemy tries to attack after it's set."},
	{12, "transmutation scroll", ItemType::Consumable, 0, "allows user to transmute an item into another type of consumable"},
	{13, "apothecary kit", ItemType::KeyItem, 0, "allows user to create potions and other consumables from ingredients found in the world"},
	{14, "mystic stone", ItemType::Consumable, 0, "a magical stone that can be used to enhance the power of a magic spell or ability"},
	{15, "elemental shard", ItemType::Consumable, 0, "a shard of elemental energy that can be used to change the element of a magic spell or ability"},
	{16, "healing crystal", ItemType::Consumable, 50, "a crystal that can be used to heal a party member for 50% of their max health"},
	{17, "mana crystal", ItemType::Consumable, 50, "a crystal that can be used to restore 50% mana to a party member"},
	{18, "throwable spear", ItemType::Consumable, 60, "a spear that can be thrown at an enemy to deal 60 damage"},
	{19, "throwing knife", ItemType::Consumable, 40, "a knife that can be thrown at an enemy to deal 40 damage"},
	{20, "throwing dagger", ItemType::Consumable, 50, "a dagger that can be thrown at an enemy to deal 50 damage"}

};