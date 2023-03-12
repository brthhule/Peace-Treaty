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
	for (int &x: resourceBuildingsLevels)
		x = 1;
	for (int &x: otherBuildingsLevels)
		x = 1;
	resourcesPresent = INITIAL_VALUES;
	xCoord = sendXCoordinate;
	yCoord = sendYCoordinate;
	participantIndex = pIndex;
	basicStats();
}

void Provinces::basicStats()
{
	OF.modifyArray(resourcesPresent, INITIAL_VALUES, true);
	
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
	return otherBuildingsLevels[3] * 10;
}

int Provinces::findProvinceLevel()
{
	unitLevel = 0;
	for (int x: resourceBuildingsLevels)
		unitLevel += resourceBuildingsLevels[x];
	for (int x: otherBuildingsLevels)
		unitLevel += x;
	
	unitLevel /= resourceBuildingsLevels.size() + otherBuildingsLevels.size();
	return unitLevel;
}

//Province stuff
void Provinces::updateProvinceResources()
{
	for (int x = 0; x < resourceBuildingsLevels.size(); x++)
		resourcesPresent[x] += resourceBuildingsProduction[x];
}

//Other
void Provinces::setCoordinates(int xCoordinate, int yCoordinate)
{
	xCoord = xCoordinate;
	yCoord = yCoordinate;
}
void Provinces::initializeCapital()
{
	isACapital = true;
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
	for (int x = 0; x < 5; x++)
	{
		resourceBuildingsProduction[x] = resourceBuildingsLevels[x] * INITIAL_VALUES[x];
	}
    std::cout << "\033[;34m";

	std::cout << "Building stats of this province: " << std::endl;
	for (int x = 0; x < 5; x++)
	{
		std::cout << "- " << RESOURCE_BUILDING_NAMES[x] << " (" << buildingNames[x].substr(0, 1) << ") " << std::endl;
		std::cout << "    Level: " << resourceBuildingsLevels[x] << std::endl;
		std::cout << "    " << RESOURCE_NAMES[x] << " production rate : " << resourceBuildingsProduction[x] << std::endl;
	}
	//Add implementation
	std::cout << "Barracks (B) " << std::endl;
	std::cout << "    Level: " << otherBuildingsLevels[0] << std::endl;
	std::cout << "    Max training capacity: " << barracksCapacity << "\n\n\033[;0m";


}
//Fix this-- add distintion between resource buildings and other types
int Provinces::getBuildingLevel(int index)
{
	return resourceBuildingsLevels[index];
}
void Provinces::updateBuildingsProduction()
{
	for (int x = 0; x < 5; x++)
	{
		resourceBuildingsProduction[x] = resourceBuildingsLevels[x] * RESOURCE_PRODUCTION[x];
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

void Provinces::compileProvinceStats (std::array<std::array<int, 5>, 7> &provinceStatsArray, bool &isACapitalArg, std::array<std::vector<int>, 7> &otherStats, std::string &unitNameArg, std::unordered_map<std::string, CommanderProfile*> &commandersArg)
{
	unitNameArg = unitName;
	isACapitalArg = isACapital;
	

	provinceStatsArray[0] = resourcesPresent;
	provinceStatsArray[1] = troopsPresent;
	provinceStatsArray[2] = troopsInjured;
	provinceStatsArray[3] = troopsLost;
	provinceStatsArray[4] = resourceBuildingsLevels;
	provinceStatsArray[5] = resourceBuildingsProduction;
	provinceStatsArray[6] = maxResources;

	
	otherStats[0] =  {CP, totalTroops, troopsTrainedThisTurn}; //Troop Stuff

	otherStats[1] =  {xCoord, yCoord};
	otherStats[2] =  {participantIndex, unitLevel};
	otherStats[3] =  {maxGarrison, maxInfirmaryCapacity};
	
	std::vector <int >newVector;
	for (int x: otherBuildingsLevels)
		newVector.push_back(x);
	otherStats[4] =  newVector;
	
  otherStats[5] =  {totalMaxResources, foodConsumption};
	otherStats[6] =  {scoutReportTurn, scoutReportLogLevel, logAccuracy};

	commandersArg = commanders;


	//Commander stuff
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