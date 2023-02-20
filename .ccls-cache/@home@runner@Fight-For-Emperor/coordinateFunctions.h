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

#include "Units.h"
#include "textFunctions.h"
#include "AttackMA.h"
#include "otherFunctions.h"

using namespace std;

int translateCoordinate(int coordinate, char indicator, char whichWay);

Provinces* getCoordinates(int identifier);
int getRandomCoordinate();
