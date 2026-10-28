Here's the improved `README.md` file, incorporating the new content while maintaining the existing structure and coherence:

# Battle Application - Sprint 1: State Management & Pre-Battle Setup

## Sprint Overview
**Sprint Goal:** Implement state-based menu system with pre-battle character setup  
**Sprint Duration:** 1 week  
**Status:** In Progress  

---

## What We're Building This Sprint

A central hub menu system that serves as the main interface for the game. Players will use this menu to prepare for battle before engaging enemies.

### Main Menu Options
The State Caller Menu will have these 5 options:

┌─────────────────────────────────────────┐
│     BATTLE APPLICATION - MAIN MENU      │
├─────────────────────────────────────────┤
│                                         │
│  1. Random Battle!                      │
│  2. Party Status                        │
│  3. Equipment Selection                 │
│  4. Inventory                           │
│  5. Bestiary                            │
│                                         │
│  Navigate with UP/DOWN, ENTER to select │
└─────────────────────────────────────────┘

---

## Menu Option Details

### 1. Random Battle!
**What it does:**
- Spawns a random enemy encounter
- Uses current party configuration and positioning
- Uses equipped items from all characters
- Launches into the full battle system
- Returns to main menu when battle completes (win or lose)

**No changes needed yet** - Uses existing `BattleHandler` system

---

### 2. Party Status
**What it does:**
- Display all active party members
- Show each character's current stats:
  - HP / Max HP
  - Mana / Max Mana
  - Fatigue / Max Fatigue
  - Level
  - Experience
  - Current Position (left to right on battlefield)
- Show equipped items per character (Weapon, Shield, Armor)
- View only - no modifications

**User Interface:**
=== PARTY STATUS ===

[Position 1] Zack - Level 5
  HP: 45/50    [==========]
  Mana: 20/20  [==========]
  Fatigue: 15/20 [=========_]
  Equipped: Iron Sword, Wooden Shield, Leather Armor
  Position: Far Left

[Position 2] Elle - Level 4
  HP: 38/40    [=========_]
  Mana: 25/25  [==========]
  Fatigue: 18/20 [=========_]
  Equipped: Dagger, None, Cloth Armor
  Position: Left-Center

[Position 3] Ivan - Level 3
  HP: 30/32    [=========_]
  Mana: 15/20  [=======___]
  Fatigue: 20/20 [==========]
  Equipped: None, None, None
  Position: Center

**Return to main menu when done**

---

### 3. Equipment Selection ⭐ CRITICAL
**What it does:**
- Select which character to equip
- Select which equipment slot (Weapon, Shield, Armor)
- Choose from available equipment in inventory
- See stat preview before confirming
- Equip or unequip items
- Changes persist in the menu

**User Flow:**

Step 1: Select Character
┌─────────────────────────┐
│  Who do you want to     │
│  equip?                 │
├─────────────────────────┤
│ --> Zack (Level 5)      │
│     Elle (Level 4)      │
│     Ivan (Level 3)      │
└─────────────────────────┘

Step 2: Select Equipment Slot
┌─────────────────────────────────────┐
│  Zack's Equipment                   │
├─────────────────────────────────────┤
│ --> Weapon: Iron Sword              │
│     Shield: Wooden Shield           │
│     Armor: Leather Armor            │
│     Back to Character Select        │
└─────────────────────────────────────┘

Step 3: Change Equipment (Weapon example)
┌─────────────────────────────────────┐
│  Zack - Select Weapon               │
├─────────────────────────────────────┤
│  Current: Iron Sword (+3 STR)       │
│                                     │
│  Available in Inventory:            │
│ --> Excalibur (+12 STR) - MYTHICAL  │
│     Lightbringer (+8 STR) - RARE    │
│     Dagger (+2 STR)                 │
│     [Unequip]                       │
│     Back                            │
└─────────────────────────────────────┘

Step 4: Stat Preview
┌─────────────────────────────────────┐
│  Equip Excalibur?                   │
├─────────────────────────────────────┤
│  Current Stats:                     │
│    Strength: 8                      │
│    Defense: 5                       │
│    Speed: 6                         │
│    Max HP: 50                       │
│                                     │
│  With Excalibur:                    │
│    Strength: 20 (+12) ✓             │
│    Defense: 5 (no change)           │
│    Speed: 6 (no change)             │
│    Max HP: 50 (no change)           │
│                                     │
│  [Confirm] [Cancel]                 │
└─────────────────────────────────────┘

