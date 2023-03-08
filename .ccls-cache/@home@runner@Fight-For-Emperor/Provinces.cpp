#include "Provinces.h"
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
	isNeutral = true;
	scoutLogTurnLevel[0] = -1;
	scoutLogTurnLevel[1] = -1;
    troopsTrainedThisTurn = 0;
  deleteProvince = false;
}
Provinces::Provinces(int sendXCoordinate, int sendYCoordinate, int pIndex)
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
		provinceStats[x] = &initialResources[x];
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
  
	provinceX = sendXCoordinate;
	provinceY = sendYCoordinate;
  
	participantIndex = pIndex;
	scoutLogTurnLevel[0] = -1;
	scoutLogTurnLevel[1] = -1;
    troopsTrainedThisTurn = 0;
  deleteProvince = false;
}


//Province stats

int Provinces::findMaxGarrison()
{
	int maxGarrisonThingy = buildingLevels[5] * 10;
	return maxGarrisonThingy;
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

//Other
void Provinces::setCoordinates(int xCoordinate, int yCoordinate)
{
	xCoord = xCoordinate;
	yCoord = yCoordinate;
}
void Provinces::initializeCapital()
{
	for (int x = 0; x < 5; x++)
	{
		resourcesPresent[x] = initialStats[x];
		buildingLevels[x] = 1;
	}
	buildingLevels[5] = 1;
	buildingLevels[6] = 1;

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
	for (int x = 0; x < 6; x++)
	{
		buildingsProduction[x] = buildingLevels[x] * provinceBuildingsProductionNumbers[x];
	}
    std::cout << "\033[;34m";

	std::cout << "Building stats of this province: " << std::endl;
	for (int x = 0; x < 5; x++)
	{
		std::cout << "- " << buildingNames[x] << " (" << buildingNames[x].substr(0, 1) << ") " << std::endl;
		std::cout << "    Level: " << buildingLevels[x] << std::endl;
		std::cout << "    " << provinceResourcesNames[x] << " production rate : " << buildingsProduction[x] << std::endl;
	}
	std::cout << "Barracks (B) " << std::endl;
	std::cout << "    Level: " << buildingLevels[5] << std::endl;
	std::cout << "    Max training capacity: " << buildingsProduction[5] << std::endl;
	std::cout << std::endl;
	std::cout << "\033[;0m";


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
void Provinces::removeCommander(CommanderProfile *newCommander)
{
	int index = 0;
	for (int x = 0; x < commandersNum(); x++)
	{
		if (newCommander->getUnitName() == commanders[x]->getUnitName())
		{
			index = x;
		}
	}
	commanders.erase(commanders.begin() + index);
}



void Provinces::addTroopsTrainedThisTurn(int amount)
{
    troopsTrainedThisTurn += amount;
}

void Provinces::changeParticipant(int num)
{
  participantIndex = num;
}

int Provinces::getCoordinate (char identifier)
{
  switch (identifier)
  {
    case 'X':
      return xCoord;
    case 'Y':
      return yCoord;
    default:
      return -1;//in case something bad happen
  }
}



bool Provinces::deleteStatus()
{
  return deleteProvince;
}

int Provinces::translateX(bool isInput)
{
	if (isInput)
	{
		return xCoord - 1;
	} else
	{
		return xCoord + 1;
	}
}

int Provinces::translateY(bool isInput)
{
	if (isInput)
	{
		return abs(yCoord - continentSize);
	} else
	{
		return abs(continentSize - yCoord);
	}
}

int Provinces::getTotalCP()
{
	int totalCP = 0;
	totalCP += getCP();
	for (int x = 0; x < commandersNum(); x++)
	{
		totalCP += commanders[x]->getCP();
	}
}

std::vector<int> Provinces::getTotalResources()
{
	std::vector<int> totalResources = resourcesPresent;
	for (int x = 0; x < commandersNum(); x++)
	{
		for (int y = 0; y < 5; y++)
		{
			totalResources[y] += commanders[x].getResource(y);
		}
	}
	return totalResources;
}