#ifndef PROVINCES_H
#define PROVINCES_H

#include <vector>
#include <iostream>

#include "AllUnits.h"

class Provinces : public AllUnits
{
public:
	/*Constructors*/
	Provinces();
	Provinces(int xCoordinate, int yCoordinate);

	/*Destructor*/

	/*Accessor Functions*/
	int getProvinceStats(int index);
	int findProvinceScoutLog(int index);
	int findMaxGarrison();
	int findMaxInfirmaryCapacity();
	int getBuildingLevel(int index);
	int getCommandersPresent();
	int returnCommanderPresentIdentifier(int index);
	int returnCommanderIndex(int index);
	int getTroopsTrainedThisTurn();
	int findProvinceLevel();
	int returnProvinceParticipantIndex();


	void printBuildingStats();

	char getProvinceIdentifier();

	/*Mutator Functions*/
	void updateProvinceScoutLog(int index, int value);
	void updateBuildingsProduction();
	void updateProvinceResources();
	void setProvinceIdentifier(char identifier);
	void addCommandersPresent(int amount);
	void removeCommandersPresent(int amount);
	void setCoordinates(int xCoordinate, int yCoordinate);
	void provinceIsACapital(char identifier);
	void resetTroopsTrainedThisTurn();
	void increaseBuildingLevel(int index, int amount);
    void completeProvinceScoutReport(int accuracy);

	//public variables
	char provinceIdentifier;
	int commandersPresent;
	vector <int> commandersPresentIndices;
	std::vector <char> listOfCommandersPresent;

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
	int provinceScoutReport[28] = {};/*
[27] = turn number of scout report
[28] = accuracy of scout report*/
	int provinceLevel;
	int maxGarrison;
	int maxInfirmaryCapacity;
	int buildingLevels[7];
	int buildingsProduction[6];
	int maxResources[5];
	int totalMaxResources;
	int troopsTrainedThisTurn;

	int resourcesPresent[5];
	int troopsPresent[5];
	int troopsInjured[5];
	int totalCP;
	int totalTroops;
	int foodConsumption;

	int initialStats[5] = { 5, 4, 3, 2, 1 };


	int provinceParticipantIndex;
};

#endif