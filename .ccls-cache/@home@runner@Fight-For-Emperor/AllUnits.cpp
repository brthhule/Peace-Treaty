
#include <string>
#include <iostream>
#include "AllUnits.h"
#include "CommanderProfile.h"
#include "Provinces.h"

using namespace std;
/*int resourcesPresent[5];
	int troopsPresent[5];
	int troopsInjured[5];
	int totalCP;*/

extern int troopsCP[5];
extern int provinceBuildingsProductionNumbers[6];

extern string provinceResourcesNames[5];
extern string buildingNames[6];
extern string troopNames[5];
extern int currentParticipantIndex;//Fix this at some point-- make sure right index is sent to constructor

//Constructor
AllUnits::AllUnits()
{
	for (int x = 0; x < 5; x++)
	{
		resourcesPresent[x] = 0;
		troopsPresent[x] = 0;
		troopsInjured[x] = 0;
	}
	totalCP = 0;
	totalTroops = 0;
	foodConsumption = 0;
	canSelectThisUnit = 'N';
	belongsToParticipant = currentParticipantIndex;
	indexInList = 0;//Fix this
}
AllUnits::AllUnits(char unitIdentifier)
{
	for (int x = 0; x < 5; x++)
	{
		resourcesPresent[x] = initialStats[x];
		troopsPresent[x] = 0;
		troopsInjured[x] = 0;
	}
	totalCP = 0;
	totalTroops = 0;
	foodConsumption = 0;
	canSelectThisUnit = 'N';
	indexInList = 0;//Fix this
	belongsToParticipant = currentParticipantIndex;

}



//Accessor Functions
int AllUnits::getResource(int resourceIndex)
{
	return resourcesPresent[resourceIndex];
}
int AllUnits::getCommanderArmyCP()
{
	return totalCP;
}
int AllUnits::getTroopsPresent(int troopTypeIndex)
{
	return troopsPresent[troopTypeIndex];
}
int AllUnits::getTotalCP()
{
	int totalCP = 0;
	for (int x = 0; x < 5; x++)
	{
		totalCP += troopsPresent[x] * troopsCP[x];
	}
	return totalCP;
}
int AllUnits::getCoordinate(char identifier)
{
	switch (identifier)
	{
	case 'X':
		return unitXCoordinate;
	case 'Y':
		return unitYCoordinate;
	default:
		return '-1';//in case something bad happen
	}
}
int AllUnits::getBelongsToParticipant()
{
	return belongsToParticipant;
}
int AllUnits::returnIndexInList()
{
	return indexInList;
}

void AllUnits::printResources()
{
	std::cout << "Resources present in this province: " << endl;
    std::cout << "\033[;34m";
	for (int x = 0; x < 5; x++)
	{
		cout << "- " << provinceResourcesNames[x] << ": " << resourcesPresent[x] << endl;
	}
	std::cout << endl;
	cout << "\033[;0m";
}

string AllUnits::getUnitName()
{
	return unitName;
}
void AllUnits::changeUnitName(string name)
{
	unitName = name;
}

//Mutator Functions
void AllUnits::addTroops(int troopsAdd[5])
{
	for (int x = 0; x < 5; x++)
	{
		troopsPresent[x] += troopsAdd[x];
	}
}
void AllUnits::addSpecificTroop(int index, int amount)
{
	troopsPresent[index] += amount;
}
void AllUnits::removeTroops(int troopIndex, int troopAmount)
{
	troopsPresent[troopIndex] -= troopAmount;
}

void AllUnits::addResources(int resourceIndex, int resourceAmount)
{

}
void AllUnits::subtractResources(int index, int amount)
{
	resourcesPresent[index] -= amount;
}

void AllUnits::addInjuredTroops(int troopIndex, int troopAmount)
{
	troopsInjured[troopIndex] += troopAmount;
}

void AllUnits::changeBelongsToParticipant(int index)
{
	belongsToParticipant = index;
}
void AllUnits::changeIndexInList(int index)
{
	indexInList = index;
}
void AllUnits::changeCanSelectThisUnit()
{
	canSelectThisUnit = 'Y';
}

