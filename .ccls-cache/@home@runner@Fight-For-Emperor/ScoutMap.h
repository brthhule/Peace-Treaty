#ifndef SCOUTMAP_H
#define SCOUTMAP_H

#include <iostream>
#include <vector>
#include "Provinces.h"
#include "CommanderProfile.h"

class ScoutMap
{
public:
	ScoutMap();
	ScoutMap(int continentSize);

private:
	std::vector<std::vector<Provinces>> newScoutMap;
	
};

#endif