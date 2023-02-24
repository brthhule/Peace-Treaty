#ifndef MOBILITY_H
#define MOBILITY_H

#include <iostream>
#include <vector>

#include "Participants.h"
#include "Provinces.h"
#include "CommanderProfile.h"

extern int continentSize;
extern vector<vector <Provinces>> provincesMap;

using namespace std;

class Mobility
{
public:
	Mobility(CommanderProfile *sCommander, Participants *newP);
	void moveUnitOne();
	vector <Provinces*> moveUnitTwo ();
private:
	CommanderProfile *selectedCommander;
	Participants* participant;
	int sCommanderX;
	int sCommanderY;
};

#endif