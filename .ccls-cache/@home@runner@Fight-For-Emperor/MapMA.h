#include <iostream>
#include "Units.h"

#include "otherFunctions.h"
#include "textFunctions.h"
#include "Units.h"
#include "BuildMA.h"
#include "ScoutMA.h"
#include "AttackMA.h"
#include "TrainMA.h"
#include "Lists.h"
#include "coordinateFunctions.h"

using namespace std;

class MapMA
{
public:
	//Constructors
	MapMA(Participants *newParticipant);

	void viewPlayerMap();
	void selectUnitOriginal(Provinces *selectedProvince);
	void selectPlayerProvince();
	void playerUnitAction();
	void selectEnemyAction();
	void selectEnemyProvince();

	void scoutLogFunction();
	void provinceReportLog(char whatReportChar);
  Participants *returnParticipant();

private:
	Participants *participant;
};