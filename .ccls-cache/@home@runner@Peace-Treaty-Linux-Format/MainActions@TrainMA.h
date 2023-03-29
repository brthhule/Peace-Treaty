#ifndef TRAINMA_H
#define TRAINMA_H

#include <iostream>
#include <iostream>
#include <vector>

#include "Units/Provinces.h"
#include "Units/Participants.h"

#include "Units/Misc/textFunctions.h"
#include "Units/Misc/Lists.h"
#include "Units/Misc/OtherFunctions.h"
#include "Units/Misc/ConstValues.h"

extern std::vector <std::vector <Provinces>> provincesMap;
extern std::vector <Participants> participantsList;

extern ConstValues CV;

class TrainMA
{
public:
	//constructor
	TrainMA();
	TrainMA(Participants *newParticipant);
	//other functions
	void TrainMAFunction();
private:
	Provinces *province;
	OtherFunctions OF;
	Participants *participant;
};

#endif

