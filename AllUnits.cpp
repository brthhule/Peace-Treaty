#include "AllUnits.h"

//Constructor
AllUnits::AllUnits(int index)
{
	for (int x = 0; x < 5; x++)
	{
		resourcesPresent[x] = initialStats[x];
		troopsPresent[x] = 0;
		troopsInjured[x] = 0;
	}
	CP = 0;
	totalTroops = 0;
	foodConsumption = 0;
	canSelectThisUnit = 'N';
	participantIndex = index;
	resourcesPresent, troopsPresent, troopsInjured, troopsLost = {0, 0, 0, 0, 0};

}

//Accessor Functions

int AllUnits::getTroopsPresent(int troopTypeIndex){
	return troopsPresent[troopTypeIndex];
}

std::vector <int> AllUnits::getAllTroopsPresent(){
	return troopsPresent;
}

void AllUnits::removeTroops(std::vector<int>troops){
	troopsPresent = OF.subtractVectors(troopsPresent, troops);
}

void AllUnits::removeSpecificTroop(int troopIndex, int troopAmount){
	troopsPresent[troopIndex] -= troopAmount;
}

void AllUnits::addTroops(int troopsAdd[5]){
	for (int x = 0; x < 5; x++)
		troopsPresent[x] += troopsAdd[x];
}

void AllUnits::addSpecificTroop(int index, int amount){
	troopsPresent[index] += amount;
}

void AllUnits::addSpecificInjuredTroop(int troopIndex, int amount){
	troopsInjured[troopIndex] += amount;
}

void AllUnits::addInjuredTroops(std::vector<int> troops){
	troopsInjured = OF.addVectors(troopsInjured, troops);
}

int AllUnits::getCP(){
	CP = 0;
	for (int x = 0; x < 5; x++){
		CP += troopsPresent[x] * troopsCP[x];
	}
	return CP;
}

int AllUnits::getParticipantIndex()
{
	return participantIndex;
}

void AllUnits::printResources()
{
	std::cout << "Resources currently present in this " << isCommanderOrProvince << ": \n";
    std::cout << "\033[;34m";
	for (int x = 0; x < 5; x++)
	{
		std::cout << "- " << provinceResourcesNames[x] << ": " << resourcesPresent[x] <<  std::endl;
	}
	std::cout <<  std::endl;
	std::cout << "\033[;0m";
}

std::string AllUnits::getUnitName()
{
	return unitName;
}
void AllUnits::changeUnitName(std::string name)
{
	unitName = name;
}

//Mutator Functions


void AllUnits::changeResource(int index, int amount, int direction)
{
	if (direction == 1)
	{
		resourcesPresent[index] += amount;
	}
	else
	{
		resourcesPresent[index] -= amount;
	}
}
void AllUnits::changeResources(std::vector<int> resources, int direction)
{
	for (int x = 0; x < 5; x++)
	{
		if (direction == 1)
			resourcesPresent[x] += resources[x];
		else
			resourcesPresent[x] -= resources[x];
	}
}

int AllUnits::returnLevel()
{
	return unitLevel;
}

void AllUnits::printOutputCoordinates()
{
	std::cout << "(" << translateX(false) <<", " << translateY(false) << ")";
}

int AllUnits::translateX(bool isInput)
{
	if (isInput)
	{
		return xCoord - 1;
	} else
	{
		return xCoord + 1;
	}
}

int AllUnits::translateY(bool isInput)
{
	if (isInput)
	{
		return abs(yCoord - continentSize);
	} else
	{
		return abs(continentSize - yCoord);
	}
}

std::vector<int> AllUnits::returnCoordinates()
{
	return {xCoord, yCoord};
}

int AllUnits::returnCoordinate(char which)
{
	switch (which)
	{
		case 'X':
			return xCoord;
			break;
		case 'Y':
			return yCoord;
			break;
	}
}

void AllUnits::addSpecificTroopLost(int index, int amount)
{
	troopsLost[index] += amount;
}
void AllUnits::addTroopsLost(std::vector<int> troopsLostVector)
{
	troopsLost = OF.addVectors(troopsLost, troopsLostVector);
}
std::vector<int> AllUnits::getTroopsLost()
{
	return troopsLost;
}

void AllUnits::addSpecificResource(int index, int amount)
{
	resourcesPresent[index] += amount;
}

void AllUnits::addResources(std::vector<int> resourcesVector)
{
	resourcesPresent = OF.addVectors(resourcesPresent, resourcesVector);
}

void AllUnits::subtractSpecificResource (int index, int amount)
{
	resourcesPresent[index] -= amount;
}

void AllUnits::subtractResources(std::vector<int> resourcesVector)
{
	resourcesPresent = OF.subtractVectors(resourcesPresent, resourcesVector);
}