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
  if (commandersNum > 0)
	{
		if (selectCommander() == true)
			upgradeCommandersTwo();
	}
  else 
    std::cout << "No commanders available, can not upgrade\n";
  
  OF.enterAnything();
}
void ArmyDeploymentMA::upgradeCommandersTwo() 
{
  selectedCommander->printCosts(newCommander->getUpgradeCosts());

	char proceedWithUpgradeQuestion =
      OF.getInput("\nProceed with upgrade? ", {"Y", "N"}, 1).at(0);
  if (proceedWithUpgradeQuestion == 'Y') {

    std::array<int, 5> commanderCosts = newCommander->getUpgradeCosts();
		bool commanderUpgradeIsSuccess = capitalProvince->subtractCheckResources(commanderCosts);

    if (commanderUpgradeIsSuccess == true) {
      newCommander->addLevel();
      std::cout << "Upgrade successful; Commander " << newCommander->returnName() << "is now level " << newCommander->returnLevel() << std::endl;
    } else {
      capitalProvince->modifyResources(commanderCosts, true);
      std::cout << "Upgrade failed. " << std::endl;
    }
  }
}

bool *ArmyDeploymentMA::selectCommander() {
  displayCommanders();
  std::string commanderName = " ";
  println("Enter the name of the commander you wish to select: ");
  getline(std::cin, commanderName);

  if (participant->hasCommander(commanderName) == false) 	{
		println("Invalid character entered. Please try again... (Enter any character to continue)");
    selectCommander();
  } 
	else 
		std::cout << "Commander " << commanderName << " selected...\n";
	
	selectedCommander = participant->getCommanderByName(commanderName);

	std::cout << "Confirm selection of commander " << newCommander->returnName() << "? (Y/N): ";
	char confirmSelection = OF.getInput("0", {"Y", "N"}, 2).at(0);

	if (confirmSelection == 'Y')
		return true;
	return false;
	
}

void ArmyDeploymentMA::viewArmyOverview() {
  if (selectCommander() == true)
	{
		std::cout << "Commander " << newCommander->returnName() << " selected... " << std::endl;
    std::cout << "The coordinates of this Commander: " << newCommander->printOutputCoordinates() << "\n\n";

    newCommander->printCommanderStats();
	}
	OF.enterAnything();	
}

void ArmyDeploymentMA::trainCommanders() {
  std::string yesOrNoString;
  std::cout << "You have " << commandersNum << "/" << selectedCommander->getMaxCommanders() << " total army commanders. \n";
  std::cout << "Do you want to train a commander? (Y/N) ";

  std::array<int, 5> trainCosts = participant->getTrainCosts();

  if (OF.getInput("Proceed with training", {"Y", "N"}, 1).at(0) == 'Y') 	{
    if (commandersNum < maxAmountOfCommanders) /*if amount of commanders is less than max (not at max capacity)*/
        proceedWithTraining(trainCosts);
    else 
      std::cout << "At maximum army commander amount. Training failed, returning to menu \n";
  } 
	else 
    OF.enterAnything();
}

void ArmyDeploymentMA::proceedWithTraining(std::array<int,5> trainCosts) {
  bool trainingSuccess = capitalProvince->subtractCheckResources(trainCosts);

  if (trainingSuccess == true) 
	{
    CommanderProfile newCommander(1, participant->getNewName());
    newCommander.setLocation(capitalProvince->returnCoordinates());
    capitalProvince->addCommander(&newCommander);
		
		println("Commander training successful ");
    std::cout << "Current commanders: " << commandersNum << std::endl;
  } 
	else 
	{
    std::cout << "Commander training failed (Not enough resources)... \n\n";
    capitalProvince->addResources(trainCosts);
  }
}

void ArmyDeploymentMA::deployCommanderMF() 
{
  if (selectCommander() == false)
		return;
	
  selectedCommander->printCommanderStats();

  std::cout << "Deploy commander " << selectedCommander->getUnitName() << "? (Y/N) ";
  char confirmDeploy = OF.getInput("Replacement", {"Y", "N"}, 2).at(0);

  if (confirmDeploy == 'Y') 
	{
    if (selectedCommander->hasMovedQuestion() == false) {
      Mobility newMobility(newCommander, participant);
      newMobility.moveUnitOne();
      returnToMenu = true;
    } 
		else 
		{
			std::cout << "This unit has already moved... please pick another unit \n";
			deployCommanderMF();
		}

  OF.enterAnything();
}

void ArmyDeploymentMA::displayCommanders() {
  std::cout << "Here is list of your commanders: \n";
	std::unordered_map<std::string, CommanderProfile*> commandersMap = participant->getCommandersMap;
  std::unordered_map<std::string, CommanderProfile*>::iterator it;
  for (it = commandersMap.begin(); it != commandersMap.end(); it++) 	{
    CommanderProfile *tempCommander = it->second;
    std::cout << "- Commander " << tempCommander->returnName() << "; Level: " << tempCommander->returnLevel() << std::endl;
    delete tempCommander;
  }
}

void ArmyDeploymentMA::printCosts(std::vector<int> costs, std::string type) {
  std::cout << "The following are the " << type << " costs: \n";
  for (int x = 0; x < 5; x++)
    std::cout << provinceResourcesNames[x] << ": " << costs[x];

  std::cout << "The following are the resources currently in your capital: \n";
  capitalProvince->printResources();
}

// for (int x = 0; x < capitalProvince->howManyCommanders(); x++) {
//   int xCoordinate = newParticipant->listOfProvincesX[x];
//   int yCoordinate = newParticipant->listOfProvincesY[x];

//   listOfCommandersIndex.push_back(
//       provincesMap[xCoordinate][yCoordinate].returnCommanderIndex(x));
//   amountOfCommanders.push_back(x + 1);
// }