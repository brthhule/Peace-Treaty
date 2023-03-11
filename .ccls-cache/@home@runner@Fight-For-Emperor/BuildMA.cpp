#include "BuildMA.h"
#define print(x)std::cout << x;
#define println(x)std::cout << x << std::endl;

extern std::vector<std::vector<Provinces>> provincesMap;
extern std::string buildingNames[6];
extern std::string provinceResourcesNames[5];
extern int currentParticipantIndex;

BuildMA::BuildMA() { province = findProvince(); }
BuildMA::BuildMA(Provinces *newProvince, Participants *newParticipant) {
  province = newProvince;
  participant = newParticipant;
}

Provinces *BuildMA::findProvince() {
  std::cout << "Welcome to the Player Build menu" << std::endl << std::endl;
  province = participant->getCoords(1);

  if (province->getCoordinate('X') != -1) {
      if (province->getParticipantIndex() == participant->getParticipantIndex()) {
      playerBuildFunction();
      } else {
      std::string anyInput = " ";
      print("Invalid province elected. Please try again. \nEnter anything to "
            "proceed back to the Player Build menu (Screen will clear) ");
      std::getline(std::cin, anyInput);
      OF.clearScreen();
      }
      std::cout << std::endl;
  }
}

void BuildMA::playerBuildFunction() {
  OF.clearScreen();
  println(
      "---------- Start printing province information ----------\n\033[34m");
  println("Province of kingdom " + participant->getKingdomName());
 std::cout << "Coordinates: ("
       << OF.translateCoordinate(province->getCoordinate('X'), 'x', 'O') << ", "
       << OF.translateCoordinate(province->getCoordinate('Y'), 'y', 'O')
       << ") \n\n\033[0m";

  province->printResources();
  province->printBuildingStats();
  println("---------- End printing province information ----------\n");

  char upgradeBuilding = ' ';
  char repeatPlayerBuildFunction = 'Y';

  Lists newList(7);
  upgradeBuilding = newList.listOfActions();
  if (upgradeBuilding == 'U') {
    upgradeBuildings();
    playerBuildFunction();
    std::cout << std::endl;
  } else {
    std::cout << "Returning to previous menu... " << std::endl;
    OF.clearScreen();
  }
}

void BuildMA::upgradeBuildings() {
  std::vector<int> requiredResources = {0, 0, 0, 0, 0};
  int buildingNumber = 0;
	std::vector<std::string> buildingLetterList = {"F", "L", "Q", "M", "C", "B", "H"};

  char buildingLetter = OF.getInput("Enter the first letter of the building you want to upgrade (enter 'H' for help): ", buildingLetterList, false).at(0);
	
  if (buildingLetter != 'H') {
    for (int x = 0; x < 6; x++) {
      if (buildingLetter == buildingLetterList[x].at(0)) {
        buildingNumber = x;
        x = 6;
      }
    }

    printInformation(buildingNumber, requiredResources);
    char upgradeProceed = OF.getInput("Proceed with upgrade? (Y/N) ", {"Y", "N"}, 1).at(0);

    if (upgradeProceed == 'Y') {
      bool upgradeSuccess = true;
			
			province->subtractResources(requiredResources);
			for (int g: province->getAllResources())
				if (g < 0)
					upgradeSuccess = false;


      if (upgradeSuccess == false) {
        province->addResources(requiredResources);
        println("Upgrade failed. Not enough resources. ");
      } else {
        println("Upgrade successful.\n");
        province->increaseBuildingLevel(buildingNumber, 1);
      }
    }
  } else {
    Lists newList(12);
    newList.listOfHelp();
  }
	
  char upgradeAgain = OF.getInput("Upgrade another building (Y/N): ", {"Y", "N"}, 1).at(0);
  if (upgradeAgain == 'Y') {
    upgradeBuildings();
  }
  std::cout << "Returning to Build Infrastructure action menu. " << std::endl;
}

void BuildMA::printInformation(int buildingNumber, std::vector<int> requiredResources) {
 std::cout << "---------- Start printing information----------\n\n\033[34m";
  println(buildingNames[buildingNumber] + " selected \n");
  println("The following is the cost of the upgrade: ");
  for (int x = 0; x < 5; x++) {
    requiredResources[x] = (int)requiredResourcesBuildings[buildingNumber][x] *
                           province->getBuildingLevel(x);
    std::cout << provinceResourcesNames[x] << ": " << requiredResources[x]
              << std::endl;
  }
  println("\nThe following are how many resources are in this province: ");
  province->printResources();
 std::cout << "----------End printing informatio----------" << std::endl;
}