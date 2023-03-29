#ifndef PLAYERACTION_H
#define PLAYERACTION_H

#include <iostream>
#include <cmath>

#include "Units/Participants.h"
#include "ArmyOverviewMA.h"
#include "Miscellaneous/Lists.h"
#include "BuildMA.h"
#include "TrainMA.h"
#include "Miscellaneous/OtherFunctions.h"
#include "MapMA.h"

class PlayerAction
{
public:
	PlayerAction();
	PlayerAction(Participants *newP);
	char randomAction();
	void initialDecision();
	void pauseGame();
private:
	Participants *participant;
	OtherFunctions OF;
};

#endif