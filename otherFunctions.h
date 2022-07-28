#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <string>

#include "AllUnits.h"

using namespace std;

char getChar(string testToDisplay, string acceptableValues, int caseInstance);
char checkChar(string inputAV, string input);

int translateCoordinate(int coordinate, char indicator, char whichWay);
int calculatePlayerValues(int decision);
int findCommanderIndex(char commanderChar);
int checkInt(vector<int>& acceptableValuesTwo, string input);

void showMap();
void updateprovinceResources();
void moveUnit(int xCoordinate, int yCoordinate, int participantIndex, int commanderIndex);

string convertPCIToString(vector <char> playerCommanderIdentifiers);

vector<int> getCoordinates(int identifier);
vector<int> getTrainBuildCoordinates();

void findTotalPlayerUnits(int totalPlayerUnits[5]);
