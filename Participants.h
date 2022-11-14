#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#include <iostream>
#include <vector>

#include "CommanderProfile.h"
#include "Provinces.h"

using namespace std;

class Participants
{
public:
    //constructors
    Participants();
    Participants(int pIndex);

    //Capital stuff
        //Accessors
    int getCapitalCoordinate(char whichCoordinate);
    //Mutators
    void updateCapitalCoordinates(int xCoordinate, int yCoordinate);

    //Commander stuff
        //Accessors
    int howManyCommanders();
    int findCommanderIndex(string commanderName);
    void addNewCommander();
    //Mutators

//Province stuff
    //Accessors
    int howManyProvinces();
    int findProvinceIndexWithCoordinates(int provinceXCoordinate, int provinceYCoordinate);
    //Mutators
    void addProvince(int xCoordinate, int yCoordinate);

    //Public variables

    int capitalX;
    int capitalY;
    //std::vector <CommanderProfile> listOfCommanders;
    vector <int> listOfProvincesX;//Includes the capital province in this
    vector <int> listOfProvincesY;

    int playerTroopsLost[5] = { 0,0,0,0,0 };
    int totalPlayerUnits[5] = { 0,0,0,0,0 }; /*0) Militia, 1) Guards, 2) Cavalry, 3) Knights, 4) Paladins*/

    void setKingdomName(string newName);
    string getKingdomName();



private:
    int participantIndex;
    string kingdomName;

    //Figure out sizes later
    int AIMainAction[5];
    int AIBuildMA[2];
    int AITroopMA[3];

};
#endif