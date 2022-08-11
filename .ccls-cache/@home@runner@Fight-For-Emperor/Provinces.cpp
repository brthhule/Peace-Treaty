#include <iostream>
#include <vector>

#include "Provinces.h"
#include "AllUnits.h"
#include "textFunctions.h"

using namespace std;

extern vector <Participants> participantsList;
extern int currentParticipantIndex;
extern string provinceResourcesNames[5];
extern string buildingNames[6];
extern string troopNames[5];
extern int provinceBuildingsProductionNumbers[6];
extern int initialResources[5];
extern int troopsCP[5];
extern int turn;

//constructors
Provinces::Provinces()
{
	for (int x = 0; sizeof(provinceScoutReport); x++)
	{
		provinceScoutReport[x] = 0;
	}
	for (int x = 0; x < 5; x++)
	{
		provinceStats[x] = &resourcesPresent[x];
		provinceStats[x + 6] = &troopsPresent[x];
		provinceStats[x + 18] = &buildingLevels[x];
	}
	provinceStats[5] = &totalMaxResources;
	provinceStats[23] = &buildingLevels[6];
	provinceStats[24] = &buildingLevels[7];
	provinceStats[25] = &totalCP;
	provinceStats[11] = &maxGarrison;
	provinceStats[17] = &maxInfirmaryCapacity;
	provinceStats[26] = &foodConsumption;
	maxGarrison = findMaxGarrison();
	maxInfirmaryCapacity = findMaxInfirmaryCapacity();

	provinceLevel = 1;
	belongsToParticipant = -1;
	scoutLogTurnLevel[0] = -1;
	scoutLogTurnLevel[1] = -1;
    troopsTrainedThisTurn = 0;
}
Provinces::Provinces(int sendXCoordinate, int sendYCoordinate, int index)
{
	//Initialize building levels
	for (int x = 0; x < sizeof(buildingLevels) / sizeof(int); x++)
	{
		buildingLevels[x] = 1;
	}
	for (int x = 0; x < sizeof(provinceScoutReport) / sizeof(int); x++)
	{
		provinceScoutReport[x] = 0;
	}
	for (int x = 0; x < 5; x++)
	{
		provinceStats[x] = &resourcesPresent[x]; //Set pointer to parent array
		*provinceStats[x] = initialResources[x];
		provinceStats[x + 6] = &troopsPresent[x];
		provinceStats[x + 18] = &buildingLevels[x];
	}
	provinceStats[5] = &totalMaxResources;
	provinceStats[23] = &buildingLevels[6];
	provinceStats[24] = &buildingLevels[7];
	provinceStats[25] = &totalCP;
	provinceStats[11] = &maxGarrison;
	provinceStats[17] = &maxInfirmaryCapacity;
	provinceStats[26] = &foodConsumption;
	maxGarrison = findMaxGarrison();
	maxInfirmaryCapacity = findMaxInfirmaryCapacity();
	provinceLevel = 1;
	unitXCoordinate = sendXCoordinate;
	unitYCoordinate = sendYCoordinate;
	isACapital = 'N';
	belongsToParticipant = index;
	scoutLogTurnLevel[0] = -1;
	scoutLogTurnLevel[1] = -1;
    troopsTrainedThisTurn = 0;
}


//Province stats
int Provinces::getProvinceStats(int index)
{
	return *provinceStats[index];
}
int Provinces::findMaxGarrison()
{
	int maxGarrisonThingy = buildingLevels[5] * 10;
	return maxGarrisonThingy;
}
int Provinces::findMaxInfirmaryCapacity()
{
	return (buildingLevels[6] * 10);
}
int Provinces::findProvinceLevel()
{
	provinceLevel = 0;
	for (int x = 0; x < sizeof(buildingLevels) / sizeof(int); x++)
	{
		provinceLevel += buildingLevels[x];
	}
	provinceLevel /= 6;
	return provinceLevel;
}
int Provinces::getTroopsTrainedThisTurn()
{
	return troopsTrainedThisTurn;
}

