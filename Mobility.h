#ifndef MOBILITY_H
#define MOBILITY_H

#include <iostream>
#include <vector>

#include "OtherFunctions.h"
#include "Participants.h"
#include "Provinces.h"
#include "CommanderProfile.h"

extern int continentSize;
extern std::vector<std::vector <Provinces>> provincesMap;

class Mobility
{
public:
	Mobility(CommanderProfile *sCommander, Participants *newP);
	void moveUnitOne();
	std::vector <Provinces*> moveUnitTwo ();
private:
	CommanderProfile *selectedCommander;
	Participants* participant;
	int sCommanderX;
	int sCommanderY;
};

#endif