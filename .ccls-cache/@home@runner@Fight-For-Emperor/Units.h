#ifndef UNITS_H
#define UNITS_H

#include <iostream>
#include <vector>
#include "textFunctions.h"
#include "coordinateFunctions.h"

using namespace std;

using namespace std;



class AllUnits
{
public:
	//constructor
	AllUnits(Participants *part);

	int getCommanderArmyCP();
	int getTroopsPresent(int troopTypeIndex);
	int getTotalCP();
	Participants *participantBelong();
	

	//Troops Functions
	void removeTroops(int troopIndex, int troopAmount);
	void addInjuredTroops(int troopIndex, int troopAmount);
	void addTroops(int troopsAdd[5]);
	void addSpecificTroop(int index, int amount);

  //resources
	void addRSS(int index, int amount);
	int getResource(int resourceIndex);
	void printResources();

	void changeUnitName(string name);
  string getUnitName();

protected:
	int resourcesPresent[5];
	int troopsPresent[5];
	int troopsInjured[5];
	int totalCP;
	int totalTroops;
	int fooParticdConsumption;

	int initialStats[5] = { 5, 4, 3, 2, 1 };

  //Coordinates;
	int xCoord = 0;
	int yCoord = 0;
	char canSelectThisUnit;
	Participants *participant;//Participant index of the Participant object a unit belongs to
	string unitName;
};

class CommanderProfile: public AllUnits
{
public:
	//Constructors
	CommanderProfile();
	CommanderProfile(int commanderLevel, string name);
	//Destructor
	~CommanderProfile();


	//Accessor functions

	//Stats stuff
	int getCommanderStat(int index);
	void printCommanderStats();
	void changeCommanderStat(int index, int amount);
	void setLocation (Provinces *newProvince);

	//Scout report stuff 
	void updateCommanderScoutReport(int index, int value);
	void completeCommanderScoutReport(int accuracy);
	int printCommanderScoutReport(int idex);

	//Other commander stuff
	int getCommanderLevel();
	void addCommanderLevel(int amount);

	//Moving
	void moveUnit();
	vector <Provinces*> moveUnitOne ();
	char hasCommanderMoved();
	void resetCommanderMoved();

private:
	int* commanderArmyStats[20];/*
[0] = food the army possesses    Resources
[1]  = wood
[2] = ore
[3] = gold
[4] = mana
[5] = militia present            Troops Present
[6] = guards present
[7] = cavalry present
[8] = knights present
[9]  = paladins present
[10] = militia injured            Troops Injured
[11] = guards injured
[12] = cavalry injured
[13] = knights injured
[14] = paladins injured
[15] = total troops               Miscellaneous stats
[16] = totalCP
[17] = leaderLevel
[18] = maxTroops
[19] = food consumption
*/
	int commanderLevel;
	int commanderScoutReport[22];/*
[0] = food the army possesses    Resources
[1]  = wood
[2] = ore
[3] = gold
[4] = mana
[5] = militia present            Troops Present
[6] = guards present
[7] = cavalry present
[8] = knights present
[9]  = paladins present
[10] = militia injured            Troops Injured
[11] = guards injured
[12] = cavalry injured
[13] = knights injured
[14] = paladins injured
[15] = total troops               Miscellaneous stats
[16] = totalCP
[17] = leaderLevel
[18] = maxTroops
[19] = food consumption
[20] = turn number of scout report
[21] = accuracy of scout report*/
	int maxTroops;//check
	int totalMaxResources;
	char hasMoved;

	string MANDescriptions[5] = { "Resources in", "Troops present in", "Troops injured in", "Other stats of" };//check
	string namesOfMAN[20];//check
	Provinces *provinceLocation;
};

class Provinces : public AllUnits
{
public:
	/*Constructors*/
	Provinces();
	Provinces(int xCoordinate, int yCoordinate, Participants *newParticipant);

	/*Destructor*/

	/*Accessor Functions*/
	int getProvinceStats(int index);
	int findProvinceScoutLog(int index);
	int findMaxGarrison();
	int findMaxInfirmaryCapacity();
	int getBuildingLevel(int index);

	int returnCommanderIndex(int index);
	int getTroopsTrainedThisTurn();
	int findProvinceLevel();

	void printBuildingStats();
	char isProvinceACapitalQuestion();

	string getProvinceName();
  void setDeleteProvince ()
  {
    deleteProvince = true;
  }
	/*Mutator Functions*/
	void updateProvinceScoutLog(int index, int value);
	void updateBuildingsProduction();
	void updateProvinceResources();
	void setCoordinates(int xCoordinate, int yCoordinate);
	void provinceIsACapital();
	void addCommanderProvince(int commanderIndex);
	void removeCommanderProvince(int commanderIndex);
	void changeParticipant (Participants &part);
	void resetTroopsTrainedThisTurn();
	void increaseBuildingLevel(int index, int amount);
	void completeProvinceScoutReport(int accuracy);
  void addTroopsTrainedThisTurn(int amount);

  int getCoordinate(char identifier);
  string printCoordinates();
  bool deleteStatus();

  



	//public variables
	vector <int> commandersPresentIndex;
	int scoutLogTurnLevel[2];//[0] is the turn of the scout report, [1] is the scout log level


	//from AllUnits
	//Accessor Functions

private:
	int* provinceStats[27];/*
[0] food present
[1] wood present
[2] ore present
[3] gold present
[4] mana present
[5] max resources province can hold
[6] garrisoned militia
[7] garrisoned guards
[8] garrisoned cavalry
[9] garrisoned knights
[10] garrisoned paladins
[11] max garrison
[12] injured malitia
[13] injured guards
[14] injured cavalry
[15] injured knights
[16] injured paladins
[17] max infirmary capacity
[18] farm level
[19] lumber mill level
[20] quarry level
[21] mine level
[22] church level
[23] barracks level
[24] infirmary level
[25] total CP
[26] food consumption*/
	int provinceLevel;
	int maxGarrison;
	int maxInfirmaryCapacity;
	int buildingLevels[7];
	int buildingsProduction[6];
	int maxResources[5];
	int totalMaxResources;
	int troopsTrainedThisTurn;

	int troopsPresent[5];
	int troopsInjured[5];
	int totalCP;
	int totalTroops;
	int foodConsumption;

	int initialStats[5] = { 5, 4, 3, 2, 1 };

	bool isACapital;

	int provinceScoutReport[28] = {};/*
[27] = turn number of scout report
[28] = accuracy of scout report*/
  bool isNeutral;

  int provinceX;
  int provinceY;
  Participants *participant;
  bool deleteProvince;

};

#endif