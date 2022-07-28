#include <iostream>
#include <string>

#include "CommanderProfile.h"

using namespace std;

class AttackMA
{
public:
	//constructor
	AttackMA();
	AttackMA(int xCoordinatearg, int yCoordinatearg, int enemyXarg, int enemyYarg, int participantIndexarg, int commanderIndexarg);

	//Function stuff
	void playerAttack();
	void playerCommitAttack();
	void playerCommitAttackWin(int oldResources[5]);
	void battleCalculations(int lostCombatPower, int deadTroops[5], int playerTroopsLost[5], int a);
	void battleCalculationsTwo(int& lostCombatPower, int deadTroops[5], int playerTroopsLost[5], int identifier);
private:
	int unitAttackingX;
	int unitAttackingY;
	int unitBeingAttackedX;
	int unitBeingAttackedY;
	int participantIndex;
	int commanderIndex;
	vector <int> commandersBeingAttackedIndices;
	int enemyParticipantIndex;
};
