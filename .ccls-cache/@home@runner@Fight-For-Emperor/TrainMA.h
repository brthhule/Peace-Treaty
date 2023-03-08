#ifndef TRAINMA_H
#define TRAINMA_H

#include <iostream>
#include <iostream>
#include <vector>

#include "Provinces.h"
#include "textFunctions.h"
#include "Participants.h"
#include "Lists.h"
#include "OtherFunctions.h"

extern std::vector <std::vector <Provinces>> provincesMap;
extern std::vector <Participants> participantsList;
extern std::string troopNames[5];
extern std::string provinceResourcesNames[5];
extern int currentParticipantIndex;

class TrainMA
{
public:
	//constructor
	TrainMA();
	TrainMA(Provinces *newP);
	//other functions
	void TrainMAFunction();
private:
	Provinces *province;
	OtherFunctions OF;
};

#endif

