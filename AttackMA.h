#ifndef ATTACKMA_H
#define ATTACKMA_H

#include <iostream>
#include <string>
#include <vector>

#include "coordinateFunctions.h"
#include "Participants.h"
#include "Provinces.h"
#include "CommanderProfile.h"

extern vector <Participants> participantsList;
extern vector<vector<Provinces>> provincesMap;
extern int continentSize;
extern int enemyDifficulty;
extern int troopsCP[5];
extern string provinceResourcesNames[5];

using namespace std;

class AttackMA
{
public:
	//constructor
	AttackMA();
	AttackMA(vector<int> unitAttackingArg, vector <int> unitAttackedArg, Participants * attackingParticipantArg, CommanderProfile* commanderArg);

	//Function stuff
	void playerAttack();
	void playerCommitAttack();
	void playerCommitAttackWin(int oldResources[5]);
	void battleCalculations(int lostCombatPower, int deadTroops[5], int a);
	void battleCalculationsTwo(int& lostCombatPower, int deadTroops[5], int troopIndex);
private:
	vector <int> unitAttacking;
	vector <int> unitAttacked;
	Participants * attackingParticipant;//player
	Participants * attackedParticipant;//enemy

	CommanderProfile * commander;
	vector <int> commandersBeingAttackedIndices;
};

#endif