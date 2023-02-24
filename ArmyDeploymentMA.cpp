#include "ArmyDeploymentMA.h"
#include "CommanderProfile.h"
#include "Provinces.h"
#include "Participants.h"

extern int maxAmountOfCommanders;
extern vector<vector<Provinces>> provincesMap;
extern vector<Participants> participantsList;

extern string provinceResourcesNames[5];
extern int initialResources[5];
extern int currentParticipantIndex;

ArmyDeploymentMA::ArmyDeploymentMA() {
  capitalX = -1;
  capitalY = -1;
}

ArmyDeploymentMA::ArmyDeploymentMA(Participants *newP) {
  participant = newP;
  capitalProvince = participant->getCapital();
  capitalX = capitalProvince->getCoordinate('X');
  capitalY = capitalProvince->getCoordinate('Y');
  commandersNum = participant->commandersNum();
}

void ArmyDeploymentMA::armyDeploymentMF() {
  char armyDeploymentActionChar;

  std::cout << "Welcome to the Army Deployment action menu" << endl;
  Lists newList(5);
  armyDeploymentActionChar = newList.listOfActions();
  std::cout << endl;

  switch (armyDeploymentActionChar) {
  case 'T':
    trainCommanders();
    break;
  case 'U':
    upgradeCommandersOne();
    break;
  case 'V':
    viewArmyOverview();
    break;
  case 'D': {
    deployCommanderMF();
    break;
  }
  case 'H': {
    Lists newList(5);
    newList.listOfHelp();
    break;
  }
  case 'M':
    return;
    break;
  }
  armyDeploymentMF();
}

void ArmyDeploymentMA::upgradeCommandersOne() /*fix this-- finish making it*/
{
  int commandersNum = participant->commandersNum();
  std::cout << "You have " << commandersNum << " army commanders." << endl;

  if (commandersNum > 0) {
    upgradeCommandersTwo();
  } else {
    std::cout << "No commanders available, can not upgrade" << endl;
  }

  string thingy = " ";
  std::cout << "Enter anything to return to Army Deployment menu: \n\n";
  getline(cin, thingy);
}
void ArmyDeploymentMA::upgradeCommandersTwo() {
  vector<int> indexOfCommanders;
  for (int x = 1; x <= commandersNum; x++) {
    indexOfCommanders.push_back(x);
  }

  std::cout << "Here is list of your commanders: " << endl;
  for (int x = 0; x < participant->commandersNum(); x++) {
    CommanderProfile *tempCommander = participant->getCommander(x);
    std::cout << x + 1 << ") Commander " << tempCommander->getUnitName()
              << "; Level: " << tempCommander->getCommanderLevel() << endl;
    delete tempCommander;
  }

  std::cout << endl;
  int indexOfCommander =
      getInt("Enter the number of the army commander you want to upgrade: ",
             indexOfCommanders, 1) - 1;

  CommanderProfile *newCommander =
      participant->getCommander(indexOfCommander);
	newCommander -> printCosts(newCommander->getUpgradeCosts);

  std::cout << endl;
  char failCommanderUpgrade = 'S';
	char proceedWithUpgradeQuestion = getChar("Proceed with upgrade? ", "YN", 1);
  if (proceedWithUpgradeQuestion == 'Y') {

    vector<int> commanderCosts = newCommander->getUpgradeCosts();
    for (int x = 0; x < 5; x++) {
      capitalProvince->addResources(x, commanderCosts[x] * -1);
      if (capitalProvince->getR(x) < 0) {
        failCommanderUpgrade = 'F';
      }
    }
    if (failCommanderUpgrade == 'S') {
      newCommander->addCommanderLevel();
      std::cout << "Upgrade successful; Commander "
                << newCommander->getCommanderName() << "is now level "
                << newCommander->getCommanderLevel() << endl;
    } else {
      for (int x = 0; x < 5; x++) {
        capitalProvince->addResources(x, commanderCosts[x]);
      }
      std::cout << "Upgrade failed. " << endl;
    }
  }
}