**Features:**
- Show current equipped item in each slot
- Show what's available in inventory
- Preview stat changes (highlight +/- in green/red)
- Confirm before equipping
- Return to character select or back to main menu

---

### 4. Inventory
**What it does:**
- Assign usable items to characters
- View what items each character has
- Show item effects/descriptions
- Stand-in inventory for testing

**User Interface:**
=== INVENTORY MANAGEMENT ===

Zack's Items:
  [] Health Potion - Restores 30 HP
  [] Mana Potion - Restores 20 Mana
  [x] Revive Potion - Brings downed ally to 50% HP
  [] Antidote - Cures poison

Elle's Items:
  [x] Health Potion
  [] Strength Tonic - +15% damage for 2 turns
  [] Energy Elixir - Restores 15 Fatigue

Ivan's Items:
  [x] Health Potion
  [x] Health Potion
  [] Mana Potion

**Note:** Items will be used during battle via alchemy/item actions

---

### 5. Bestiary
**What it does:**
- Shows all enemies encountered so far
- Displays stats for discovered enemies
- Grayed out for enemies not yet encountered
- Shows abilities and attack patterns

**User Interface:**
=== BESTIARY ===

[Discovered] Skeleton (Level 1)
  HP: 15 | Attack: 8 | Defense: 3 | Speed: 4
  Abilities: Slash, Bone Throw

[Discovered] Goblin (Level 2)
  HP: 20 | Attack: 10 | Defense: 5 | Speed: 6
  Abilities: Backstab, Poison Arrow

[NOT YET ENCOUNTERED] Orc (Level 3)
  ????? | ????? | ????? | ?????
  Abilities: ??????

[Discovered] Giant Bat (Level 1)
  HP: 12 | Attack: 6 | Defense: 2 | Speed: 7
  Abilities: Bite, Wing Buffet

**Updates** - When player encounters an enemy in battle, it's added to the Bestiary

---

## Technical Implementation

### Files to Create

1. **GameState.h** - Enum and state management
2. **GameStateManager.h/cpp** - Manages state transitions
3. **EquipmentManager.h/cpp** - Equipment operations
4. **MainMenu.h/cpp** - Menu display and navigation
5. **Bestiary.h/cpp** - Enemy discovery tracking
6. **InventoryManager.h/cpp** - Item management

### Files to Update

1. **Battle Application.cpp** - New main loop with state system
2. **PartyMember.h/cpp** - Add inventory fields
3. **DisplayUI.h/cpp** - Add new menu displays
4. **BattleHandler.h/cpp** - Add bestiary discovery call

---

## Implementation Checklist

### Phase 1: State System Foundation
- [ ] Create `GameState.h` with enum
- [ ] Create `GameStateManager.h/cpp`
- [ ] Update `Battle Application.cpp` main loop with state management
- [ ] Test state transitions between all 5 menu options

### Phase 2: Equipment System
- [ ] Create `EquipmentManager.h/cpp`
- [ ] Update `PartyMember.h` with equipment inventory
- [ ] Create equipment selection UI in `DisplayUI.cpp`
- [ ] Test equipping/unequipping items
- [ ] Test stat preview before confirming

### Phase 3: Menu Displays
- [ ] Create `MainMenu.h/cpp` for main menu display
- [ ] Add Party Status display function
- [ ] Add Inventory display function
- [ ] Add Inventory management UI
- [ ] Create `Bestiary.h/cpp`

### Phase 4: Integration & Polish
- [ ] Wire all menus into state system
- [ ] Add bestiary discovery on battle start
- [ ] Test full menu navigation loop
- [ ] Test equipment persists between menus
- [ ] Test Random Battle uses current equipment
- [ ] Bug fixes and cleanup

---

## Success Criteria (Definition of Done)

### ✅ Main Menu Navigation
- [ ] Main menu displays all 5 options correctly
- [ ] UP/DOWN arrows navigate menu
- [ ] ENTER selects option
- [ ] Menu loops continuously until Random Battle or Exit

### ✅ Party Status
- [ ] Shows all party members
- [ ] Displays correct HP/Mana/Fatigue values
- [ ] Shows equipped items
- [ ] Shows battlefield positions
- [ ] Returns to main menu on completion

