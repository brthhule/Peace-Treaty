#include "ScoutMA.h"

#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

extern std::vector<std::vector<Provinces>> provincesMap;
extern std::vector<Participants> participantsList;
extern std::vector<std::vector<CommanderProfile>> allCommanders;
extern int currentParticipantIndex;
extern int continentSize;
extern int turn;

ScoutMA::ScoutMA(Participants *newParticipant, Provinces *newProvince) {
  participant = newParticipant;
  yourProvince = newProvince;
}

void ScoutMA::selectTargetToScout() /*So much to fix here... truly so much....
                                       make sure to simplify things later on*/
{
  targetProvince = participant->getCoords(1);
  if (targetProvince->getParticipantIndex() == participant->getParticipantIndex())
	{
		std::cout << "This province belongs to you; please select a different province";
		selectTargetToScout();
	}
	
  std::cout << "Province " << targetProvince->getUnitName() << " selected " << std::endl;
  std::cout << "You can only scout this unit if one of your provinces or commanders is next to it... "
            << std::endl;

  for (int a = -1; a <= 1;
       a++)
  {
    for (int b = -1; b <= 1; b++) {
      if (/*X coordinates*/ targetProvince->getCoordinate('X') + a >= 0 &&
          targetXCoordinate + a < continentSize &&
          /*Y coordinates*/ targetYCoordinate + b >= 0 &&
          targetYCoordinate + b < continentSize) {
        if (provincesMap[targetXCoordinate + a][targetYCoordinate + b]
                .getBelongsToParticipant() == currentParticipantIndex) {
          provincesCanSelectX.push_back(targetXCoordinate + a);
          provincesCanSelectY.push_back(targetYCoordinate + b);
        }

        for (int x = 0; x < attackingParticipant->howManyCommanders(); x++) {
          if (allCommanders[currentParticipantIndex][x].getCoordinate('X') ==
                  targetXCoordinate + a &&
              allCommanders[currentParticipantIndex][x].getCoordinate('Y') ==
                  targetXCoordinate + b) {
            commandersCanSelect.push_back(x);
          }
        }
      }
    }
  }

  // If there are commanders or provinces that can scout the target
  if (provincesCanSelectX.size() > 0 || commandersCanSelect.size() > 0) {
    playerScoutStepTwo();
  } else {
    std::cout << "No player provinces or armies are around the target... "
              << std::endl;
  }
  std::cout << "Returning to previous menu" << std::endl << std::endl;
} /*fix this-- needs to be reviewed*/

void ScoutMA::playerScoutStepTwo() // Finish this later
{
  int accuracy = 0;
  std::vector<int> unitsCanScoutWith;

  std::cout << "You have "
            << provincesCanSelectX.size() + commandersCanSelect.size()
            << " provinces and armies next to the target. Below is a list of "
               "units that can scout the target.";
  std::cout << " Please note that the higher the level of the scouting unit, "
               "the more accurate the results of the scout report are (The "
               "level of the target unit is "
            << enemyLevel << "). " << std::endl
            << std::endl;

  std::vector<int> unitLevels = showUnitsCanScout();
  int cutOffThingy = unitLevels[0];
  unitLevels.erase(unitLevels.begin());

  for (int x = 1; x <= unitLevels.size(); x++) {
    unitsCanScoutWith.push_back(x);
  }
  std::cout << std::endl;

  int scoutWithThis =
      stoi(OF.getInput("Please enter the number of the unit you would like to select: ",
             unitsCanScoutWith, 1));
  scoutWithThis--;

  int xCoordinateThingy = 0;
  int yCoordinateThingy = 0;
  int unitAccuracyLevel = 0;

  std::cout << "Proceed scout action with unit at ("
            << translateCoordinate(xCoordinateThingy, 'x', 'O') << ", "
            << translateCoordinate(yCoordinateThingy, 'y', 'O') << ")? (Y/N) ";
  char proceedWithScoutChar = getChar(" ", "YN", 2);

  if (proceedWithScoutChar == 'Y') {
    int accuracy = 50;
    if (unitLevels[scoutWithThis] > enemyLevel) {
      for (int x = unitLevels[scoutWithThis]; x >= enemyLevel; x--) {
        accuracy += 5;
      }
    }
    if (unitLevels[scoutWithThis] < enemyLevel) {
      for (int x = unitLevels[scoutWithThis]; x <= enemyLevel; x++) {
        accuracy -= 5;
      }
    }

    if (accuracy > 100) {
      accuracy = 100;
    }
    if (accuracy < 0) {
      accuracy = 0;
    }

    if (scoutWithThis < cutOffThingy) {
      Participants *newParticipant = &participantsList[currentParticipantIndex];
      provincesMap[newParticipant->listOfProvincesX[scoutWithThis]]
                  [newParticipant->listOfProvincesY[scoutWithThis]]
                      .completeProvinceScoutReport(accuracy);
    } else {
      Participants *newParticipant = &participantsList[currentParticipantIndex];
      allCommanders[currentParticipantIndex][scoutWithThis]
          .completeCommanderScoutReport(accuracy);
    }
  }
}
std::vector<int> ScoutMA::showUnitsCanScout() {
  Participants *attackingParticipant =
      &participantsList[currentParticipantIndex];

  std::vector<int> unitLevels = {0};
  std::cout << "\033[;34m";
  std::vector<CommanderProfile *> commandersCanSelect;
  char commanderThingy = ' ';
  int provinceIndex = 0;
  int commanderIndex = 0;
  // For all the provinces in the std::vector

  std::cout << "Provinces that can scout: " << std::endl;
  for (int a = 0; a < provincesCanSelectX.size(); a++) {
    unitLevels.push_back(
        provincesMap[provincesCanSelectX[a]][provincesCanSelectY[a]]
            .findProvinceLevel());
    std::cout << a + 1 << ": ("
              << translateCoordinate(provincesCanSelectX[a], 'x', 'O') << ", "
              << translateCoordinate(provincesCanSelectY[a], 'y', 'O') << "); ";
    std::cout << "Unit level: " << unitLevels.back();
  }
  int cutOffProvinceCommanderThingy = (int)unitLevels.size() - 1;
  unitLevels[0] = cutOffProvinceCommanderThingy;

  std::cout << "Commanders that can scout: " << std::endl;
  for (int a = 0; a < commandersCanSelect.size(); a++) {
    unitLevels.push_back(commandersCanSelect[a]->getCommanderLevel());
    std::cout << a + a << ": ("
              << translateCoordinate(commandersCanSelect[a]->getCoordinate('X'),
                                     'x', 'O')
              << ", "
              << translateCoordinate(commandersCanSelect[a]->getCoordinate('Y'),
                                     'y', 'O')
              << "); ";
    std::cout << "Unit level: " << unitLevels.back();
  }
  std::cout << std::endl;
  std::cout << "\033[;0m";
  return unitLevels;
}
