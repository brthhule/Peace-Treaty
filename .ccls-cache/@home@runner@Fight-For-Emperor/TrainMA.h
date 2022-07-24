#include <iostream>
#include <iostream>
#include <vector>

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
};

