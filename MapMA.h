#include <iostream>
#include "Participants.h""

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