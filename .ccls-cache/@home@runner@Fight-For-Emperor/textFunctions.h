#ifndef ARMYDEPLOYMENTMA_H
#define ARMYDEPLOYMENTMA_H

#include <iostream>
#include <string.h>
#include <vector>
#include <string>
#include <stdlib.h>

extern std::string provinceResourcesNames[5];
extern std::string buildingNames[6];
extern std::string troopNames[5];
extern int initialResources[5];
extern int continentSize;

void synopsis();
void viewAllStatsFunction();
void casualtyReport(int troopsLost[5], int injuredTroops[5]);

#endif






