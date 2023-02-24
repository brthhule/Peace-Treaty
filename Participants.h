#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#include <iostream>
#include <vector>
#include "Provinces.h"
#include "CommanderProfile.h"

class Participants
{
public:
	//constructors
	Participants();

	#include "otherFunctions.h"
	#include "coordinateFunctions.h"

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
