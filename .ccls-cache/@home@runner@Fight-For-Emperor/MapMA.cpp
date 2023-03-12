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
  participant->showMap();

  print("Welcome to the View Map action menu");
  Lists newList(8);
  whatToDo = newList.listOfActions();

  switch (whatToDo) {
  case 'P': {
    Provinces *province = participant->getYourProvince(1);
		
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
		//selectEnemyProvince(enemyProvince);
    break;
  }
  case 'S': {
    ScoutMA newScout(participant, enemyProvince);
    newScout.selectTargetToScout();
		//selectEnemyProvince(enemyProvince);
    break;
  }
  case 'V': {
    if (enemyProvince->getScoutReportTurn() != -1)
      if (OF.getInput("View scout log for this province? (Y/N) ", {"Y", "N"}, 1).at(0) ==
          'Y')
        scoutLogFunction(enemyProvince);
		
		selectEnemyProvince(enemyProvince);
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
	
	Lists newLists (2);
	switch (newLists.listOfActions()) {
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
			Mobility newMobility (participant->getCommander(commanderIndex), participant);
			newMobility.moveUnitOne(); /*fix this*/
			playerUnitAction(newProvince);
		} else
		{
			println("This unit has already moved this turn... returning to the View Map action menu \n");
		break;
		}
	}
	case 'H':
	{
		Lists newLists(2);
		newLists.listOfHelp();
		break;
		playerUnitAction(newProvince);
	}
	case 'M':
		std::cout << "Returning to menu... \n" ;
		break;
	}
}




void MapMA::selectEnemyAction() /*Add implementation*/
{
  std::cout << "This is an enmy army. \n";
  Lists newLists(1);
	char action = newLists.listOfActions();

	switch (action)
	{
		case 'A':
			break;
		case 'S':
			break;
		case 'H':
			break;
		case 'M':
			break;
	}
}

void MapMA::scoutLogFunction(Provinces* enemyProvince) {
  char repeatScoutLog = 'N';
  char whatReportChar;

  std::cout << "Turn of scout report: "
            << enemyProvince->getScoutReportTurn()
            << "; Level of report: "
            << enemyProvince -> getScoutLogTurnLevel()
            << std::endl
            << std::endl;
  do {
		Lists newLists(11);
    whatReportChar = newLists.listOfActions();
    provinceReportLog(whatReportChar, enemyProvince);

  } while (repeatScoutLog == 'Y');
}
void MapMA::provinceReportLog(char whatReportChar, Provinces* enemyProvince) {
  int totalGarrisonedCP = 0;
  switch (whatReportChar) {
  case 'G': {
    std::cout << "Garrisoned troops: " << std::endl;
    for (int x = 0; x < 5; x++) {
      std::cout << "-" << troopNames[x] << ": "
                << enemyProvince->getTroopsPresent(x)
                << std::endl;
      totalGarrisonedCP +=
          (enemyProvince->getTroopsPresent(x) *
           troopsCP[x]);
    }
    std::cout << "Total Garrison Combat Power: " << totalGarrisonedCP << std::endl
              << std::endl;
    break;
  }
  case 'R':
    enemyProvince->printResources();
    break;
  case 'B':
    enemyProvince->printBuildingStats();
    break;
  case 'M':
    break;
  }
}
