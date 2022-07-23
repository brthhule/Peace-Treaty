#include <iostream>
#include <string.h>
#include <vector>

#include "AllUnits.h"

using namespace std;

void printListOfProvinces();

void synopsis();

void playerUnitActionHelp();
void armyDeploymentHelp(int maxAmountOfCommanders);
void playerActionHelp();
void playerMapHelp();

void upgradeBuildingsHelp(); //fix this
void viewAllStatsFunction();
char listOfActions(int identifier);
void casualtyReport(int deadTroops[5], int injuredTroops[5]);
void printCostsToTrainAnotherCommander(int trainArmyCommanderCosts[5], int currentPlayerCommanders
);
extern int playerTroopsLost[5];
extern const int initialResources[5];





