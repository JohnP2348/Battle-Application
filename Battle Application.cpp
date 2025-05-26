// The issue is caused by an unclosed '{' in the code. The main function and some blocks are not properly closed.  
// Below is the corrected code with proper closing braces added.  

#include <iostream>  
#include <string>  // includes the ability to make a string for the commands and options
#include <vector>  // includes the ability to make a container for the party members
#include "PartyMember.h"  // Include the header file for PartyMember
using namespace std;  


int main()  
{  
   

   string Fight = "1. Fight \n";  
   string Run = "2. Flee \n";  
   string status = "3. Status \n";  

   int FightChoice;  
   cout << "Battle";  
   cout << "Pick a command: \n";  
   cout << Fight;  
   cout << Run;  
   cout << status;  
   cin >> FightChoice;  

   if (FightChoice == 1)  
   {  
       cout << "You have chosen to fight!";  

       // define the commands and sub menus  
       vector<string> commands = { "Attack", "Ability", "Magic", "Item", "Defend" };  
       // store each command picked by the player for the corresponding character  
       vector<int> chosenCommands(party.size());  
       // iterate through the party members and ask for their command  
       for (size_t i = 0; i < party.size(); i++)  
       {  
           cout << party[i].name << "'s turn!\n";  
           cout << "choose an action!";  

           // display the commands  
           for (size_t j = 0; j < commands.size(); j++)  
           {  
               cout << j + 1 << ": " << commands[j] << "\n";  
           }  
           int choice;  
           cout << "Enter your choice: ";  
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
           cout << "Escape failed! The enemy attacks!";  
       }  
   }  
   else if (FightChoice == 3)  
   {  
       cout << "Party Status";  
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