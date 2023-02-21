#ifndef OTHERFUNCTIONS
#define OTHERFUNCTIONS

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
#include "AttackMA.h"

using namespace std;

int calculatePlayerValues(int decision);

char getChar(string textToDisplay, string acceptableValues, int caseInstance);
char checkChar(string inputAV, string input);
int getInt(string textToDisplay, vector <int> acceptableValues, int caseInstance);
int checkInt(vector<int>& acceptableValuesTwo, string input);
void pauseGame();

void showMap();
void updateprovinceResources();
void createMap();

string createRandomName();
char findConsonant(int randomNumber);
char findVowel(int randomNumber);

int findAmountOfEnemyProvinces();

void clearScreen ();

#endif