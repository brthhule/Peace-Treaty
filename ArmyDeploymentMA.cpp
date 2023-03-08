#include "ArmyDeploymentMA.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

extern int maxAmountOfCommanders;
extern std::vector<std::vector<Provinces>> provincesMap;
extern std::vector<Participants> participantsList;

extern std::string provinceResourcesNames[5];
extern int initialResources[5];
extern int currentParticipantIndex;

ArmyDeploymentMA::ArmyDeploymentMA() {}

ArmyDeploymentMA::ArmyDeploymentMA(Participants *newP) {
  participant = newP;
  capitalProvince = participant->getCapital();
  commandersNum = participant->commandersNum();
}

void ArmyDeploymentMA::armyDeploymentMF() {
  char armyDeploymentActionChar;

  println("Welcome to the Army Deployment action menu");
  Lists newList(5);
  armyDeploymentActionChar = newList.listOfActions();
  std::cout << std::endl;

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
  std::cout << "You have " << commandersNum << " army commanders." << std::endl;

  if (commandersNum > 0) {
    upgradeCommandersTwo();
  } else {
    std::cout << "No commanders available, can not upgrade" << std::endl;
  }

  std::string thingy = " ";
  std::cout << "Enter anything to return to Army Deployment menu: \n\n";
  getline(std::cin, thingy);
}
void ArmyDeploymentMA::upgradeCommandersTwo() {
  std::vector<int> indexOfCommanders;
  for (int x = 1; x <= commandersNum; x++) {
    indexOfCommanders.push_back(x);
  }

  std::cout << "Here is list of your commanders: " << std::endl;
  for (int x = 0; x < participant->commandersNum(); x++) {
    CommanderProfile *tempCommander = participant->getCommander(x);
    std::cout << x + 1 << ") Commander " << tempCommander->getName()
              << "; Level: " << tempCommander->getLevel() << std::endl;
    delete tempCommander;
  }

	std::vector<std::string> selectableCommanders;
	for (int h = 0; h < indexOfCommanders.size(); h++)
	{
		selectableCommanders.push_back("" + std::to_string(indexOfCommanders[h]));
	}
	
  std::cout << std::endl;
  int indexOfCommander =
      stoi(OF.getInput("Enter the number of the army commander you want to upgrade: ",
                selectableCommanders, 1)) -
      1;

  CommanderProfile *newCommander = participant->getCommander(indexOfCommander);
  newCommander->printCosts(newCommander->getUpgradeCosts());

  std::cout << std::endl;
  char failCommanderUpgrade = 'S';
  char proceedWithUpgradeQuestion =
      OF.getInput("Proceed with upgrade? ", {"Y", "N"}, 1).at(0);
  if (proceedWithUpgradeQuestion == 'Y') {

    std::vector<int> commanderCosts = newCommander->getUpgradeCosts();
    for (int x = 0; x < 5; x++) {
      capitalProvince->subtractResource(x, commanderCosts[x] * -1);
      if (capitalProvince->getResource(x) < 0) {
        failCommanderUpgrade = 'F';
      }
    }
    if (failCommanderUpgrade == 'S') {
      newCommander->addLevel();
      std::cout << "Upgrade successful; Commander " << newCommander->getName()
                << "is now level " << newCommander->getLevel() << std::endl;
    } else {
      for (int x = 0; x < 5; x++) {
        capitalProvince->addResource(x, commanderCosts[x]);
      }
      std::cout << "Upgrade failed. " << std::endl;
    }
  }
}

CommanderProfile *ArmyDeploymentMA::selectCommander() {
  displayCommanders();
  std::string commanderName = " ";
  println("Enter the name of the commander you wish to select: ");
  getline(std::cin, commanderName);
	CommanderProfile* newCommander;

	if (participant->hasCommander(commanderName) == false)
	{
		selectCommander();
	}
  else 
		newCommander = participant->getCommanderName(commanderName);
		
    std::cout << "Confirm selection of commander "
              << newCommander->getName() << "? (Y/N): ";
    char confirmSelection = OF.getInput("0", {"Y", "N"}, 2).at(0);
    if (confirmSelection == 'Y') {
      return newCommander;
    }
		else
		{
			newCommander-> setDelete();
			return newCommander;
		}
  }
}