### ✅ Equipment Selection
- [ ] Can select which character to equip
- [ ] Can select which equipment slot to change
- [ ] Shows current equipped item
- [ ] Shows available items in inventory
- [ ] Displays stat differences (+/- highlighted)
- [ ] Equipment changes persist in menu
- [ ] Changes carry over to Random Battle
- [ ] Can unequip items

### ✅ Inventory Management
- [ ] Shows items per character
- [ ] Can assign items to characters
- [ ] Items display in party status
- [ ] No crashes when managing inventory

### ✅ Bestiary
- [ ] Discovered enemies appear
- [ ] Shows enemy stats for discovered enemies
- [ ] Undiscovered enemies show "????"
- [ ] Updates after each battle
- [ ] Can scroll through all entries

### ✅ Random Battle Integration
- [ ] Uses current equipment configuration
- [ ] Uses current party positioning
- [ ] Adds enemy to bestiary after encounter
- [ ] Returns to main menu after battle
- [ ] Preserves party status between battles

### ✅ Overall
- [ ] No crashes in 10+ full menu cycles
- [ ] All state transitions work smoothly
- [ ] Data persists correctly between menus
- [ ] Code compiles without errors

---

## Stand-In Test Data

For testing purposes, create pre-populated equipment inventory:

// Example equipment for testing
Equipment inventory[] = {
    // Weapons
    Equipment(1, "Iron Sword", "Basic sword", WEAPON, COMMON),
    Equipment(2, "Lightbringer", "Swift blade", WEAPON, RARE),
    Equipment(3, "Excalibur", "Legendary sword", WEAPON, MYTHICAL),
    Equipment(4, "Dagger", "Small blade", WEAPON, COMMON),

    // Shields
    Equipment(5, "Wooden Shield", "Basic shield", SHIELD, COMMON),
    Equipment(6, "Golden Sun Shield", "Legendary shield", SHIELD, RARE),
    Equipment(7, "Aegis Shield", "Ancient shield", SHIELD, MYTHICAL),

    // Armor
    Equipment(8, "Leather Armor", "Light protection", ARMOR, COMMON),
    Equipment(9, "Chain Mail", "Medium protection", ARMOR, RARE),
};

---

## Testing Scenarios

### Scenario 1: Basic Navigation
1. Start game
2. Main menu appears
3. Navigate through all 5 options
4. Each returns to main menu
5. Repeat 5+ times

### Scenario 2: Equipment Change
1. Go to Equipment Selection
2. Select Zack
3. Select Weapon slot
4. Choose Excalibur
5. Confirm change
6. Check Party Status - Zack should have Excalibur equipped
7. Start Random Battle - Zack should have Excalibur in combat

### Scenario 3: Inventory Check
1. Go to Inventory
2. Assign Health Potion to Zack
3. Go to Party Status - should see item assigned
4. Start Random Battle - item should be available

### Scenario 4: Bestiary Discovery
1. Go to Bestiary - should be mostly empty/grayed out
2. Start Random Battle against Skeleton
3. Win or lose the battle
4. Return to main menu
5. Check Bestiary - Skeleton should now be discovered

---

## Known Limitations (For This Sprint)

1. **No Save/Load** - Progress resets when game closes
2. **Stand-in Inventory** - Pre-populated equipment list for testing
3. **No Graphics** - Pure text-based UI
4. **Single Party** - No multi-party management
5. **Item Effects Not Implemented** - Items track but don't do anything yet (next sprint)

---

## Notes for Developers

- Reuse existing `DisplayMenuSelector()` function from DisplayUI for navigation
- Keep consistent with existing HP bar display format
- Use existing color scheme from current battle display
- Maintain C++14 compatibility
- All menus should return to main menu cleanly

---

## Sprint Review Questions

At end of sprint, answer:
- [ ] Can a player navigate all 5 menu options smoothly?
- [ ] Can a player equip/unequip equipment?
- [ ] Do stat changes persist throughout the game?
- [ ] Does the bestiary track discovered enemies?
- [ ] Does Random Battle use configured equipment?
- [ ] Are there any crashes or edge cases?

---

**Sprint Start Date:** [INSERT DATE]  
**Sprint End Date:** [INSERT DATE]  
**Last Updated:** October 28, 2026  
**Repository:** https://github.com/JohnP2348/Battle-Application

This revised README maintains the original structure while integrating the new content seamlessly, ensuring clarity and coherence throughout the document.