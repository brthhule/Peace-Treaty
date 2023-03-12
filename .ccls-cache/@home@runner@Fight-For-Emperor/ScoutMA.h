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
  void selectTarget();
  void playerScoutStepTwo();
  int selectUnitToScout(std::string &unitName, bool &isProvince, std::array<int, 2> coordinates);
  void scoutLogCalculationsProvince(int accuracy);
	void getCanScout();
	bool checkHasUnit (std::string unitName);

private:
  std::vector<CommanderProfile*> commandersCanScout;
  std::vector<Provinces *> provincesCanScout;
  std::vector<int> unitLevels;

  int targetInformation[2]; //[0] is for whether it is a province (1) or
                            //commander (2); [1] is the index of the unit in its
                            //Participants object
  int enemyLevel;
  Participants *participant;
	Participants* targetParticipant;

  Provinces *yourProvince;
	Provinces* targetProvince;
	OtherFunctions OF;
};

#endif