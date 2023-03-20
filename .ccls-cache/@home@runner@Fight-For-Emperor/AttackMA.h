#ifndef ATTACKMA_H
#define ATTACKMA_H

#include <iostream>
#include <string>
#include <vector>

#include "Participants.h"
#include "CommanderProfile.h"
#include "Provinces.h"
#include "AllUnits.h"
#include "ConstValues.h"

extern std::vector <Participants> participantsList;
extern std::vector<std::vector<Provinces>> provincesMap;
extern int continentSize;
extern int enemyDifficulty;
extern ConstValues CV;

class AttackMA
{
public:
	//constructor
	AttackMA(Provinces *defendingProvinceArg, Participants* attackingParticipantArg);
	AttackMA(Provinces* attackerProvinceArg, Provinces* defenderProvinceArg, Participants * attackingParticipantArg, CommanderProfile* commanderArg);
	void findCommander (std::vector<CommanderProfile*> commandersCanAttack);
	void printResourcesGained();
	void determineLostCP(int attackerCP, int defendingCP, int& attackerLostCP, int& defenderLostCP);

	//Function stuff
	void preAttack();
	void playerCommitAttack();
	void calculateTroopsLost(CommanderProfile* commander, int lostCombatPower, std::array<int,5> &troopsLost, int troopIndex);
	void battleCalculationsTwo(int& lostCombatPower, int troopsLost[5], int troopIndex);


private:
	Provinces *attackingProvince;
	Provinces *defendingProvince;
	Participants * attackingParticipant;//player
	Participants * defendingParticipant;//enemy
	CommanderProfile * attackingCommander;
	std::vector <CommanderProfile*> defendingCommanders;
	bool defenseCanRetreat;
	std::array<int,5> oldResources;
	OtherFunctions OF;
};

#endif