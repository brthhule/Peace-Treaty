#ifndef MAPMA_H
#define MAPMA_H

#include <iostream>

#include "OtherFunctions.h"
#include "textFunctions.h"
#include "BuildMA.h"
#include "ScoutMA.h"
#include "AttackMA.h"
#include "TrainMA.h"
#include "Lists.h"

#include "Participants.h"
#include "Provinces.h"

class MapMA
{
public:
	//Constructors
	MapMA(Participants *newParticipant);

	void viewPlayerMap();

	void selectUnitOriginal(Provinces *selectedProvince);
	void selectPlayerProvince();
	void playerUnitAction(Provinces *newP);
	void selectEnemyAction();
	void selectEnemyProvince(Provinces *newP);

	void scoutLogFunction();
	void provinceReportLog(char whatReportChar);


  Participants *returnParticipant();

private:
	Participants *participant;
	int pIndex;
	Provinces *prov;
	OtherFunctions OF;
};

#endif