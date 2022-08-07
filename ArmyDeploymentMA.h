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

	//Accessors
	void printCostsToUpgradeACommander(int commanderUpgradeCosts[5], int indexOfCommander);

	//Other Function stuff
	void armyDeploymentMF();
	void trainCommanders();
	void upgradeCommanders();
	void viewArmyOverview();
	void deployCommanderMF();
	void printCostsToTrainAnotherCommander(int trainArmyCommanderCosts[5]);


	void deployCommanderDisplayInformation(int commandersInCapital);
private:
	int capitalX;
	int capitalY;
};