CommanderProfile *ArmyDeploymentMA::selectCommander(char &successfulSelection) {
  successfulSelection = 'N';
  vector<int> listOfOptions = {};
  for (int x = 0; x < commandersNum; x++) {
    listOfOptions.push_back(x + 1);
  }
  std::cout << "You have " << commandersNum << " commanders. " << endl;

  if (commandersNum > 0) {
    std::cout << "Here is a list of your commanders: " << endl;
    for (int x = 0; x < commandersNum; x++) {
      std::cout << x + 1 << ") Commander "
                << participant->getCommander(x)->getUnitName() << endl;
    }
    std::cout << endl;

    int index =
        getInt("Please enter the number of the commander you wish to select: ",
               listOfOptions, 1) -
        1;
    std::cout << "Confirm selection of commander "
         << participant->getCommander(index)->getUnitName() << "? (Y/N): ";
    char confirmSelection = getChar("0", "YN", 2);
    if (confirmSelection == 'Y') {
			CommanderProfile *commanderPointer = participant->getCommander(index);
			successfulSelection = 'Y';
			return commanderPointer;
    }
  }
	cout << "Selection cancelled... " << endl;
	CommanderProfile newCommanderThingy;
	CommanderProfile* trashCommander = &newCommanderThingy;
	successfulSelection = 'N';
	return trashCommander;
}

void ArmyDeploymentMA::viewArmyOverview() {
	char decision = 'N';
	CommanderProfile *newCommander = selectCommander(decision);
  switch (decision) {
  case 'Y': {
    std::cout << "Commander " << newCommander->getCommanderName() << " selected... "
         << endl;
    std::cout << "The coordinates of this Commander: ("
         << translateCoordinate(newCommander->returnCoordinate('X'), 'x', 'O')
         << ", "
         << translateCoordinate(newCommander->returnCoordinate('Y'), 'y', 'O')
         << ") " << endl;
    std::cout << endl;

    newCommander->printCommanderStats();
    break;
  }
  case 'N':
    std::cout << "Returning to Army Deployment Menu... " << endl;
    break;
  }
	delete newCommander;
}



void ArmyDeploymentMA::trainCommanders() {
  string yesOrNoString;
  std::cout << "You have " << commandersNum
            << " army commanders in total. " << endl;
  std::cout << "Do you want to train a commander? (Y/N) ";

  vector <int> trainCosts = participant->getTrainCosts();

  if (getChar("Replacement", "YN", 2) == 'Y') {
    if (commandersNum <
        maxAmountOfCommanders) /*if amount of commanders is less than max (not
                                  at max capacity)*/
    {
      printCosts(trainCosts, "training");

      if (getChar("Proceed with training? (Y/N) ", "YN", 1) == 'Y') {
				proceedWithTraining(trainCosts);
			}
    } else 
		{
      std::cout << "At maximum army commander amount. Training failed, returning to menu \n";
    }
  } else {
    std::cout << "Returning to previous menu... " << endl;
  }
}

void ArmyDeploymentMA::proceedWithTraining (vector <int> trainCosts)
{
	char failCommanderTraining = 'S';
	for (int x = 0; x < 5; x++) 
	{
		capitalProvince->addResources(x, trainCosts[x] * -1);
		if (capitalProvince->getR(x) < 0) {
			failCommanderTraining = 'F';
		}
	}

	if (failCommanderTraining == 'S') 
	{
		std::cout << "Commander training successful " << endl;
		std::cout << "Current commanders: "
							<< commandersNum + 1 << endl;

		CommanderProfile newCommander(1, participant->getNewName(),
																	participant->commandersNum());
		newCommander.changeCoordinates(
				capitalProvince-> returnCorodinate('X'),
				capitalProvince-> returnCorodinate('Y'));
	} else 
	{
		std::cout << "Commander training failed (Not enough resources)... \n\n"
		for (int x = 0; x < 5; x++) {
			newProvince->addResources(x, trainArmyCommanderCosts[x]);
		}
	}
}


