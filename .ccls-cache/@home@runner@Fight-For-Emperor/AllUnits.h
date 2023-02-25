#ifndef ALLUNITS_H
#define ALLUNITS_H

#include <string>
#include <iostream>

/*int resourcesPresent[5];
	int troopsPresent[5];
	int troopsInjured[5];
	int totalCP;*/

extern int troopsCP[5];
extern int provinceBuildingsProductionNumbers[6];

extern std::string provinceResourcesNames[5];
extern std::string buildingNames[6];
extern std::string troopNames[5];
extern int currentParticipantIndex;//Fix this at some point-- make sure right index is sent to constructor

class AllUnits
{
public:
	//constructor
	AllUnits();
	AllUnits(int index);

	int getCommanderArmyCP();
	int getTroopsPresent(int troopTypeIndex);
	int getTotalCP();
	int getParticipantIndex();
	

	//Troops Functions
	void removeTroops(int troopIndex, int troopAmount);
	void addInjuredTroops(int troopIndex, int troopAmount);
	void addTroops(int troopsAdd[5]);
	void addSpecificTroop(int index, int amount);

  //resources
	void addRSS(int index, int amount);
	int getResource(int resourceIndex);
	void printResources();

	void changeUnitName(std::string name);
  std::string getUnitName();

protected:
	int resourcesPresent[5];
	int troopsPresent[5];
	int troopsInjured[5];
	int totalCP;
	int totalTroops;
	int foodConsumption;

	int initialStats[5] = { 5, 4, 3, 2, 1 };

  //Coordinates;
	int xCoord = 0;
	int yCoord = 0;
	char canSelectThisUnit;
	int participantIndex;
	std::string unitName;
};

#endif