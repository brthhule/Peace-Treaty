#include <iostream>
#include <iostream>
#include <vector>

#include "Provinces.h"

class TrainMA
{
public:
	//constructor
	TrainMA(Provinces *newP);
	//other functions
	void TrainMAFunction();
	vector <Provinces*> getTrainProvince();
private:
	Provinces *province;
};

