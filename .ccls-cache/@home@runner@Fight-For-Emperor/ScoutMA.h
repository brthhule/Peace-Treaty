#ifndef SCOUTMA_H
#define SCOUTMA_H

#include <vector>
#include <iostream>

using namespace std;

class ScoutMA
{
public:
    //Constructors
    ScoutMA (int targetXCoordinateV, int targetYCoordinateV);
    //Functions
    void playerScout();
private:
    int targetXCoordinate;
    int targetYCoordinate;

};


vector <int> showUnitsCanScout();
void scoutLogCalculationsProvince(int accuracy);

#endif