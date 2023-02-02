#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#include <iostream>
#include <vector>

#include "CommanderProfile.h"
#include "Provinces.h"

using namespace std;

class Participants
{
public:
	//constructors
	Participants();

	//Capital stuff
	Provinces* getCapital();
	void setCapital(Provinces *newProvince);

	//Commander stuff
	int commandersNum();
	int findCommanderIndex(CommanderProfile *commander);
	void addCommander();
			
	//Province stuff
	int provincesNum();
	Provinces *findProvince(int x, int y);
	void addProvince(Provinces *newProvince);

	//Create participant
	void setKingdomName(string newName);
	string getKingdomName();
	void initialCapRSS();
	void createCapital();
	void setKingdomName ();
  bool isAlive();
	bool isPlayer();
	void createAsPlayer (bool choice);
	void viewStats();
	vector<int> calculatePlayerValues (int decision);
	Provinces *getProvince (int index);
	
	int findAllUnits();//Create funciton
	vector <int> troopsLost = { 0,0,0,0,0 };
	vector <int> totalUnits = { 0,0,0,0,0 }; /*0) Militia, 1) Guards, 2) Cavalry, 3) 
Knights, 4) Paladins*/

private:
	string kingdomName = " ";
	bool playerStatus;//true = player, false = AI

	vector <Provinces*> provincesList;
	vector <CommanderProfile*> commandersList;
	int capitalIndex;

	//Figure out sizes later
	int AIMainAction [5];
	int AIBuildMA [2];
	int AITroopMA [3];

	int pMaxCommanders;

};
#endif