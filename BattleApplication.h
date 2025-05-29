#pragma once
#include <vector>
#include <string>
#include "PartyMember.h"


void RunBattleMenu();

void HandleFight(std::vector<PartyMember>& party);
void HandleFlee(std::vector<PartyMember>& party);
void ShowPartyStatus(const std::vector<PartyMember>& party);