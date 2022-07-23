#pragma once
#include <iostream>
#include <string>
using namespace std;
class ArmyDeploymentMA
{
public:
	//constructor
	ArmyDeploymentMA();
	ArmyDeploymentMA(int xCoordinate, int yCoordinate);

	void printCostsToUpgradeACommander(int commanderUpgradeCosts[5], int indexOfCommander);

	void armyDeploymentMF();
	void trainCommanders();
	void upgradeCommanders();
	void viewArmyOverview();
	void deployCommanderMF();
	string deployCommanderDisplayInformation(int commandersInCapital);
private:
	int capitalX;
	int capitalY;
	string provinceResourcesNames[5] = { "Food", "Wood", "Ore", "Gold", "Mana" };

};

