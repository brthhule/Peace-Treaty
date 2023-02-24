#ifndef OTHERFUNCTIONS_H
#define OTHERFUNCTIONS_H

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

#include "textFunctions.h"
#include "Provinces.h"
#include "main.cpp"

extern std::vector<std::vector<Provinces>> provincesMap;
extern int provinceBuildingsProductionNumbers[6];
extern int continentSize;
extern int troopsCP[5];
extern int currentParticipantIndex;

char getChar(std::string textToDisplay, std::string acceptableValues, int caseInstance);
char checkChar(std::string inputAV, std::string input);
int getInt(std::string textToDisplay, std::vector <int> acceptableValues, int caseInstance);
int checkInt(std::vector<int>& acceptableValuesTwo, std::string input);
void pauseGame();

void showMap();
void updateprovinceResources();
void createMap();

std::string createRandomName();
char findConsonant(int randomNumber);
char findVowel(int randomNumber);

int findAmountOfEnemyProvinces();

void clearScreen ();

#endif