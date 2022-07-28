#include <iostream>
#include "Participants.h"

//Constructors
//Accessors
int Participants::getCapitalCoordinate (int whichCoordinate)
{
    return capitalCoordinates [whichCoordinate];//whichCoordinate = 0 for x coordinate, 1 for y
}

int Participants::findProvinceWithCoordinates (int provinceXCoordinate, int provinceYCoordinate)
{
    for (int x = 0; x < listOfProvinces.size(); x++)
    {
        if (listOfProvinces[x].getCoordinate('X') == provinceXCoordinate && listOfProvinces[x].getCoordinate('Y') == provinceYCoordinate)
        {
            return x;
        }
    }
    return -1;//If something wrong happens
}

//Mutators
void Participants::updateCapitalCoordinates (int whichCoordinate, int value)
{
    capitalCoordinates [whichCoordinate] = value;
}

void Participants::addCommander (CommanderProfile newCommanderProfile)
{
    listOfCommanders.push_back(newCommanderProfile);
}

void Participants::addProvince(Provinces newProvince)
{
    listOfProvinces.push_back (newProvince);
}

void Participants::addResourcesToProvince(int provinceXCoordinate, int provinceYCoordinate, int resourceIndex, int resourceAmount)
{
    int indexOfProvince = findProvinceWithCoordinates (provinceXCoordinate, provinceYCoordinate);
}

