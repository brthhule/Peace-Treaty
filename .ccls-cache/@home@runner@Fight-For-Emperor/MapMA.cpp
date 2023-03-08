#include "MapMA.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;
#define part() getParticipantIndex()

extern std::vector<std::vector<Provinces>> provincesMap;
extern std::vector<Participants> participantsList;
extern std::string troopNames[5];
extern int troopsCP[5];

MapMA::MapMA(Participants *newParticipant) { participant = newParticipant;
pIndex = participant->getParticipantIndex();}

void MapMA::viewPlayerMap() {
  char whatToDo = ' ';
  OF.showMap();

  print("Welcome to the View Map action menu");
  Lists newList(8);
  whatToDo = newList.listOfActions();

  switch (whatToDo) {
  case 'P': {
    Provinces *province = participant->getYourCoords(1);
		
    if (province->deleteStatus() != true) {
      selectUnitOriginal(province);
    }
    viewPlayerMap();
    break;
  }
  case 'H': {
    Lists newLists(8);
    newLists.listOfHelp();
    viewPlayerMap();
    break;
  }
  default:
    println("Returning to the previous menu.");
    std::cout << std::endl;
    break;
  }
}

Participants *MapMA::returnParticipant() { return participant; }

void MapMA::selectUnitOriginal(Provinces *selectedProvince) {
	prov = selectedProvince;
  if (prov->part() ==
      pIndex) // If belongs to participant
  {
    selectPlayerProvince();
  } else if (prov->part() == -1) // If empty province
  {
    if (prov->commandersNum() >
        0) // If there are more than 0 commnaders
    {
      if (prov->returnCommander(0)->getParticipantIndex() == pIndex)
      {
        playerUnitAction(prov);
      } else {
        selectEnemyAction();
      }
    }
  } else // If enemy province
  {
    selectEnemyProvince(prov);
  }
}
void MapMA::selectPlayerProvince() {
  if (prov->isCapital()) {
    print("This is your capital province ");
  } else {
    print ("This is one of your provinces ");
    ;
  }
  std::cout << std::endl << std::endl;

  Lists newList(9);
  char selectPlayerCapitalAction = newList.listOfActions();

  switch (selectPlayerCapitalAction) {
  case 'B': {
    BuildMA newBuildMA(prov, participant);
    newBuildMA.playerBuildFunction();
    break;
  }
  case 'T': {
    TrainMA newTrainMA(prov);
    newTrainMA.TrainMAFunction();
    break;
  }
  case 'M':
    std::cout << "Returning to the map..." << std::endl;
    std::cout << std::endl;
    break;
  }
}


void MapMA::selectEnemyProvince(Provinces *newP) {
  Provinces *enemyProvince = newP;
	if (enemyProvince->isCapital()) {
    println("This is an enemy capital province ");
  } else {
    println("This is one of the enemy's provinces");
  }

  println("\n\nWelcome to the Enemy Provinces Action Selection menu ");
	
  Lists newLists(10);
  char selectUnitEnemyProvinceChar = newLists.listOfActions();

  switch (selectUnitEnemyProvinceChar) {
  case 'A': {
    AttackMA newAttackMA(enemyProvince, participant);
    newAttackMA.playerAttack();
		//selectEnemyProvince(enemyProvince());
    break;
  }
  case 'S': {
    ScoutMA newScout(participant, enemyProvince);
    newScout.selectTargetToScout();
		//selectEnemyProvince(enemyProvince());
    break;
  }
  case 'V': {
    if (enemyProvince->scoutLogTurnLevel[0] != -1) {
      if (OF.getInput("View scout log for this province? (Y/N) ", {"Y", "N"}, 1).at(0) ==
          'Y') /*Ask user if they want to view scout log, get char, go to
                  scoutLogFunction if 'Y'*/
      {
        scoutLogFunction();
				
      }
    }
		selectEnemyProvince(enemyProvince());
    break;
  }
  case 'M':
    std::cout << "Returning to the menu... " << std::endl;
    break;
  }
}

void MapMA::playerUnitAction(Provinces *newP) {
	Provinces *newProvince = newP;
  println("This is one of your armies ");
	char playerUnitActionChar = listOfActions(2);
	switch (playerUnitActionChar) {
	case 'P': {
		// find index of commander unit, fix this
		int commanderIndex = 0;
		for (int x = 0; x < participant->commandersNum(); x++) {
			if (participant->getProvince(x) == newProvince) {
				commanderIndex = x;
				x = participant->commandersNum();
			}
		}
		if (participant->getCommander(commanderIndex)->hasMovedQuestion() == false) {
			Mobility newMobility ()
			participant->getCommander(commanderIndex)->moveUnit(); /*fix this*/
		} else
			println("This unit has already moved this turn... returning to the View Map action menu \n");
		playerUnitActionChar = 'M';
		break;
	}
	case 'H':
		listOfHelp(2);
		break;
	case 'M':
		std::cout << "Returning to menu... " << std::endl;
		repeatPlayerUnitAction = 'N';
		break;
	}
	
	if (playerUnitActionChar != 'M')
	{
		playerUnitAction(newProvince);
	}
}




void MapMA::selectEnemyAction() /*finish this*/
{
  std::cout << "This is an enmy army. " << std::endl;
  char repeatSelectEnemyAction = 'Y';
  do {
    listOfActions(1);
  } while (repeatSelectEnemyAction == 'Y');
}

void MapMA::scoutLogFunction() {
  char repeatScoutLog = 'N';
  char whatReportChar;

  std::cout << "Turn of scout report: "
            << provincesMap[xCoordinate][yCoordinate].scoutLogTurnLevel[0]
            << "; Level of report: "
            << provincesMap[xCoordinate][yCoordinate].scoutLogTurnLevel[1]
            << std::endl
            << std::endl;
  do {
    whatReportChar = listOfActions(11);
    provinceReportLog(whatReportChar);

  } while (repeatScoutLog == 'Y');
}
void MapMA::provinceReportLog(char whatReportChar) {
  int totalGarrisonedCP = 0;
  switch (whatReportChar) {
  case 'G': {
    std::cout << "Garrisoned troops: " << std::endl;
    for (int x = 0; x < 5; x++) {
      std::cout << "-" << troopNames[x] << ": "
                << provincesMap[xCoordinate][yCoordinate].getTroopsPresent(x)
                << std::endl;
      totalGarrisonedCP +=
          (provincesMap[xCoordinate][yCoordinate].getTroopsPresent(x) *
           troopsCP[x]);
    }
    std::cout << "Total Garrison Combat Power: " << totalGarrisonedCP << std::endl
              << std::endl;
    break;
  }
  case 'R':
    provincesMap[xCoordinate][yCoordinate].printResources();
    break;
  case 'B':
    provincesMap[xCoordinate][yCoordinate].printBuildingStats();
    break;
  case 'M':
    break;
  }
}
