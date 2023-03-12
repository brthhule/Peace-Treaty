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
	provincesCanScout = {};
	commandersCanScout = {};
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
	
  std::cout << "Province " << targetProvince->getUnitName() << " selected \n";
  std::cout << "You can only scout this unit if one of your provinces or commanders is next to it... \n";

	//Check nearby provinces
	getCanScout();
  // If there are commanders or provinces that can scout the target
  if (provincesCanScout.size() > 0 || commandersCanScout.size() > 0) {
    playerScoutStepTwo();
  } else {
    std::cout << "No player provinces or armies are around the target... \n";
  }
  std::cout << "Returning to previous menu\n\n";
} /*fix this-- needs to be reviewed*/

void ScoutMA::playerScoutStepTwo() // Finish this later
{
  int accuracy = 0;
  std::vector<int> unitsCanScoutWith;

  std::cout << "You have "
            << provincesCanScout.size()
            << " provinces and " << commandersCanScout.size() << "armies next to the target. Below is a list of "
               "units that can scout the target.";
  std::cout << " Please note that the higher the level of the scouting unit, "
               "the more accurate the results of the scout report are (The "
               "level of the target unit is "
            << enemyLevel << "). \n\n";

	std::string returnUnitName = " ";
	bool isProvince = false;
  int unitlevel = selectUnitToScout(returnUnitName, isProvince, coordinates);

  int xCoordinateThingy = 0;
  int yCoordinateThingy = 0;
  int unitAccuracyLevel = 0;

  std::cout << "Proceed scout action with unit at ("
            << OF.printCoordinates(coordinates) << "? (Y/N) ";
  char proceedWithScoutChar = OF.getInput(" ", {"Y", "N"}, 2).at(0);

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

void ScoutMA::getCanScout()
{
	int targetX = targetProvince->getCoordinate('X');
	int targetY = targetProvince->getCoordinate('Y');
	
	for (int a = -1; a <= 1;
       a++)
  {
    for (int b = -1; b <= 1; b++) {
			
      if (/*X coordinates*/ targetX + a >= 0 &&
          targetX + a < continentSize &&
          /*Y coordinates*/ targetY + b >= 0 &&
          targetY + b < continentSize) {
				
        if (provincesMap[targetX + a][targetY + b].getParticipantIndex() == currentParticipantIndex) {
					provincesCanScout.push_back(&provincesMap[targetX + a][targetY+ b]);
        }

        for (int x = 0; x < participant->commandersNum(); x++) {
					CommanderProfile* newCommander = participant->getCommander(x);
					std::vector<int> newVector = {targetX + a, targetY + b};
          if (newCommander->returnCoordinates() == newVector)
			{
            commandersCanScout.push_back(newCommander);
          }
        }
      }
    }
  }
}

int ScoutMA::selectUnitToScout(int &unitName, bool &isProvince, std::array<int, 2> &coordinates) {
	int unitLevel = 0;
	std::cout << "\033[;34m";
 
  // For all the provinces in the std::vector

  std::cout << "Provinces that can scout: " << std::endl;
  for (Provinces* province: provincesCanScout) {
    std::cout<< province->getUnitName() << "; " << province->printOutputCoordinates() << "; Level: " << province->returnLevel() << std::endl;
  }

  std::cout << "Commanders that can scout: " << std::endl;
  for (CommanderProfile* commander: commandersCanScout) {
     std::cout<< commander->getUnitName() << "; " << commander->printOutputCoordinates() << "; Level: " << commander->returnLevel() << std::endl;
  }
  std::cout << "\n\033[;0m";

	std::string newUnitName = " ";
	print("Enter the name of the province/commander you wish to select to scout: ");
	std::getline(std::cin, newUnitName);

	if (checkHasUnit(newUnitName) == false)
	{
		std::cout << "Invalid name entered; please try again \n";
		selectUnitToScout(newUnitName, isProvince, coordinates);
	}
	println(unitName + " selected...");
	isProvince = false;
	for(Provinces* province: provincesCanScout)
		if (newUnitName == province -> getUnitName())
		{
			isProvince = true;
			province->returnCoordinates(coordinates);
		}
	for (CommanderProfile* commander: commandersCanScout())
		if (unitName == commander->getUnitName())
			commander->returnCoordinates(coordinates);
	
	returnUnitName = unitName;
  return unitLevel;
}

bool ScoutMA::checkHasUnit (std::string unitName)
{
	for (Provinces* province: provincesCanScout)
		if (unitName == province->getUnitName())
			return true;
	for (CommanderProfile* commander: commandersCanScout)
		if (unitName == commander -> getUnitName())
			return true;
	return false;
}