void ArmyDeploymentMA::deployCommanderMF() {
  Participants *newParticipant = &participantsList[currentParticipantIndex];
  int commandersInCapital =
      (int)provincesMap[capitalX][capitalY].commandersPresentIndex.size();

  if (commandersInCapital == 0) {
    std::cout << "No commanders in capital, cannot deploy..." << endl;
  } else {
    deployCommanderDisplayInformation(commandersInCapital);

    char returnToMenu = 'N';
    vector<int> listOfCommandersIndex;
    vector<int> amountOfCommanders = {-1};
    for (int x = 0; x < provincesMap[newParticipant->listOfProvincesX[0]]
                                    [newParticipant->listOfProvincesY[0]]
                                        .commandersPresentIndex.size();
         x++) {
      int xCoordinate = newParticipant->listOfProvincesX[x];
      int yCoordinate = newParticipant->listOfProvincesY[x];
      listOfCommandersIndex.push_back(
          provincesMap[xCoordinate][yCoordinate].returnCommanderIndex(x));
      amountOfCommanders.push_back(x + 1);
    }
    do {
      int commanderLetterIdentifier =
          getInt("Enter the number identifier of the commander you want to "
                 "deploy (enter '1' to go back to previous menu): ",
                 amountOfCommanders, 1);
      std::cout << endl;

      if (commanderLetterIdentifier != 1) {
        int indexToSelect = commanderLetterIdentifier - 1;
        CommanderProfile *newCommander3 =
            &allCommanders[currentParticipantIndex][indexToSelect];

        newCommander3->printCommanderStats();

        string confirmDeployCommanderString;
        int commanderIndex =
            provincesMap[capitalX][capitalY].returnCommanderIndex(
                indexToSelect);
        std::cout << "Deploy commander "
                  << allCommanders[currentParticipantIndex][commanderIndex]
                         .getUnitName()
                  << "? (Y/N) ";
        char confirmDeployCommanderChar = getChar("Replacement", "YN", 2);

        int participantIndex = 0; /*Fix this when developing AI*/
        int xThingyTwo = newCommander3->getCoordinate('X');
        int yThingyTwo = newCommander3->getCoordinate('Y');
        if (confirmDeployCommanderChar == 'Y') {
          if (newCommander3->hasCommanderMoved() == 'N') {
            newCommander3->moveUnit();
            returnToMenu = 'Y';
          } else {
            std::cout
                << "This unit has already moved... please pick another unit "
                << endl;
          }
        }
      } else {
        returnToMenu = 'Y';
      }
    } while (returnToMenu == 'N');
    std::cout << endl;
  }
  std::cout << "Returning to the Army Deployment action menu" << endl;
  std::cout << endl;
}


void ArmyDeploymentMA::deployCommanderDisplayInformation(
    int commandersInCapital) {
  int findCommanderLevel = 0;
  string commanderName = " ";

  Participants *newParticipant = &participantsList[currentParticipantIndex];

  std::cout << "The following commanders are in the capital: "
            << provincesMap[capitalX][capitalY].commandersPresentIndex.size()
            << endl;

  for (int a = 0; a < commandersInCapital; a++) {
    int commanderIndex = provincesMap[newParticipant->getCapitalCoordinate('X')]
                                     [newParticipant->getCapitalCoordinate('Y')]
                                         .commandersPresentIndex[a];
    commanderName =
        allCommanders[currentParticipantIndex][commanderIndex].getUnitName();
    // int commanderIndex =
    // participantsList[currentParticipantIndex].findCommanderIndex(commanderName);
    std::cout
        << "Commander "
        << allCommanders[currentParticipantIndex][commanderIndex].getUnitName()
        << "; Level: "
        << allCommanders[currentParticipantIndex][commanderIndex]
               .getCommanderLevel()
        << endl;
  }
}


void ArmyDeploymentMA::printCosts(vector<int>costs, string type)
{
	cout << "The following are the " << type << " costs": << endl;
	for (int x = 0; x < 5; x++)
		{
			cout << provinceResourcesNames[x] << ": " << costs[x];
		}

	cout << "The following are the resources currently in your capital: \n";
	capitalProvince->printResources();
}