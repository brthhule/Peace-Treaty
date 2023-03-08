#ifndef ALLUNITS_H
#define ALLUNITS_H

#include <string>
#include <vector>
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
extern int currentParticipantIndex;

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
	void addSpecificTroop(int index, int amount){troopsPresent[index] += amount;}
	void addTroops(int troopsAdd[5]){for (int x = 0; x < 5; x++)
		troopsPresent[x] += troopsAdd[x];}
	void removeSpecificTroop(int troopIndex, int troopAmount){troopsPresent[troopIndex] -= troopAmount;}
	void removeTroops(std::vector<int>troops){
		troopsPresent = subtractVectors(troopsPresent, troops);
	}
	void addSpecificInjuredTroop(int troopIndex, int troopAmount){troopsInjured[troopIndex] += troopAmount;}
	void addInjuredTroops(std::vector<int> troops){troopsInjured = addVectors(troopsInjured, troops);}


  //resources
	void changeResource(int index, int amount, int direction);
	void addResource(int index, int amount){resourcesPresent[index] += amount;}
	void subtractResource (int index, int amount)
{resourcesPresent[index] -= amount;}
	void changeResources(std::vector<int> resources, int direction);
	int getResource(int resourceIndex){return resourcesPresent[resourceIndex];}
	std::vector <int> getAllResources () {return resourcesPresent;}
	void printResources();

	void changeUnitName(std::string name);
  std::string getUnitName();
	std::vector<int> addVectors(std::vector<int> primeVector, std::vector<int> secondaryVector);
	std::vector<int> subtractVectors(std::vector<int> primeVector, std::vector<int> secondaryVector);
protected:
	std::vector<int> resourcesPresent;
	std::vector<int> troopsPresent;
	std::vector<int> troopsInjured;
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
};

#endif