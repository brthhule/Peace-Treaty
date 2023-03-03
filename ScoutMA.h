#ifndef SCOUTMA_H
#define SCOUTMA_H

#include <iostream>
#include <vector>

#include "Participants.h"
#include "Provinces.h"
#include "OtherFunctions.h"

class ScoutMA {
public:
  // Constructors
  ScoutMA(Participants *newParticipant, Provinces *newProvince);

  // Functions
  void selectTargetToScout();
  void playerScoutStepTwo();
  std::vector<int> showUnitsCanScout();
  void scoutLogCalculationsProvince(int accuracy);

private:
  std::vector<int> commandersCanSelect;
  std::vector<Provinces *> provincesCanSelect();
  std::vector<int> unitLevels;

  int targetInformation[2]; //[0] is for whether it is a province (1) or
                            //commander (2); [1] is the index of the unit in its
                            //Participants object
  int targetParticipantIndex;
  int enemyLevel;
  Participants *participant;
  Provinces *yourProvince;
	Provinces* targetProvince;
	OtherFunctions OF;
};

#endif