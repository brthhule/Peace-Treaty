#ifndef MOBILITY_H
#define MOBILITY_H

#include <iostream>
#include <vector>

#include "OtherFunctions.h"
#include "Units/Participants.h"
#include "Units/Provinces.h"
#include "CommanderProfile.h"
#include "AttackMA.h"

extern int continentSize;
extern std::vector<std::vector <Provinces>> provincesMap;

class Mobility
{
public:
	Mobility(std::string commanderName, Participants *newP);
	void moveUnitOne();
	std::vector <Provinces*> moveUnitTwo ();
private:
	CommanderProfile *selectedCommander;
	Participants* participant;
	Provinces* selectedCommanderProvince;
};

#endif