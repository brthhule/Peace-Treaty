
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
AllUnits::AllUnits(Participants *part)
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
	participant = part;

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

Participants* AllUnits::participantBelong()
{
	return participant;
}

void AllUnits::printResources()
{
	std::cout << "Resources present in this province: " << endl;
    std::cout << "\033[;34m";
	for (int x = 0; x < 5; x++)
	{
		std::cout << "- " << provinceResourcesNames[x] << ": " << resourcesPresent[x] << endl;
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

void AllUnits::addRSS(int index, int amount)
{
  resourcesPresent[index] += amount;
}

void AllUnits::addInjuredTroops(int troopIndex, int troopAmount)
{
	troopsInjured[troopIndex] += troopAmount;
}

