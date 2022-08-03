#ifndef ALLUNITS_H
#define ALLUNITS_H

#include <string>
#include <iostream>
#include "otherFunctions.h"

using namespace std;

class AllUnits
{
public:
	//constructors
	AllUnits();
	AllUnits(char unitIdentifier);
	//destructor
	//Accessor Functions
	int getResource(int resourceIndex);
	int getCommanderArmyCP();
	int getTroopsPresent(int troopTypeIndex);
	void printResources();
	int getTotalCP();
	int getCoordinate(char identifier);
    int getBelongsToParticipant ();
    int returnIndexInList ();

	//Mutator Functions
	void removeTroops(int troopIndex, int troopAmount);
	void addResources(int resourceIndex, int resourceAmount);
	void addInjuredTroops(int troopIndex, int troopAmount);
	void subtractResources(int index, int amount);
	void addTroops(int troopsAdd[5]);
	void addSpecificTroop(int index, int amount);
    void resetCanSelectThisUnit();
    void changeBelongsToParticipant (int index);
    void changeIndexInList (int index);
    void changeCanSelectThisUnit();


protected:
	int resourcesPresent[5];
	int troopsPresent[5];
	int troopsInjured[5];
	int totalCP;
	int totalTroops;
	int foodConsumption;

	int initialStats[5] = { 5, 4, 3, 2, 1 };

	int unitXCoordinate = 0;
	int unitYCoordinate = 0;
    char canSelectThisUnit;
    int belongsToParticipant;//Participant index of the Participant object a unit belongs to
    int indexInList; //Index of unit in listOfCommanders or listOfParticipants in its Participants object
};

#endif