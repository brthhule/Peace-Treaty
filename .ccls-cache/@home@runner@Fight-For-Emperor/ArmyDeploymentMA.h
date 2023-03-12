#ifndef ARMYDEPLOYMENTMA_H
#define ARMYDEPLOYMENTMA_H

#include <iostream>
#include <string>
#include <vector>

#include "OtherFunctions.h"
#include "textFunctions.h"
#include "Participants.h"
#include "Provinces.h"
#include "Lists.h"
#include "CommanderProfile.h"
#include "Mobility.h"
#include "AllUnits.h"

#define UNIT_SIZE 5

class ArmyDeploymentMA
{
public:
	//constructor
	ArmyDeploymentMA();
	ArmyDeploymentMA(Participants *newP);

	//Accessors
	void printCosts(std::vector<int>costs, std::string type);

	//Other Function stuff
	void armyDeploymentMF();
	void trainCommanders();
	void proceedWithTraining(std::vector <int> trainCosts);
	void upgradeCommandersOne();
	void upgradeCommandersTwo();
	void viewArmyOverview();
	void deployCommanderMF();

	CommanderProfile *selectCommander();


	void displayCommanders();
private:
	Participants *participant;
	Provinces *capitalProvince;
	int commandersNum;
	OtherFunctions OF;
};

#endif