class BuildMA
{
public:
	//Constructors
	BuildMA();
	BuildMA(int xCoordinate, int yCoordinate);

	//Accessors/Functions?
	void findProvinceCoordinates();
	void playerBuildFunction();
	void upgradeBuildings();
private:
	int provinceXCoordinate;
	int provinceYCoordinate;
	double requiredResourcesBuildings[6][5] = { {1, 0.5, 0.25, 0.125, 0.0625}, {2, 1, 0.5, 0.25, 0.125}, {3, 2, 1, 0.5, 0.25}, {4, 3, 2, 1, 0.5}, {5, 4, 3, 2, 1}, {1, 1, 1, 1, 0.2} }; /*double requiredResourcesFarm [5] = {1, 0.5, 0.25, 0.125, 0.0625};
	double requiredResourcesLumberMill [5] = {2, 1, 0.5, 0.25, 0.125};
	double requiredResourcesQuarry [5] = {3, 2, 1, 0.5, 0.25};
	double requiredResourcesMine [5] = {4, 3, 2, 1, 0.5};
	double requiredResourcesChurch [5] = {5, 4, 3, 2, 1};
	double requiredResourcesBarracks [5] = {1, 1, 1, 1, 0.2};*/
};

