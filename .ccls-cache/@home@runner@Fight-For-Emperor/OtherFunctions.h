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

extern std::vector<std::vector<Provinces>> provincesMap;
extern int provinceBuildingsProductionNumbers[6];
extern int continentSize;
extern int troopsCP[5];
extern int currentParticipantIndex;

class OtherFunctions
{
public:
	OtherFunctions();

	//Check input-- maybe use template for this?
	std::string getInput(std::string text, std::vector<std::string> AV, bool redo);

	//Map stuff
	int translateCoordinate(int coordinate, char indicator, char whichWay);
	int translateCoordinateInput(int coordinate, char indicator);
	int translateCoordinateOutput(int coordinate, char indicator);
	void showMap();
	void updateprovinceResources();
	void createMap();

	//Name Functionality
	std::string createRandomName();

	//Other stuff
	int findAmountOfEnemyProvinces();
	void clearScreen ();
	void pauseGame();

private:
};


#endif