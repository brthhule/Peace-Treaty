#ifndef SCOUTMA_H
#define SCOUTMA_H

#include <vector>
#include <iostream>

using namespace std;

class ScoutMA
{
public:
    //Constructors
    ScoutMA(int targetXCoordinateV, int targetYCoordinateV);

    //Functions
    void selectTargetToScout();
    void playerScoutStepTwo();
    vector <int> showUnitsCanScout();
    void scoutLogCalculationsProvince(int accuracy);

private:
    int targetXCoordinate;
    int targetYCoordinate;
    vector<int> commandersCanSelect;
    vector <int> provincesCanSelectX;
    vector <int> provincesCanSelectY;
    vector<int> unitLevels;

    int targetInformation[2];//[0] is for whether it is a province (1) or commander (2); [1] is the index of the unit in its Participants object
    int targetParticipantIndex;
    int enemyLevel;
};



#endif