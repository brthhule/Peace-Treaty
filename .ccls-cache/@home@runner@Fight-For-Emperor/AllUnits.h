#ifndef ALLUNITS_H
#define ALLUNITS_H

#include <string>
#include <vector>
#include <iostream>
#include <array>

#include "OtherFunctions.h"
#define UNIT_AMOUNT = 5

/*int resourcesPresent[5];
	int troopsPresent[5];
	int troopsInjured[5];
	int totalCP;*/
extern const std::array<int, 5> TROOPS_CP;
extern const std::array<int, 5> RESOURCE_PRODUCTION;
extern const std::array<std::string, 5> RESOURCE_NAMES;
extern const std::array<std::string, 5> RESOURCE_BUILDING_NAMES;
extern const std::array<std::string, 5> TROOP_NAMES;
extern int continentSize;
extern const int BARRACKS_PRODUCTION;

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
	std::array<int, 5> getAllTroopsPresent();

	void modifySpecificTroop(int index, int amount, bool isAdd);
	std::array<int, 5> modifyTroops(std::array<int, 5> troopsAdd, bool isAdd);
	void addSpecificInjuredTroop(int troopIndex, int amount);
	void addInjuredTroops(std::array<int, 5> troops);
	std::array<int,5> getAllTroopsInjured();

	void addSpecificTroopLost(int index, int amount);
	void addTroopsLost(std::array<int, 5> troopsArray);
	std::array<int, 5> getAllTroopsLost();
	int getTotalTroops ();
	int getFoodConsumption (){return foodConsumption;}

	//Provinces & Commanders
	int getLevel();

	//Coordinate Stuff
	std::array<int, 2> getCoordinates();
	int getCoordinate(char which);
	void printOutputCoordinates();
	int translateX (bool isInput);
	int translateY (bool isInput);


  //resources
	void modifySpecificResource(int index, int amount, bool isAdd);
	void modifyResources(std::array<int, 5> resourcesArray, bool isAdd);
	int getResource(int resourceIndex){return resourcesPresent[resourceIndex];}
	std::array<int,5> getAllResources ();//Add implementation
	void printResources();
	std::string printCoordinates();


	void changeUnitName(std::string name);
  std::string getUnitName();


protected:
	std::array<int, 5> resourcesPresent = {0, 0, 0, 0, 0};
	std::array<int, 5> troopsPresent = {0, 0, 0, 0, 0};
	std::array<int, 5> troopsInjured = {0, 0, 0, 0, 0};
	std::array<int, 5> troopsLost = {0, 0, 0, 0, 0};
	int CP;
	int totalTroops;
	int foodConsumption;

	const int initialStats[5] = { 5, 4, 3, 2, 1 };

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