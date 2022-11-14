#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

#include "AllUnits.h"

using namespace std;

int translateCoordinate(int coordinate, char indicator, char whichWay);

void getCoordinates(int identifier, int& xCoordinate, int& yCoordinate);
void getTrainBuildCoordinates(int& xCoordinate, int& yCoordinate);

int getRandomCoordinate();
