#include <iostream>
#include <string>
using namespace std;

class AttackMA
{
public:
	//constructor
	AttackMA();
	AttackMA(int xCoordinatearg, int yCoordinatearg, int enemyXarg, int enemyYarg, int participantIndexarg, int commanderIndexarg);

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
	string provinceResourcesNames[5] = { "Food", "Wood", "Ore", "Gold", "Mana" };
};
