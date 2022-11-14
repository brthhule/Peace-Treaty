#include <iostream>
#include <vector>
#include "Participants.h"

using namespace std;
extern int currentParticipantIndex;
extern vector <vector <CommanderProfile>> allCommanders;

//Constructors
Participants::Participants()
{
    capitalX = 0;
    capitalY = 0;
    participantIndex = -1;
    kingdomName = " ";
}
Participants::Participants(int pIndex)
{
    capitalX = 0;
    capitalY = 0;
    participantIndex = pIndex;
    kingdomName = " ";
}
//Accessors
int Participants::getCapitalCoordinate(char whichCoordinate)
{
    switch (whichCoordinate)
    {
    case 'X':
        return capitalX;
        break;
    case 'Y':
        return capitalY;
        break;
    }
    return -1;//if something goes wrong
}
int Participants::findProvinceIndexWithCoordinates(int provinceXCoordinate, int provinceYCoordinate)
{
    for (int x = 0; x < listOfProvincesX.size(); x++)
    {
        if (listOfProvincesX[x] == provinceXCoordinate && listOfProvincesY[x] == provinceYCoordinate)
        {
            return x;
        }
    }
    return -1;//If something wrong happens
}

int Participants::howManyProvinces()
{
    return (int)listOfProvincesX.size();
}
int Participants::howManyCommanders()
{
    return (int) allCommanders[currentParticipantIndex].size();
}
int Participants::findCommanderIndex(string commanderName)
{
    for (int x = 0; x < howManyCommanders(); x++) /*find index of chosen commander unit*/
    {
        if (commanderName == allCommanders[currentParticipantIndex][x].getUnitName())
        {
            return x;
        }
    }
    return -1;//if something goes wrong
}


//Mutators
void Participants::updateCapitalCoordinates(int xCoordinate, int yCoordinate)
{
    capitalX = xCoordinate;
    capitalY = yCoordinate;
}

void Participants::addProvince(int xCoordinate, int yCoordinate)
{
    listOfProvincesX.push_back(xCoordinate);
    listOfProvincesY.push_back(yCoordinate);
}

void Participants::addNewCommander()
{
    //Creates new participant
    CommanderProfile newCommander(1, getNewName(), 1);
    newCommander.changeCoordinates(getCapitalCoordinate('X'), getCapitalCoordinate('Y'));
    allCommanders[currentParticipantIndex].push_back(newCommander);
}

void Participants::setKingdomName(string newName)
{
    kingdomName = newName;
}

string Participants::getKingdomName()
{
    return kingdomName;
}