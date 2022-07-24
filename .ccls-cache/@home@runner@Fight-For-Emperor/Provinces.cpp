#include "Provinces.h"

//constructors
Provinces::Provinces()
{
	for (int x = 0; sizeof (provinceScoutReport) / sizeof(int); x++)
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
	provinceIdentifier = '0';
}
Provinces::Provinces(int sendXCoordinate, int sendYCoordinate)
{
	for (int x = 0; sizeof(provinceScoutReport) / sizeof(int); x++)
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
	provinceIdentifier = '0';
	xCoordinate = sendXCoordinate;
	yCoordinate = sendYCoordinate;
}
//Accessors
int Provinces::getProvinceStats(int index)
{
	return *provinceStats[index];
}
int Provinces::findProvinceScoutLog(int index)
{
	return provinceScoutReport[index];
}
int Provinces::findMaxGarrison()
{
	int maxGarrisonThingy = buildingLevels [5] * 10;
	return maxGarrisonThingy;
}
int Provinces::findMaxInfirmaryCapacity()
{
	return (buildingLevels[6] * 10);
}
void Provinces::printBuildingStats()
{
	cout << "\033[;34m";
	for (int x = 0; x < 6; x++)
	{
		buildingsProduction[x] = buildingLevels [x]  * provinceBuildingsProductionNumbersTwo[x];
	}
	std::cout << "Buildings in this province: " << endl << endl;
	for (int x = 0; x < 5; x++)
	{
		std::cout << buildingNamesThree[x] << " (" << buildingNamesThree[x].substr(0, 1) << ") " << endl;
		std::cout << "    Level: " << buildingLevels[x] << endl;
		std::cout << "    " << provinceResourcesNamesThree[x] << " production rate : " << buildingsProduction[x] << endl;
	}
	std::cout << "Barracks (B) " << endl;
	std::cout << "    Level: " << buildingLevels[5] << endl;
	std::cout << "    Max training capacity: " << buildingsProduction[5] << endl;
	std::cout << endl;
	cout << "\033[;0m";


}
char Provinces::getProvinceIdentifier()
{
	return provinceIdentifier;
}
int Provinces::getBuildingLevel(int index)
{
	return buildingLevels[index];
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
int Provinces::getCommandersPresent()
{
	return commandersPresent;
}
int Provinces::returnCommanderPresentIdentifier(int index)
{
	return listOfCommandersPresent[index];
}
int Provinces::getCoordinate(char whichCoordinate)
{
	switch (whichCoordinate)
	{
	case 'Y':
		return yCoordinate;
		break;
	case 'X':
		return xCoordinate;
		break;
	}
}
int Provinces::returnCommanderIndex(int index)
{
	return commandersPresentIndices[index];
}
int Provinces::getTroopsTrainedThisTurn()
{
	return troopsTrainedThisTurn;
}

/*Mutator Functions*/
void Provinces::updateProvinceScoutLog(int index, int value)
{
	provinceScoutReport[index] = value;
}
void Provinces::setProvinceIdentifier(char identifier)
{
	provinceIdentifier = identifier;
}
void Provinces::updateBuildingsProduction()
{
	for (int x = 0; x < sizeof(buildingsProduction) / sizeof(int); x++)
	{
		buildingsProduction[x] = buildingLevels[x] * provinceBuildingsProductionNumbersTwo[x];
	}
}
void Provinces::updateProvinceResources()
{
	for (int x = 0; x < sizeof(buildingsProduction) / sizeof(int); x++)
	{
		resourcesPresent[x] += buildingsProduction[x];
	}
}
void Provinces::addCommandersPresent(int amount)
{
	commandersPresent += amount;
}
void Provinces::removeCommandersPresent(int amount)
{
	commandersPresent -= amount;
}
void Provinces::setCoordinates(int xCoordinate, int yCoordinate)
{
	unitXCoordinate = xCoordinate;
	unitYCoordinate = yCoordinate;
}
void Provinces::provinceIsACapital(char identifier)
{
	for (int x = 0; x < 5; x++)
	{
		resourcesPresent[x] = initialStats[x];
		buildingLevels[x] = 1;
	}
	buildingLevels[6] = 1;
	buildingLevels[7] = 1;
	commandersPresent += 1;
}
void Provinces::resetTroopsTrainedThisTurn()
{
	troopsTrainedThisTurn = 0;
}

int Provinces::getProvinceResource(int resourceIndex)
{
	return resourcesPresent[resourceIndex];
}
int Provinces::getProvinceTroopsPresent(int troopTypeIndex)
{
	return troopsPresent[troopTypeIndex];
}
void Provinces::printProvinceResources()
{

}

//Mutator Functions
void Provinces::removeProvinceTroops(int troopIndex, int troopAmount)
{
	troopsPresent[troopIndex] -= troopAmount;
}
void Provinces::addProvinceResources(int resourceIndex, int resourceAmount)
{
	resourcesPresent[resourceIndex] += resourceAmount;
}
void Provinces::addProvinceInjuredTroops(int troopIndex, int troopAmount)
{
	troopsInjured[troopIndex] -= troopAmount;
}
void Provinces::subtractProvinceResources(int index, int amount)
{
	resourcesPresent [index] -= amount;
}
void Provinces::addProvinceTroops(int troopsAdd[5])
{
	for (int x = 0; x < 5; x++)
	{
		troopsPresent[x] += troopsAdd[5];
	}
}
void Provinces::addProvinceSpecificTroop(int index, int amount)
{
	troopsPresent[index] += amount;
}
void Provinces::increaseBuildingLevel(int index, int amount)
{
	resourcesPresent[index] += amount;
}
