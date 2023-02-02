#ifndef SCOUTMA_H
#define SCOUTMA_H

#include <vector>
#include <iostream>

#include "Provinces.h"
#include "Participants.h"

using namespace std;

class ScoutMA
{
public:
    //Constructors
    ScoutMA(Participants* newParticipant, Provinces *newProvince);

    //Functions
    void selectTargetToScout();
    void playerScoutStepTwo();
    vector <int> showUnitsCanScout();
    void scoutLogCalculationsProvince(int accuracy);

private:
    vector<int> commandersCanSelect;
    vector<Provinces*> provincesCanSelect();
    vector<int> unitLevels;

    int targetInformation[2];//[0] is for whether it is a province (1) or commander (2); [1] is the index of the unit in its Participants object
    int targetParticipantIndex;
    int enemyLevel;
  Participants *participant;
  Provinces *targetProvince;
};



#endif