#include "ArmyDeploymentMA.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

extern std::vector<Participants> participantsList;

extern std::string provinceResourcesNames[5];
extern int initialResources[5];
extern int currentParticipantIndex;

ArmyDeploymentMA::ArmyDeploymentMA(Participants *newP) {
  participant = newP;
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
		if (participant->selectCommander() == true)
			upgradeCommandersTwo();
	}
  else 
    std::cout << "No commanders available, can not upgrade\n";
  
  OF.enterAnything();
}
void ArmyDeploymentMA::upgradeCommandersTwo() 
{
  participant->selectedCommanderPrintCosts();

	char proceedWithUpgradeQuestion =
      OF.getInput("\nProceed with upgrade? ", {"Y", "N"}, 1).at(0);
  if (proceedWithUpgradeQuestion == 'Y') {

    std::array<int, 5> commanderCosts = participant->getSCCC();
		bool commanderUpgradeIsSuccess = participant->getCapital()->subtractCheckResources(commanderCosts);

    if (commanderUpgradeIsSuccess == true) {
      participant->SCAL();
      std::cout << "Upgrade successful; Commander " << participant->getSCName() << "is now level " << participant->getSCLevel() << std::endl;
    } else {
      participant->getCapital()->modifyResources(commanderCosts, true);
      std::cout << "Upgrade failed. " << std::endl;
    }
  }
}

void ArmyDeploymentMA::viewArmyOverview() {
  if (participant->selectCommander() == true)
	{
		std::cout << "Commander " << participant->getSCName() << " selected... " << std::endl;
    std::cout << "The coordinates of this Commander: ";
		participant->SC1();
		std::cout << "\n\n";

    participant->SC2();
	}
	OF.enterAnything();	
}

void ArmyDeploymentMA::trainCommanders() {
  std::string yesOrNoString;
  std::cout << "You have " << commandersNum << "/" << participant->getMaxCommanders() << " total army commanders. \n";
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
  bool trainingSuccess = participant->getCapital()->subtractCheckResources(trainCosts);

  if (trainingSuccess == true) 
	{
    participant->addCommander();
		
		println("Commander training successful ");
    std::cout << "Current commanders: " << commandersNum << std::endl;
  } 
	else 
	{
    std::cout << "Commander training failed (Not enough resources)... \n\n";
    participant->getCapital()->modifyResources(trainCosts, true);
  }
}

void ArmyDeploymentMA::deployCommanderMF() 
{
  if (participant->selectCommander() == false)
		return;
	
  participant->SC2();

  std::cout << "Deploy commander " << participant->getSCName() << "? (Y/N) ";
  char confirmDeploy = OF.getInput("Replacement", {"Y", "N"}, 2).at(0);

  if (confirmDeploy == 'Y') 
	{
    if (participant->SCMoved() == false) {
      Mobility newMobility(participant->getSCName(), participant);
      newMobility.moveUnitOne();
    } 
		else 
		{
			std::cout << "This unit has already moved... please pick another unit \n";
			deployCommanderMF();
		}

	  OF.enterAnything();
	}
}

void ArmyDeploymentMA::printCosts(std::vector<int> costs, std::string type) {
  std::cout << "The following are the " << type << " costs: \n";
  for (int x = 0; x < 5; x++)
    std::cout << provinceResourcesNames[x] << ": " << costs[x];

  std::cout << "The following are the resources currently in your capital: \n";
  participant->getCapital()->printResources();
}

