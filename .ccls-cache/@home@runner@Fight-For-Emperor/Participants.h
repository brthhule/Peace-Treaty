#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#include <iostream>
#include <vector>

#include "CommanderProfile.h"
#include "Provinces.h"


class Participants
{
public:
    //constructors
    Participants();

    //Accessors
    int getCapitalCoordinate(int whichCoordinate);
    int findProvinceWithCoordinates(int provinceXCoordinate, int provinceYCoordinate);
    char returnGetProvinceIdentifier(int xCoordinate, int yCoordinate);
    char getCommanderIdentifier(int index);
    CommanderProfile *returnCommander(int index);
    Provinces *returnProvince(int index);
    int howManyProvinces();
    int howManyCommanders();


    //Mutators
    void updateCapitalCoordinates(int whichCoordinate, int value);
    void addCommander(CommanderProfile &newCommanderProfile);
    void addProvince(Provinces newProvince);
    void addResourcesToProvince(int provinceXCoordinate, int provinceYCoordinate, int resourceIndex, int resourceAmount);
    void removeCommanderIdentifier(int index);
    void updateCommanderIdentifiers();
    void clearCanSelectThisUnit();

    //Public variables
    int* participantCapitalX = &capitalCoordinates[0];
    int* participantCapitalY = &capitalCoordinates[1];
    int capitalCoordinates[2];
    vector <char> commanderIdentifiersList;
    vector <char> commanderIdentifiers;

private:
    vector <CommanderProfile> listOfCommanders;
    vector <Provinces> listOfProvinces;//Includes the capital province in this
    char generalCommanderIdentifiers[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    

};
#endif