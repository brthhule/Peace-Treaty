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
#include "Mobility.h"

#include "Participants.h"
#include "Provinces.h"
#include "ConstValues.h"

extern std::vector<std::vector<Provinces>> provincesMap;
extern std::vector<Participants> participantsList;
extern ConstValues CV;

class MapMA
{
public:
	//Constructors
	MapMA(Participants *newParticipant);

	void viewPlayerMap();

	void selectUnitOriginal(Provinces *selectedProvince);
	void selectPlayerProvince();
	void playerUnitAction(Provinces *newP);
	void playerUnitActionP(Provinces *newP);
	void selectEnemyAction();
	void selectEnemyProvince(Provinces *newP);

	void scoutLogFunction(Provinces* enemyProvince);
	void provinceReportLog(char whatReportChar, Provinces* enemyProvince);


  Participants *getParticipant();

private:
	Participants *participant;
	int pIndex;
	Provinces *prov;
	OtherFunctions OF;
};

#endif