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

#define UNIT_AMOUNT 5

extern std::vector <std::vector <Provinces>> provincesMap;
extern std::vector <Participants> participantsList;
extern const std::array<std::string, UNIT_AMOUNT> TROOP_NAMES;
extern const std::array<std::string, UNIT_AMOUNT> RESOURCE_NAMES;
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

