#include <iostream>
#include <vector>
#include "Participants.h"

using namespace std;

//Constructors
Participants::Participants()
{
    //Initialize commanderIdentifiersList to be generalCommanderIdentifiers
    for (int x = 0; x < sizeof(generalCommanderIdentifiers); x++)
    {
        commanderIdentifiersList.push_back(generalCommanderIdentifiers[x]);
    }
    capitalCoordinates[0] = 0;
    capitalCoordinates[1] = 0;
}
//Accessors
char Participants::returnGetProvinceIdentifier(int xCoordinate, int yCoordinate)
{
    int provinceIndex = findProvinceWithCoordinates(xCoordinate, yCoordinate);
    return listOfProvinces[provinceIndex].getProvinceIdentifier();
}
int Participants::getCapitalCoordinate(int whichCoordinate)
{
    return capitalCoordinates[whichCoordinate];//whichCoordinate = 0 for x coordinate, 1 for y
}
int Participants::findProvinceWithCoordinates(int provinceXCoordinate, int provinceYCoordinate)
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
char Participants::getCommanderIdentifier(int index)
{
    return commanderIdentifiersList[index];
}
CommanderProfile* Participants::returnCommander(int index)
{
    return &listOfCommanders[index];
}
Provinces* Participants::returnProvince(int index)
{
    return &listOfProvinces[index];
}
int Participants::howManyProvinces()
{
    return (int)listOfProvinces.size();
}
int Participants::howManyCommanders()
{
    return (int)listOfCommanders.size();
}

//Mutators
void Participants::updateCapitalCoordinates(int whichCoordinate, int value)
{
    capitalCoordinates[whichCoordinate] = value;
}
void Participants::addCommander(CommanderProfile &newCommanderProfile)
{
    listOfCommanders.push_back(newCommanderProfile);
}
void Participants::addProvince(Provinces newProvince)
{
    listOfProvinces.push_back(newProvince);
}
void Participants::addResourcesToProvince(int provinceXCoordinate, int provinceYCoordinate, int resourceIndex, int resourceAmount)
{
    int indexOfProvince = findProvinceWithCoordinates(provinceXCoordinate, provinceYCoordinate);
}
void Participants::removeCommanderIdentifier(int index)
{
    commanderIdentifiersList.erase(commanderIdentifiersList.begin() + index);
}
void Participants::updateCommanderIdentifiers()
{
    commanderIdentifiersList.erase(commanderIdentifiersList.begin()); /*deletes the assigned letter identifier from the letter identifier list so
                    it isn't repeated*/
    if (commanderIdentifiersList.size() == 0) /*if the lesster identifier list is empty, reset it*/
    {
        for (int x = 0; x < sizeof(generalCommanderIdentifiers); x++)
        {
            commanderIdentifiersList.push_back(generalCommanderIdentifiers[x]);
        }
        for (int x = 0; x < commanderIdentifiersList.size(); x++) /* delete any existing commander identifiers from resetted identifier
            list so it isn't used again*/
        {
            for (int y = 0; y < commanderIdentifiersList.size(); y++)/*This finds the index of the element that needs to be deleted. Potential
"fix this": modify it such that it searches for the element to delete by searching for the char rather than scanning for the index-- if element is
equal to this identifier, this one, or this one, remove it; go through playerCommanderIdentifiersList like this*/
            {
                if (commanderIdentifiersList[y] == commanderIdentifiers[x])
                {
                    commanderIdentifiersList.erase(commanderIdentifiersList.begin() + y);
                    y--;
                }
            }
        }
    }
}

void Participants::clearCanSelectThisUnit()
{
    for (int x = 0; x < listOfCommanders.size(); x++)
    {
        listOfCommanders[x].resetCanSelectThisUnit();
    }

    for (int x = 0; x < listOfProvinces.size(); x++)
    {
        listOfProvinces[x].resetCanSelectThisUnit();
    }
}