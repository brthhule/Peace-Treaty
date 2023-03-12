#include "Provinces.h"
//constructors
Provinces::Provinces()
{
	participantIndex = -1;
	basicStats();
}
Provinces::Provinces(int sendXCoordinate, int sendYCoordinate, int pIndex)
{
	//Initialize building levels
	for (int x = 0; x < sizeof(buildingLevels) / sizeof(int); x++)
	{
		buildingLevels[x] = 1;
	}
	xCoord = sendXCoordinate;
	yCoord = sendYCoordinate;
	participantIndex = pIndex;
	basicStats();
}

void Provinces::basicStats()
{
	OF.modifyArray(resourcesPresent, initialResources, true);
	
	scoutReportTurn = -1;
	scoutReportLogLevel = -1;
	
	unitLevel = 1;
	maxGarrison = findMaxGarrison();
	maxInfirmaryCapacity = findMaxInfirmaryCapacity();
	
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
	unitLevel = 0;
	for (int x = 0; x < 5; x++)
		unitLevel += resourceBuildingsLevels[x];
	unitLevel += otherBuildingLevels[0] + otherBuildingLevels[1]
	
	unitLevel /= 6;
	return provinceLevel;
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
	commanders.erase(newCommander->getUnitName());
}

void Provinces::addCommander(CommanderProfile* newCommander)
{
  commanders[newCommander->getUnitName()] = newCommander;
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

std::vector <CommanderProfile*> Provinces::returnAllCommmanders(){
		std::vector<CommanderProfile*> commandersList;
		std::unordered_map<std::string, CommanderProfile*>::iterator it;
		for (it = commanders.begin(); it != commanders.end(); it++)
			commandersList.push_back(it->second);
		return commandersList;
}

CommanderProfile* Provinces::returnCommander(std::string name)
{
	return commanders[name];
}

bool Provinces::subtractCheckResources(std::array<int, 5> resourcesArray)
{
	//returns false if resources dip into negatives
	modifyResources(resourcesArray, false);
	for (int x: resourcesPresent)
		if (x < 0)
			return false;
	return true;
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
	/*/*
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
}

void compileProvinceStats (int (&provinceStatsArray)[35], bool &isACapitalArg, int (&otherStats)[17], std::string &unitNameArg, std::unordered_map<std::string, CommanderProfile*> &commandersArg;)
{
	unitNameArg = unitName;
	isACapitalArg = isACapital;
	
	for (int x = 0; x < 5; x++)
	{
		provinceStatsArray[x] = resourcesPresent[x];
		provinceStatsArray[x + 5] = troopsPresent[x];
		provinceStatsArray[x + 10] = troopsInjured[x];
		provinceStatsArray[x + 15] = troopsLost[x];
		provinceStatsArray[x + 20] = resourceBuildingsLevels[x];
		provinceStatsArray[x + 25] = resourceBuildingsProduction[x];
		provinceStatsArray[x + 30] = maxResources[x];
	}

	otherStats[1] =  CP;
	otherStats[2] =  totalTroops;
	otherStats[3] =  foodConsumption;

	otherStats[4] =  xCoord = 0;
	otherStats[5] =  yCoord = 0;
	otherStats[6] =  participantIndex;
	otherStats[7] =  unitLevel;
	otherStats[8] =  maxGarrison;
  otherStats[9] =  maxInfirmaryCapacity;

	otherStats[10] =  otherBuildingLevels[0];
	otherStats[11] =  otherBuildingLevels[1];

  otherStats[12] =  totalMaxResources;
  otherStats[13] =  troopsTrainedThisTurn;
  otherStats[14] =  foodConsumption;

	otherStats[15] =  scoutReportTurn;
	otherStats[16] =  scoutReportLogLevel;
	otherStats[17] =  logAccuracy;

	commandersArg = commanders;


	int resourcesPresent[5] = {0, 0, 0, 0, 0};
	int troopsPresent[5] = {0, 0, 0, 0, 0};
	int troopsInjured[5] = {0, 0, 0, 0, 0};
	int troopsLost[5] = {0, 0, 0, 0, 0};
	int CP;
	int totalTroops;
	int foodConsumption;

	const int initialStats[5] = { 5, 4, 3, 2, 1 };

  //Coordinates;
	int *coords [2];
	int xCoord = 0;
	int yCoord = 0;
	char canSelectThisUnit;
	int participantIndex;
	std::string unitName;
	std::string isCommanderOrProvince;
	int unitLevel;
	OtherFunctions OF;
}