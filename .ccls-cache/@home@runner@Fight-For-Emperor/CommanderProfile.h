#ifndef COMMANDERPROFILE_H
#define COMMANDERPROFILE_H

#include <iostream>
#include "AllUnits.h"
#include "Provinces.h"
#include "textFunctions.h"

using namespace std;

class CommanderProfile : public AllUnits
{
public:
	//default constructor
	CommanderProfile();

	//Overload constructors
	CommanderProfile(int commanderLevel, char identifier, int index);

	//Destructor
	~CommanderProfile();

	//Accessor functions
	int getCommanderStat(int index);
	int printCommanderScoutReport(int idex);
	int getCommanderLevel();

	char hasCommanderMoved();
	char getCommanderIdentifier();

	void changeCoordinates(int xCoordinate, int yCoordinate);
	void printCommanderStats();

	//Mutator Functions
	void changeCommanderCoordinates(int xCoordinate, int yCoordinate);
	void changeCommanderStat(int index, int amount);
	void changeCommanderIdentifier(char identifier);
	void updateCommanderScoutReport(int index, int value);
	void addCommanderLevel(int amount);
	void resetCommanderMoved();
    void completeCommanderScoutReport(int accuracy);

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
	char commanderIdentifier;
	char hasMoved;

	string MANDescriptions[5] = { "Resources in", "Troops present in", "Troops injured in", "Other stats of" };//check
	string namesOfMAN[20];//check
};

#endif