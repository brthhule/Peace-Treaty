#ifndef ATTACKMA_H
#define ATTACKMA_H

#include <iostream>
#include <string>
#include <vector>

#include "Participants.h"
#include "CommanderProfile.h"
#include "Provinces.h"

extern std::vector <Participants> participantsList;
extern std::vector<std::vector<Provinces>> provincesMap;
extern int continentSize;
extern int enemyDifficulty;
extern int troopsCP[5];
extern std::string provinceResourcesNames[5];

class AttackMA
{
public:
	//constructor
	AttackMA(Provinces *defendingProvinceArg, Participants* attackingParticipantArg);
	AttackMA(Provinces* attackerProvinceArg, Provinces* defenderProvinceArg, Participants * attackingParticipantArg, CommanderProfile* commanderArg);
	void findCommander (std::vector<CommanderProfile*> commandersCanAttack);

	//Function stuff
	void playerAttack();
	void playerCommitAttack();
	void playerCommitAttackWin(int oldResources[5]);
	void battleCalculations(int lostCombatPower, int deadTroops[5], int a);
	void battleCalculationsTwo(int& lostCombatPower, int deadTroops[5], int troopIndex);


private:
	Provinces *attackingProvince;
	Provinces *defendingProvince;
	Participants * attackingParticipant;//player
	Participants * defendingParticipant;//enemy
	CommanderProfile * attackingCommander;
	std::vector <CommanderProfile*> defendingCommanders;
};

#endif