#include "BuildMA.h"
#define print(x)std::cout << x;
#define println(x)std::cout << x << endl;

extern std::vector<Participants> participantsList;
extern int continentSize;

using namespace std;

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
  std::cout << "Welcome to the Player Build menu" << endl << endl;
  std::vector<int> coords = getCoords(1);

  province = &provincesMap[coords[0]][coords[1]];

  if (coords[0] != -1) {
      if (province->getParticipantIndex() == participant->getParticipantIndex()) {
      playerBuildFunction();
      } else {
      std::string anyInput = " ";
      print("Invalid province elected. Please try again. \nEnter anything to "
            "proceed back to the Player Build menu (Screen will clear) ");
      std::getline(cin, anyInput);
      clearScreen();
      }
      std::cout << endl;
  }
}

void BuildMA::playerBuildFunction() {
  clearScreen();
  println(
      "---------- Start printing province information ----------\n\033[34m");
  println("Province of kingdom " + participant->getKingdomName());
 std::cout << "Coordinates: ("
       << translateCoordinate(province->getCoordinate('X'), 'x', 'O') << ", "
       << translateCoordinate(province->getCoordinate('Y'), 'y', 'O')
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
    std::cout << endl;
  } else {
    std::cout << "Returning to previous menu... " << endl;
    clearScreen();
  }
}

void BuildMA::upgradeBuildings() {
  int requiredResources[5] = {0};
  int buildingNumber = 0;
  std::string buildingLetterList = "FLQMCBH";

  char buildingLetter = getChar("Enter the first letter of the building you want to upgrade (enter 'H' for help): ", "FLQMCBH", 1);
	
  if (buildingLetter != 'H') {
    for (int x = 0; x < 6; x++) {
      if (buildingLetter == buildingLetterList.at(x)) {
        buildingNumber = x;
        x = 6;
      }
    }

    printInformation(buildingNumber, requiredResources);
    char upgradeProceed = getChar("Proceed with upgrade? (Y/N) ", "YN", 1);

    if (upgradeProceed == 'Y') {
      bool upgradeSuccess = true;
      for (int x = 0; x < 5; x++) {
        province->addRSS(x, requiredResources[x] * -1);
        if (province->getResource(x) < 0) {
          upgradeSuccess = false;
        }
      }

      if (upgradeSuccess == false) {
        for (int x = 0; x < 5; x++) {
          province->addResources(x, requiredResources[x]);
        }
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
	
  char upgradeAgain = getChar("Upgrade another building (Y/N): ", "YN", 1);
  if (upgradeAgain == 'Y') {
    upgradeBuildings();
  }
  std::cout << "Returning to Build Infrastructure action menu. " << endl;
}

void BuildMA::printInformation(int buildingNumber, int requiredResources[5]) {
 std::cout << "---------- Start printing information----------\n\n\033[34m";
  println(buildingNames[buildingNumber] + " selected \n");
  println("The following is the cost of the upgrade: ");
  for (int x = 0; x < 5; x++) {
    requiredResources[x] = (int)requiredResourcesBuildings[buildingNumber][x] *
                           province->getBuildingLevel(x);
    std::cout << provinceResourcesNames[x] << ": " << requiredResources[x]
              << endl;
  }
  println("\nThe following are how many resources are in this province: ");
  province->printResources();
 std::cout << "----------End printing informatio----------" << endl;
}