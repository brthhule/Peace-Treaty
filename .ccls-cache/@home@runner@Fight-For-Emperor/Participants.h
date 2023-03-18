#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#include <iostream>
#include <vector>
#include "Provinces.h"
#include "CommanderProfile.h"
#include "OtherFunctions.h"

#include <string.h>
#include <string>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>  
#include <ctime>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <map>
#include <unordered_map>

#include "AllUnits.h"

extern int provinceBuildingsProductionNumbers[6];
extern int continentSize;
extern int troopsCP[5];
extern int currentParticipantIndex;
extern int initialResources [5];
extern std::vector <std::vector <Provinces>> provincesMap;


class Participants
{
public:
	//constructors
	Participants();


	//Capital stuff
	Provinces* getCapital();
	void setCapital(Provinces *newProvince);
	std::string getNewName ();
	void showMap();

	//Commander stuff
	int commandersNum();
	void addCommander();
	CommanderProfile* getCommander(int index);
	int getMaxCommanders ();
	std::array<int, 5> getTrainCosts();
	bool hasCommander(std::string name);
	CommanderProfile* getCommanderByName(std::string name);
  std::unordered_map<std::string, CommanderProfile*> getCommandersMap(){return commandersList;}
			
	//Province stuff
	int provincesNum();
	Provinces *findProvince(int x, int y);
	void addProvince(Provinces *newProvince);
	Provinces *getProvince (int index);
	void printListOfProvinces();


	//Create participant
	void setKingdomName(std::string newName);
	std::string getKingdomName();
	void initialCapRSS();
	void createCapital();
	int findAllUnits();//Create funciton
	void setParticipantIndex(int num);
	int getParticipantIndex();

	//AI
	void createAsPlayer (bool choice);
	bool isAlive();
	bool isPlayer();

	//Stats
	std::vector<int> calculatePlayerValues (int decision);
	void viewAllStatsFunction();
	void viewStats();
	int calculateTotalUnits ();
	std::vector<int> calculateEachUnit();
	int calculateTotalResources();
	std::vector<int> calculateEachResource();
	int calculateTotalTroopsLost();
	std::vector<int> calculateEachTroopLost();

	int calculateTotals (int option);
	std::array<int, 5> calculateEach(int option);


	//Coordinate stuff
	
	Provinces* getCoords(int identifier);
	Provinces* getYourProvince(int identifier);
	int getRandomCoordinate();

	//Scout stuff
	void scoutProvince(Provinces *targetProvince, int accuracy);

	void printParticipantStats(int option);
  


private:
	std::string kingdomName = " ";
	bool playerStatus;//true = player, false = AI

	std::vector <Provinces*> provincesList;
	std::unordered_map <std::string, CommanderProfile*> commandersList;
	int capitalIndex;

	//Figure out sizes later
	int AIMainAction [5];
	int AIBuildMA [2];
	int AITroopMA [3];
std::array <int, 5> trainCosts = {5, 4, 3, 2, 1};
	int maxCommanders;
	int participantIndex;

	std::array <int, 5> troopsLost = { 0,0,0,0,0 };
	std::vector<std::vector<Provinces>> scoutMap;
	OtherFunctions OF;
  std::unordered_map<std::string, CommanderProfile*>::iterator it;
};

#endif