void ArmyDeploymentMA::viewArmyOverview() {
  char decision = 'N';
  CommanderProfile *newCommander = selectCommander();
  switch (decision) {
  case 'Y': {
    std::cout << "Commander " << newCommander->getName() << " selected... "
              << std::endl;
    std::cout << "The coordinates of this Commander: ("
              << participant->translateCoordinate(
                     newCommander->returnCoordinate('X'), 'x', 'O')
              << ", "
              << participant->translateCoordinate(
                     newCommander->returnCoordinate('Y'), 'y', 'O')
              << ") " << std::endl;
    std::cout << std::endl;

    newCommander->printCommanderStats();
    break;
  }
  case 'N':
    std::cout << "Returning to Army Deployment Menu... " << std::endl;
    break;
  }
  delete newCommander;
}

void ArmyDeploymentMA::trainCommanders() {
  std::string yesOrNoString;
  std::cout << "You have " << commandersNum << " army commanders in total. "
            << std::endl;
  std::cout << "Do you want to train a commander? (Y/N) ";

  std::vector<int> trainCosts = participant->getTrainCosts();

  if (OF.getInput("Replacement", {"Y", "N"}, 2).at(0) == 'Y') {
    if (commandersNum <
        maxAmountOfCommanders) /*if amount of commanders is less than max (not
                                  at max capacity)*/
    {
      printCosts(trainCosts, "training");

      if (OF.getInput("Proceed with training? (Y/N) ", {"Y", "N"}, 1).at(0) ==
          'Y') {
        proceedWithTraining(trainCosts);
      }
    } else {
      std::cout << "At maximum army commander amount. Training failed, "
                   "returning to menu \n";
    }
  } else {
    std::cout << "Returning to previous menu... " << std::endl;
  }
}

void ArmyDeploymentMA::proceedWithTraining(std::vector<int> trainCosts) {
  bool trainingSuccess = true;
  for (int x = 0; x < 5; x++) {
    capitalProvince->addResources(x, trainCosts[x] * -1);
    if (capitalProvince->getR(x) < 0) {
      trainingSuccess = false;
    }
  }
  if (trainingSuccess == true) {
    println("Commander training successful ");
    std::cout << "Current commanders: " << commandersNum + 1 << std::endl;

    CommanderProfile newCommander(1, participant->getNewName());
    newCommander.setLocation({capitalProvince->getCoordinate('X'),
                              capitalProvince->getCoordinate('Y')});
		capitalProvince -> addCommander (&newCommander);
  } else {
    std::cout << "Commander training failed (Not enough resources)... \n\n";
    for (int x = 0; x < 5; x++) {
      capitalProvince->addResources(x, trainCosts[x]);
    }
  }
}

void ArmyDeploymentMA::deployCommanderMF() {
  displayCommanders();
  bool returnToMenu = false;
  CommanderProfile *newCommander = selectCommander();
  newCommander->printCommanderStats();

	std::cout << "Deploy commander "
						<< newCommander->getUnitName()
						<< "? (Y/N) ";
	char confirmDeploy =
			OF.getInput("Replacement", {"Y", "N"}, 2).at(0);

	if (confirmDeploy == 'Y') {
		if (newCommander->hasMovedQuestion() == false) {
			Mobility newMobility(newCommander3, participant);
			newMobility.moveUnitOne();
			returnToMenu = true;
		} else {
			std::cout << "This unit has already moved... please pick another unit "
								<< std::endl;
		}
    }
	else {
    returnToMenu = true;
  }
  if (returnToMenu == false) {
    deployCommanderMF();
  }
  std::cout << "\nReturning to the Army Deployment action menu\n\n\n";
}

void ArmyDeploymentMA::displayCommanders() {
  std::cout << "You have " << participant->commandersNum() << " commanders: \n";

  for (int a = 0; a < participant->commandersNum(); a++) {
    CommanderProfile *newCommander = participant->getCommander(a);
    std::cout << "Commander " << newCommander->getName()
              << "; Level: " << newCommander->getLevel() << std::endl;
  }
}

void ArmyDeploymentMA::printCosts(std::vector<int> costs, std::string type) {
  std::cout << "The following are the " << type << " costs" : << std::endl;
  for (int x = 0; x < 5; x++) {
    cout << provinceResourcesNames[x] << ": " << costs[x];
  }

  cout << "The following are the resources currently in your capital: \n";
  capitalProvince->printResources();
}

// for (int x = 0; x < capitalProvince->howManyCommanders(); x++) {
//   int xCoordinate = newParticipant->listOfProvincesX[x];
//   int yCoordinate = newParticipant->listOfProvincesY[x];

//   listOfCommandersIndex.push_back(
//       provincesMap[xCoordinate][yCoordinate].returnCommanderIndex(x));
//   amountOfCommanders.push_back(x + 1);
// }