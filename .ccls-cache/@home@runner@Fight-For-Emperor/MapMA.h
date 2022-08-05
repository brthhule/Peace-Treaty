#include <iostream>

class MapMA
{
public:
	//Constructors
	MapMA();

	void viewPlayerMap();
	void selectUnitOriginal();
	void selectPlayerProvince();
	void playerUnitAction();
	void selectEnemyAction();
	void selectEnemyProvince();

	void scoutLogFunction();
	void provinceReportLog(char whatReportChar);

private:
	int xCoordinate;
	int yCoordinate;
};