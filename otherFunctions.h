#include <iostream>
#include <string.h>
#include <string>
#include <vector>

#include "AllUnits.h"

using namespace std;

int calculatePlayerValues(int decision);

char getChar(string textToDisplay, string acceptableValues, int caseInstance);
char checkChar(string inputAV, string input);
int getInt(string textToDisplay, vector <int> acceptableValues, int caseInstance);
int checkInt(vector<int>& acceptableValuesTwo, string input);

void showMap();
void updateprovinceResources();
void createMap();


void findTotalPlayerUnits(int totalPlayerUnits[5]);

string getNewName();
string createRandomName();
char findConsonant(int randomNumber);
char findVowel(int randomNumber);

int findAmountOfEnemyProvinces();

void clearScreen ();