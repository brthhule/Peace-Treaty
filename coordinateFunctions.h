#ifndef COORDINATEFUNCTIONS_H
#define COORDINATEFUNCTIONS_H

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

using namespace std;

int translateCoordinate(int coordinate, char indicator, char whichWay);

vector <int> getCoords(int identifier);
int getRandomCoordinate();

#endif
