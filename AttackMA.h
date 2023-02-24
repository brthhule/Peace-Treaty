#ifndef ATTACKMA_H
#define ATTACKMA_H

#include <iostream>
#include <string>
#include <vector>

#include "coordinateFunctions.h"
#include "Participants.h"
#include "CommanderProfile.h"
#include "Provinces.h"
#include "main.cpp"

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
	AttackMA();
	AttackMA(std::vector<int> unitAttackingArg, std::vector <int> unitAttackedArg, Participants * attackingParticipantArg, CommanderProfile* commanderArg);

	//Function stuff
	void playerAttack();
	void playerCommitAttack();
	void playerCommitAttackWin(int oldResources[5]);
	void battleCalculations(int lostCombatPower, int deadTroops[5], int a);
	void battleCalculationsTwo(int& lostCombatPower, int deadTroops[5], int troopIndex);
private:
	std::vector <int> unitAttacking;
	std::vector <int> unitAttacked;
	Participants * attackingParticipant;//player
	Participants * attackedParticipant;//enemy

	CommanderProfile * commander;
	std::vector <int> commandersBeingAttackedIndices;
};

#endif