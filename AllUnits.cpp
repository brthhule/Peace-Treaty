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
	totalCP = 0;
	totalTroops = 0;
	foodConsumption = 0;
	canSelectThisUnit = 'N';
	participantIndex = index;

}

//Accessor Functions

int AllUnits::getTroopsPresent(int troopTypeIndex)
{
	return troopsPresent[troopTypeIndex];
}
int AllUnits::getCP()
{
	CP = 0;
	for (int x = 0; x < 5; x++)
	{
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


std::vector<int> AllUnits::addVectors(std::vector<int> primeVector, std::vector<int> secondaryVector)
{
	for (int x = 0; x < primeVector.size(); x++)
		primeVector[x] += secondaryVector[x];
	return primeVector;
}
std::vector<int> AllUnits::subtractVectors(std::vector<int> primeVector, std::vector<int> secondaryVector)
{
	for (int x = 0; x < primeVector.size(); x++)
		primeVector[x] -= secondaryVector[x];
	return primeVector;
}