#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <string>

#include "AllUnits.h"

using namespace std;
char getChar(string testToDisplay, string acceptableValues, int caseInstance);
int translateCoordinate(int coordinate, char indicator, char whichWay);
int calculatePlayerValues(int decision);
char checkChar(string inputAV, string input);
string convertPCIToString(vector <char> playerCommanderIdentifiers);
int findCommanderIndex(char commanderChar, string listOfCommanders);
vector<int> getCoordinates(int identifier);
int checkInt(vector<int>& acceptableValuesTwo, string input);
vector<int> getTrainBuildCoordinates();
void showMap();
void updateCommanderIdentifiers(int participantIndex);

void moveUnit(int xCoordinate, int yCoordinate, int participantIndex, int commanderIndex);

extern int provinceBuildingsProduction[15][15][6];
extern const int provinceBuildingsProductionNumbers[6];
//extern int provinceResources[15][15][5];

extern int totalPlayerResources[5];
extern int continentSize;

extern int totalTroops[5];
extern const int troopsCP[5];
extern int playerTroopsLost[5];

extern int continentSize;
//extern char mapCharacters[15][15];
extern int scoutLogTurnLevel[15][15][2];