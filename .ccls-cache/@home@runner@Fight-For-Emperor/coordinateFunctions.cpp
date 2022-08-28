#include "otherFunctions.h"
#include "textFunctions.h"
#include "Provinces.h"
#include "CommanderProfile.h"
#include "AllUnits.h"
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>  
#include <ctime>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include "AttackMA.h"
#include "Participants.h"
#include "coordinateFunctions.h"
#include "otherFunctions.h"

using namespace std;
extern vector<vector <Provinces>> provincesMap;
extern vector < vector <CommanderProfile>> allCommanders;
extern vector <Provinces> provincesCanSelect;
extern int provinceBuildingsProductionNumbers[6];
extern int continentSize;
extern int troopsCP[5];
extern vector <Participants> participantsList;
extern int currentParticipantIndex;

//Just copied and pasted the stuff above from otherFunctions.h, take out why you don't need later


int translateCoordinate(int coordinate, char indicator, char whichWay)
{
    /*replacement = xCoordinate;
    xCoordinate = translateCoordinate(yCoordinate, 'y', 'I');
    yCoordinate = translateCoordinate (replacement, 'x', 'I');*/
    int translation = 0;
    switch (whichWay)
    {
    case 'I':
        switch (indicator)
        {
        case 'x':
            translation = coordinate - 1;
            break;

        case 'y':
            translation = coordinate - continentSize;
            translation = abs(translation);
            break;
        }
        break;
    case 'O':
        switch (indicator)
        {
        case 'x':
            translation = coordinate + 1;
            break;
        case 'y':
            translation = continentSize - coordinate;
            translation = abs(translation);
            break;
        }
        break;
    }
    return translation;
}

void getCoordinates(int identifier, int& xCoordinate, int& yCoordinate)/*Might have have to fix this (check if the coordinate stuff is right)*/
{
    vector<int> actualCoordinatesAVTwo = {-1};
    for (int x = 1; x <= continentSize; x++)
    {
        actualCoordinatesAVTwo.push_back(x);
    }

    string phrase;
    switch (identifier)
    {
    case 1:
        phrase = "of the province you want to select";
        break;
    case 2:
        phrase = "of the province you want to move to";
        break;
    case 3:
        phrase = "of the army you want to use to attack the target with";
    }

    std::cout << "Enter the x coordinate " << phrase << " (Enter '-1' to go back to previous menu) : ";
    xCoordinate = getInt("Replacement", actualCoordinatesAVTwo, 2);
    cout << "X: " << xCoordinate << endl;
    if (xCoordinate != -1)
    {
        std::cout << "Enter the y coordinate " << phrase << " (Enter '-1' to go back to previous menu) : ";
        yCoordinate = getInt("Replacement", actualCoordinatesAVTwo, 2);
        std::cout << endl;
        cout << "Y: " << yCoordinate << endl;
 
        if (yCoordinate != 1)
        {
            int replacement = xCoordinate;
            xCoordinate = translateCoordinate(yCoordinate, 'y', 'I');
            yCoordinate = translateCoordinate(replacement, 'x', 'I');

            cout << "X: " << xCoordinate << endl;
            cout << "Y: " << yCoordinate << endl;
        }
    }
}//Can make this an array

void getTrainBuildCoordinates(int& xCoordinate, int& yCoordinate)
{
    showMap();
    printListOfProvinces();

    return getCoordinates(1, xCoordinate, yCoordinate);
}

int getRandomCoordinate()
{
    return rand() % continentSize;
}
