#ifndef ARMYDEPLOYMENTMA_H
#define ARMYDEPLOYMENTMA_H

#include <iostream>
#include <string>
#include <vector>

#include "otherFunctions.h"
#include "textFunctions.h"
#include "Participants.h"
#include "Provinces.h"
#include "Lists.h"
#include "coordinateFunctions.h"
#include "CommanderProfile.h"

class ArmyDeploymentMA
{
public:
	//constructor
	ArmyDeploymentMA();
	ArmyDeploymentMA(Participants *newP);

	//Accessors
	void printCosts(vector<int>costs, string type);

	//Other Function stuff
	void armyDeploymentMF();
	void trainCommanders();
	void proceedWithTraining(vector <int> trainCosts);
	void upgradeCommandersOne();
	void upgradeCommandersTwo();
	void viewArmyOverview();
	void deployCommanderMF();

	CommanderProfile *selectCommander(char &successfulSelection);


	void deployCommanderDisplayInformation(int commandersInCapital);
private:
	int capitalX;
	int capitalY;
	Participants *participant;
	Provinces *capitalProvince;
	int commandersNum;
};

#endif