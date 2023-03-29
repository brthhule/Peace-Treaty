#ifndef PLAYERACTION_H
#define PLAYERACTION_H

#include <iostream>
#include <cmath>

#include "MA/ArmyOverviewMA.h"
#include "MA/BuildMA.h"
#include "MA/TrainMA.h"
#include "MA/MapMA.h"

#include "MA/Units/Participants.h"

#include "MA/Units/Misc/OtherFunctions.h"
#include "MA/Units/Misc/showText.h"

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