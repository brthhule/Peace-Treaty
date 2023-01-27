#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include "Provinces.h"
#include "textFunctions.h"
#include "otherFunctions.h"
#include "coordinateFunctions.h"


using namespace std;
extern vector <vector <Provinces>> provincesMap;
extern vector <Participants> participantsList;
extern string provinceResourcesNames[5];
extern string buildingNames[6];
extern string troopNames[5];
extern int initialResources[5];
extern int continentSize;
extern int currentParticipantIndex;

void synopsis()
{
    cout << "- Welcome to Fight For Emperor" << endl;
    cout << "- In a large continent, filled with various kingdoms, you are a monarch seeking to unit the land; you will defeat the other kingdoms and become emperorer." << endl;
    cout << "- Develop buildings, train troops, and use logistics and battle strategies to conquer enemy provinces." << endl;
    cout << "- Although players cannot save their complete data, a portion of the land that they gained in the previous game (as well as the amount of resources available) will be available through a code " << endl << endl;
}

void viewAllStatsFunction()
{
    string literallyAnyRandomCharacter;
    std::cout << "\033[;34m";//NW
    for (int x = 0; x < 5; x++)
    {
        std::cout << troopNames[x] << " lost: " << participantsList[currentParticipantIndex].playerTroopsLost[x] << endl;
    }
    std::cout << "Total troops lost: " << calculatePlayerValues(2) << endl << endl;
    std::cout << "\033[;0m";//NW

    cout << "Enter any character to go back to the Main menu: ";
    cout << "\033[31m";
    getline(cin, literallyAnyRandomCharacter);
    cout << "\033[0m";
}

void casualtyReport(int deadTroops[5], int injuredTroops[5])
{
    std::cout << endl;
    std::cout << "Troops casualties: " << endl;
    for (int x = 0; x < 5; x++) /*print out deaths*/
    {
        std::cout << troopNames[x] << " dead: " << deadTroops[x] << endl;
    }
    std::cout << endl;
    for (int x = 0; x < 5; x++) /*print out deaths*/
    {
        std::cout << troopNames[x] << " injured: " << injuredTroops[x] << endl;
    }
    std::cout << endl;
}

void printListOfProvinces()
{
    std::cout << "Here is a list of your provinces: " << endl;
    int x;
    int y;
    for (int a = 0; a < continentSize; a++)
    {
        for (int b = 0; b < continentSize; b++)
        {
            if (provincesMap[a][b].getBelongsToParticipant() == currentParticipantIndex)
            {
                x = translateCoordinate(b, 'x', 'O');
                y = translateCoordinate(a, 'y', 'O');
                std::cout << "(" << x << ", " << y << ") " << endl;
            }
        }
    }
    std::cout << endl;
}
