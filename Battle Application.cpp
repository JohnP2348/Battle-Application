// The issue is caused by an unclosed '{' in the code. The main function and some blocks are not properly closed.  
// Below is the corrected code with proper closing braces added.  
#include "Enemies.h" // Include the header file for Enemies
#include <iostream>  // includes the ability to make input and output to the console
#include <string>  // includes the ability to make a string for the commands and options
#include <vector>  // includes the ability to make a container for the party members
#include "PartyMember.h"  // Include the header file for PartyMember
#include <random> // includes the ability to spawn random enemies and make random choices for enemies.
#include <algorithm> // includes the ability to sort the party members by speed for turn order 
using namespace std;  
// to spawn 1-4 enemies with rarity logic
vector<RegularEnemy> SpawnEnemyParty() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> partySizeDist(1, 100);
    int roll = partySizeDist(gen);  // Generate a random number between 1 and 100
    int numEnemies;
    if (roll <= 40) numEnemies = 2;  // 40% chance to spawn 1 enemy
    else if (roll <= 70) numEnemies = 1;  // 30% chance to spawn 2 enemies
    else if (roll <= 90) numEnemies = 3;  // 20% chance to spawn 3 enemies
    else numEnemies = 4;  // 10% chance to spawn 4 enemies

    vector<RegularEnemy> enemies;
    uniform_int_distribution<> enemyDist(0, regularEnemies.size() - 1); // Generate a random enemy from the regularEnemies vector
    for (int i = 0; i < numEnemies; i++) // for loop
    {
        enemies.push_back(regularEnemies[enemyDist(gen)]); // Add a random enemy to the enemies vector
    }
    return enemies;
}// Return the vector of enemies

int main()  
{  

	vector<RegularEnemy> enemies = SpawnEnemyParty();  // Call the function to spawn a party of enemies
    for (size_t i = 0; i < enemies.size(); i++)
    {
		cout << enemies[i].name;  // Display the name of each enemy in the party
        cout << "\n appeared! \n";  // Display the number of enemies spawned
    }
   string Fight = "1. Fight \n";  
   string Run = "2. Flee \n";  
   string status = "3. Status \n";  

   int FightChoice;  // variable to store the player's choice of action in battle
   cout << "Battle \n";  // display the title of the battle
   cout << "Pick a command: \n";  // display the options for the player to choose from
   cout << Fight;  
   cout << Run;  
   cout << status;  
   cin >> FightChoice;  // get the player's choice of action in battle

   if (FightChoice == 1)  
   {  
       cout << "You have chosen to fight! \n";  

       // define the commands and sub menus  
       vector<string> commands = { "Attack", "Ability", "Magic", "Item", "Defend" };  
       // store each command picked by the player for the corresponding character  
       vector<int> chosenCommands(party.size());  
       // iterate through the party members and ask for their command  
       for (size_t i = 0; i < party.size(); i++)  
       {  
           cout << party[i].name << "'s turn!\n";  
           cout << "choose an action! \n";  

           // display the commands  
           for (size_t j = 0; j < commands.size(); j++)  
           {  
               cout << j + 1 << ": " << commands[j] << "\n";  
           }  
           int choice;  
           cout << "Enter your choice: \n";  
           cin >> choice;  
           if (choice >= 1 && choice <= commands.size())  
           {  
               chosenCommands[i] = choice - 1;  
               cout << party[i].name << " Gets ready!\n";  
           }  
           else {  
               cout << "Pick a valid command!\n";  
               i--;  
           }  
       }  
   }  
   else if (FightChoice == 2)  
   {  
       cout << "Party attempts to escape!";  
       bool escapeSuccess = false;  
       // Add escape logic here  
       // For example, you could check if the party has a high enough speed to escape  
       if (escapeSuccess == true) {  
           return 0;  
       }  
       else {  
           cout << "Escape failed! \n The enemy attacks! \n";  
       }  
   }  
   else if (FightChoice == 3)  
   {  
       cout << "Party Status \n";  
       for (size_t i = 0; i < party.size(); i++)  
       {  
           cout << party[i].name << " Health: " << party[i].health << "/" << party[i].maxHealth << "\n";  
           cout << party[i].name << " Mana: " << party[i].mana << "/" << party[i].maxMana << "\n";  
           cout << party[i].name << " Level: " << party[i].level << "\n";  
           cout << party[i].name << " Experience: " << party[i].experience << "\n";  
       }  
   }  

   return 0; // Properly close the main function  
}