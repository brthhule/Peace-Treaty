#include "AllUnits.h"

class CommanderProfile: public AllUnits
{
public:
	//Constructors
	CommanderProfile();
	CommanderProfile(int commanderLevel, string name);
	//Destructor
	~CommanderProfile();


	//Accessor functions

	//Stats stuff
	int getCommanderStat(int index);
	void printCommanderStats();
	void changeCommanderStat(int index, int amount);
	void setLocation (Provinces *newProvince);

	//Scout report stuff 
	void updateCommanderScoutReport(int index, int value);
	void completeCommanderScoutReport(int accuracy);
	int printCommanderScoutReport(int idex);

	//Other commander stuff
	int getCommanderLevel();
	void addCommanderLevel();
	vector <int> getUpgradeCosts();
	string getCommanderName();
	vector <int> getTrainCosts();

	//Moving
	void moveUnit();
	vector <Provinces*> moveUnitOne ();
	char hasCommanderMoved();
	void resetCommanderMoved();

	int returnCoordinate(char which);

private:
	int* commanderArmyStats[20];/*
[0] = food the army possesses    Resources
[1]  = wood
[2] = ore
[3] = gold
[4] = mana
[5] = militia present            Troops Present
[6] = guards present
[7] = cavalry present
[8] = knights present
[9]  = paladins present
[10] = militia injured            Troops Injured
[11] = guards injured
[12] = cavalry injured
[13] = knights injured
[14] = paladins injured
[15] = total troops               Miscellaneous stats
[16] = totalCP
[17] = leaderLevel
[18] = maxTroops
[19] = food consumption
*/
	int commanderLevel;
	int commanderScoutReport[22];/*
[0] = food the army possesses    Resources
[1]  = wood
[2] = ore
[3] = gold
[4] = mana
[5] = militia present            Troops Present
[6] = guards present
[7] = cavalry present
[8] = knights present
[9]  = paladins present
[10] = militia injured            Troops Injured
[11] = guards injured
[12] = cavalry injured
[13] = knights injured
[14] = paladins injured
[15] = total troops               Miscellaneous stats
[16] = totalCP
[17] = leaderLevel
[18] = maxTroops
[19] = food consumption
[20] = turn number of scout report
[21] = accuracy of scout report*/
	int maxTroops;//check
	int totalMaxResources;
	char hasMoved;

	string MANDescriptions[5] = { "Resources in", "Troops present in", "Troops injured in", "Other stats of" };//check
	string namesOfMAN[20];//check
	Provinces *provinceLocation;

	vector <int> costToUpgrade = {5, 4, 3, 2, 1};

};
