#include <iostream>
#include <iostream>
#include <vector>

#include "AllUnits.h"
#include "Provinces.h"

class TrainMA
{
public:
	//constructor
	TrainMA();
	TrainMA(int xCoordinate, int yCoordinate);
	//other functions
	void TrainMAFunction();
	void findProvinceCoordinates();
private:
	int provinceXCoordinate;
	int provinceYCoordinate;
	string provinceResourcesNames [5] = {"Food", "Wood", "Ore", "Gold", "Mana"};
};

