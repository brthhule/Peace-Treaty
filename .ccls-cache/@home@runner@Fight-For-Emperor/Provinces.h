#ifndef PROVINCES_H
#define PROVINCES_H

#include <vector>
#include <iostream>

#include "Provinces.h"
#include "Participants.h"
#include "CommanderProfile.h"

class Provinces : public AllUnits
{
public:
	/*Constructors*/
	Provinces();
	Provinces(int xCoordinate, int yCoordinate, int index);

	/*Destructor*/

	/*Accessor Functions*/
	int getProvinceStats(int index);
	int findProvinceScoutLog(int index);
	int findMaxGarrison();
	int findMaxInfirmaryCapacity();
	int getBuildingLevel(int index);

	int returnCommanderIndex(int index);
	int getTroopsTrainedThisTurn();
	int findProvinceLevel();

	void printBuildingStats();
	char isProvinceACapitalQuestion();

	/*Mutator Functions*/
	void updateProvinceScoutLog(int index, int value);
	void updateBuildingsProduction();
	void updateProvinceResources();
	void setCoordinates(int xCoordinate, int yCoordinate);
	void provinceIsACapital();
	void addCommanderProvince(int commanderIndex);
	void removeCommanderProvince(int commanderIndex);

	void resetTroopsTrainedThisTurn();
	void increaseBuildingLevel(int index, int amount);
	void completeProvinceScoutReport(int accuracy);

	//public variables
	vector <int> commandersPresentIndex;
	int scoutLogTurnLevel[2];//[0] is the turn of the scout report, [1] is the scout log level


	//from AllUnits
	//Accessor Functions

private:
	int* provinceStats[27];/*
[0] food present
[1] wood present
[2] ore present
[3] gold present
[4] mana present
[5] max resources province can hold
[6] garrisoned militia
[7] garrisoned guards
[8] garrisoned cavalry
[9] garrisoned knights
[10] garrisoned paladins
[11] max garrison
[12] injured malitia
[13] injured guards
[14] injured cavalry
[15] injured knights
[16] injured paladins
[17] max infirmary capacity
[18] farm level
[19] lumber mill level
[20] quarry level
[21] mine level
[22] church level
[23] barracks level
[24] infirmary level
[25] total CP
[26] food consumption*/
	int provinceLevel;
	int maxGarrison;
	int maxInfirmaryCapacity;
	int buildingLevels[7];
	int buildingsProduction[6];
	int maxResources[5];
	int totalMaxResources;
	int troopsTrainedThisTurn;

	int troopsPresent[5];
	int troopsInjured[5];
	int totalCP;
	int totalTroops;
	int foodConsumption;

	int initialStats[5] = { 5, 4, 3, 2, 1 };

	char isACapital;

	int provinceScoutReport[28] = {};/*
[27] = turn number of scout report
[28] = accuracy of scout report*/

};

#endif