//Scout stuff
void Provinces::updateProvinceScoutLog(int index, int value)
{
	provinceScoutReport[index] = value;
}
void Provinces::completeProvinceScoutReport(int accuracy)
{
	double newAccuracy = (double)accuracy / 100;
	newAccuracy = 1 - newAccuracy;
	double accuracyAdjustedValueOne;
	int accuracyAdjustedValueTwo;

	int fooOne;
	int fooTwo;
	int findRange;
	for (int x = 0; x < 20; x++) //fix this
	{
		findRange = *provinceStats[x];
		accuracyAdjustedValueOne = findRange * newAccuracy;
		fooOne = findRange - (int)accuracyAdjustedValueOne;
		fooTwo = findRange + (int)accuracyAdjustedValueOne;
		accuracyAdjustedValueTwo = rand() % fooOne + fooTwo;
		updateProvinceScoutLog(x, accuracyAdjustedValueTwo);
	}
	updateProvinceScoutLog(20, turn);
	updateProvinceScoutLog(21, accuracy);
}
int Provinces::findProvinceScoutLog(int index)
{
	return provinceScoutReport[index];
}


//Province stuff
void Provinces::updateProvinceResources()
{
	for (int x = 0; x < sizeof(buildingsProduction) / sizeof(int) - 1; x++)
	{
		resourcesPresent[x] += buildingsProduction[x];
	}
}
char Provinces::isProvinceACapitalQuestion()
{
	return isACapital;
}

//Other
void Provinces::setCoordinates(int xCoordinate, int yCoordinate)
{
	unitXCoordinate = xCoordinate;
	unitYCoordinate = yCoordinate;
}
void Provinces::provinceIsACapital()
{
	for (int x = 0; x < 5; x++)
	{
		resourcesPresent[x] = initialStats[x];
		buildingLevels[x] = 1;
	}
	buildingLevels[5] = 1;
	buildingLevels[6] = 1;
	isACapital = 'Y';
}
void Provinces::resetTroopsTrainedThisTurn()
{
	troopsTrainedThisTurn = 0;
}

//Building Stuff
void Provinces::increaseBuildingLevel(int index, int amount)
{
	resourcesPresent[index] += amount;
}
void Provinces::printBuildingStats()
{
	cout << "\033[;34m";
	for (int x = 0; x < 6; x++)
	{
		buildingsProduction[x] = buildingLevels[x] * provinceBuildingsProductionNumbers[x];
	}
	std::cout << "Buildings in this province: " << endl << endl;
	for (int x = 0; x < 5; x++)
	{
		std::cout << buildingNames[x] << " (" << buildingNames[x].substr(0, 1) << ") " << endl;
		std::cout << "    Level: " << buildingLevels[x] << endl;
		std::cout << "    " << provinceResourcesNames[x] << " production rate : " << buildingsProduction[x] << endl;
	}
	std::cout << "Barracks (B) " << endl;
	std::cout << "    Level: " << buildingLevels[5] << endl;
	std::cout << "    Max training capacity: " << buildingsProduction[5] << endl;
	std::cout << endl;
	cout << "\033[;0m";


}
int Provinces::getBuildingLevel(int index)
{
	return buildingLevels[index];
}
void Provinces::updateBuildingsProduction()
{
	for (int x = 0; x < sizeof(buildingsProduction) / sizeof(int); x++)
	{
		buildingsProduction[x] = buildingLevels[x] * provinceBuildingsProductionNumbers[x];
	}
}

//Commander Stuff
void Provinces::addCommanderProvince(int commanderIndex)
{
	commandersPresentIndex.push_back(commanderIndex);
}
void Provinces::removeCommanderProvince(int commanderIndex)
{
	commandersPresentIndex.erase(commandersPresentIndex.begin() + commanderIndex);
}

int Provinces::returnCommanderIndex(int index)
{
	return commandersPresentIndex[index];
}

void Provinces::addTroopsTrainedThisTurn(int amount)
{
    troopsTrainedThisTurn += amount;
}
