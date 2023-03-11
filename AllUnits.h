#ifndef ALLUNITS_H
#define ALLUNITS_H

#include <string>
#include <vector>
#include <iostream>
#include "OtherFunctions.h"

/*int resourcesPresent[5];
	int troopsPresent[5];
	int troopsInjured[5];
	int totalCP;*/
extern int troopsCP[5];
extern int provinceBuildingsProductionNumbers[6];

extern std::string provinceResourcesNames[5];
extern std::string buildingNames[6];
extern std::string troopNames[5];
extern int continentSize;

class AllUnits
{
public:
	//constructor
	AllUnits();
	AllUnits(int index);

	int getCP();
	int getParticipantIndex();
	

	//Troops Functions
	int getTroopsPresent(int troopTypeIndex);
	std::vector <int> getAllTroopsPresent();
	void addSpecificTroop(int index, int amount);
	void addTroops(int troopsAdd[5]);
	void removeSpecificTroop(int troopIndex, int troopAmount);
	void removeTroops(std::vector<int>troops);
	void addSpecificInjuredTroop(int troopIndex, int amount);
	void addInjuredTroops(std::vector<int> troops);
	int returnLevel();
	int returnCoordinate(char which);
	void addSpecificTroopLost(int index, int amount);
	void addTroopsLost(std::vector<int> troopsLostVector);
	std::vector<int> getTroopsLost();
	std::vector<int> returnCoordinates();


	void printOutputCoordinates();
	int translateX (bool isInput);
	int translateY (bool isInput);
  //resources
	void changeResource(int index, int amount, int direction);
	void addSpecificResource(int index, int amount);
	void addResources(std::vector<int> resourcesVector);
	void subtractSpecificResource (int index, int amount);
	void subtractResources(std::vector<int> resourcesVector);
	void changeResources(std::vector<int> resources, int direction);
	int getResource(int resourceIndex){return resourcesPresent[resourceIndex];}
	std::vector <int> getAllResources () {return resourcesPresent;}
	void printResources();

	void changeUnitName(std::string name);
  std::string getUnitName();
protected:
	std::vector<int> resourcesPresent;
	std::vector<int> troopsPresent;
	std::vector<int> troopsInjured;
	std::vector<int> troopsLost;
	int CP;
	int totalTroops;
	int foodConsumption;

	int initialStats[5] = { 5, 4, 3, 2, 1 };

  //Coordinates;
	int xCoord = 0;
	int yCoord = 0;
	char canSelectThisUnit;
	int participantIndex;
	std::string unitName;
	std::string isCommanderOrProvince;
	int unitLevel;
	OtherFunctions OF;
};

#endif