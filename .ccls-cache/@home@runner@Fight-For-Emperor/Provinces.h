#ifndef PROVINCES_H
#define PROVINCES_H

#include <iostream>
#include <unordered_map>

#include "AllUnits.h"
#include "CommanderProfile.h"

extern const std::array<int, 5> TROOPS_CP;
extern const std::array<int, 5> RESOURCE_PRODUCTION;
extern const std::array<std::string, 5> RESOURCE_NAMES;
extern const std::array<std::string, 5> RESOURCE_BUILDING_NAMES;
extern const std::array<std::string, 5> TROOP_NAMES;
extern int continentSize;
extern const int BARRACKS_PRODUCTION;
extern const std::array<int, 5> INITIAL_VALUES;
extern int turn;

const int LOG_SIZE = 20;

class Provinces : public AllUnits {
public:
  /*Constructors*/
  Provinces();
  Provinces(int xCoordinate, int yCoordinate, int pIndex);
	void basicStats();

	/*Initialization*/
	bool isCapital(){return isACapital;};
	void setCoordinates(int xCoordinate, int yCoordinate);
  void initializeCapital(); // provinceIsACapital
  void changeParticipant(int num);

	/*Province Identity*/
	int getCoordinate(char identifier);
  bool deleteStatus();
	std::string getProvinceName();
  void setDeleteProvince() { deleteProvince = true; }

  /*Garrisons*/
  int findMaxGarrison();

	//Buildings
  int findMaxInfirmaryCapacity() { return (otherBuildingsLevels[1] * 10); };
  int getBuildingLevel(int index);
  void increaseBuildingLevel(int index, int amount);


  // Commanders
  CommanderProfile* returnCommander (std::string name);
  int findProvinceLevel();
  void addCommander(CommanderProfile *newCommander);
	void removeCommander(CommanderProfile *newCommander);
	std::vector <CommanderProfile*> returnAllCommanders();
	int commandersNum(){return commanders.size();}

	/*Training*/
  int getTroopsTrainedThisTurn() { return troopsTrainedThisTurn; };
  void addTroopsTrainedThisTurn(int amount);
  void resetTroopsTrainedThisTurn();



	/*Resources*/
	bool subtractCheckResources(std::array<int, 5> resourcesArray);
  std::array<int,5> getTotalResources();

	/*Stats*/
  void printBuildingStats();
	int getTotalCP ();
	void updateBuildingsProduction();
  void updateProvinceResources();

	/*Scout Stuff*/
	void completeProvinceScoutReport(int accuracy);
	int getScoutReportTurn(){return scoutReportTurn;}
	int getScoutLogTurnLevel(){return scoutReportLogLevel;}
	void compileProvinceStats (int (&provinceStatsArray)[35]);

	
private:
	/*Garrison*/
  int maxGarrison;
  int maxInfirmaryCapacity;
	std::array<int, 5> resourceBuildingsLevels;
	std::array<int, 5> resourceBuildingsProduction;
	std::array<int, 4> otherBuildingsLevels;//Barracks, infirmary, Library, wall
	int barracksCapacity;
	
  int maxResources[5];
  int totalMaxResources;
  int troopsTrainedThisTurn;
  int foodConsumption;



  bool isACapital;

  int *provinceScoutReport[28];
  bool deleteProvince;

	std::unordered_map<std::string, CommanderProfile*> commanders;

	int scoutReportTurn;
	int scoutReportLogLevel;
	int logAccuracy;
};

#endif