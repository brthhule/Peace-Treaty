#ifndef ARMYDEPLOYMENTMA_H
#define ARMYDEPLOYMENTMA_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "OtherFunctions.h"
#include "textFunctions.h"
#include "Participants.h"
#include "Lists.h"
#include "Mobility.h"
#include "AllUnits.h"

#define UNIT_SIZE 5

extern int maxAmountOfCommanders;

class ArmyDeploymentMA
{
public:
	//constructor
	ArmyDeploymentMA(Participants *newP);

	//Accessors
	void printCosts(std::vector<int>costs, std::string type);

	//Other Function stuff
	void armyDeploymentMF();
	void trainCommanders();
	void proceedWithTraining(std::array <int,5> trainCosts);
	void upgradeCommandersOne();
	void upgradeCommandersTwo();
	void viewArmyOverview();
	void deployCommanderMF();


	
private:
	Participants *participant;
	int commandersNum;
	OtherFunctions OF;
};

#endif