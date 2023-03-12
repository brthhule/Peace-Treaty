#ifndef PROVINCES_H
#define PROVINCES_H

#include "AllUnits.h"
#include "CommanderProfile.h"
#include "unordered_map"


extern std::string provinceResourcesNames[5];
extern std::string buildingNames[6];
extern std::string troopNames[5];
extern int provinceBuildingsProductionNumbers[6];
extern int initialResources[5];
extern int troopsCP[5];
extern int turn;
extern int continentSize;

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
  int findMaxInfirmaryCapacity() { return (otherBuildingLevels[1] * 10); };
  int getBuildingLevel(int index);
  void increaseBuildingLevel(int index, int amount);


  // Commanders
  CommanderProfile* returnCommander (std::string name);
  int findProvinceLevel();
  void addCommander(CommanderProfile *newCommander);
	void removeCommander(CommanderProfile *newCommander);
	std::vector <CommanderProfile*> returnAllCommmanders();
	int commandersNum(){return commanders.size();};

	/*Training*/
  int getTroopsTrainedThisTurn() { return troopsTrainedThisTurn; };
  void addTroopsTrainedThisTurn(int amount);
  void resetTroopsTrainedThisTurn();



	/*Resources*/
	bool subtractCheckResources(std::array<int, 5> resourcesArray);
std::vector<int> getTotalResources();

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
	int initialStats[5] = {5, 4, 3, 2, 1};

	/*Identity*/

	/*Garrison*/
  int maxGarrison;
  int maxInfirmaryCapacity;
  int resourceBuildingsLevels[5];
  int resourceBuildingsProduction[5];
	int otherBuildingLevels[2];
	
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