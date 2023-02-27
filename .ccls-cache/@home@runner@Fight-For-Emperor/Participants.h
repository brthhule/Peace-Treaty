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

	//Commander stuff
	int commandersNum();
	int findCommanderIndex(CommanderProfile *commander);
	void addCommander();
	CommanderProfile* getCommander(int index);
	int getMaxCommanders ();
	std::vector <int> getTrainCosts();
	bool hasCommander(std::string name);
	CommanderProfile* getCommanderName(std::string name);
			
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

	//Coordinate stuff
	
	Provinces* getCoords(int identifier);
	int getRandomCoordinate();

private:
	std::string kingdomName = " ";
	bool playerStatus;//true = player, false = AI

	std::vector <Provinces*> provincesList;
	std::vector <CommanderProfile*> commandersList;
	int capitalIndex;

	//Figure out sizes later
	int AIMainAction [5];
	int AIBuildMA [2];
	int AITroopMA [3];
std::vector <int> trainCosts = {5, 4, 3, 2, 1};
	int maxCommanders;
	int participantIndex;

	std::vector <int> troopsLost = { 0,0,0,0,0 };
	std::vector <int> totalUnits = { 0,0,0,0,0 }; /*0) Militia, 1) Guards, 2) Cavalry, 3) 
Knights, 4) Paladins*/
};

#endif
