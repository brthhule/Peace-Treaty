#ifndef ARMYDEPLOYMENTMA_H
#define ARMYDEPLOYMENTMA_H

#include <iostream>
#include <string.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <array>

extern std::string provinceResourcesNames[5];
extern std::string buildingNames[6];
extern std::string troopNames[5];
extern int initialResources[5];
extern int continentSize;

void synopsis();
void viewAllStatsFunction();
void casualtyReport(std::array<int,5> troopsLost, std::array<int,5> injuredTroops);

#endif






