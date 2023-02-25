#ifndef LISTS_H
#define LISTS_H

#include <iostream>
#include <string>

#include "OtherFunctions.h"

class Lists
{
public:
	//Constructors
    Lists(int identifier);
    void listOfHelp ();
    char listOfActions();
/*
1 - selectEnemyAction
2 - playerUnitAction
3 - introduction
4 - playerAction
5 - armyDeployment
6 - TrainMAFunction
7 - playerBuildFunction
8 - viewPlayerMap
9 - selectPlayerProvince
10 - selectEnemyProvince
11 - scoutLogFunction
12 - upgradeBuildings
*/
    private:
        int identifier;
};

#endif