#include "Mobility.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

Mobility::Mobility(CommanderProfile *sCommander, Participants *newP)
{
	selectedCommander = sCommander;
	sCommanderX = selectedCommander->returnCoordinate('X');
	sCommanderY = selectedCommander->returnCoordinate('Y');
	participant = newP;
}

std::vector<Provinces *> Mobility::moveUnitTwo() {
  std::vector<Provinces *> std::vectorThingy;
  for (int x = -1; x <= 1;
       x++) /*Identify all the provinces that the player can move a unit to*/
  {
    for (int y = -1; y <= 1; y++) {
      // Check to see if the coordinates are in bounds (not outside of the map
      // size)
      if (/*X coordinate stuff*/ x >= 0 && x < continentSize &&
          /*Y coordinate stuff*/ y >= 0 && y < continentSize) {
        // Make sure province isn't the starting province
        if (x != 0 || y != 0) {
          // Add province to list of provinces can move to
          std::vectorThingy.push_back(
              &provincesMap[x + sCommanderX][y + sCommanderY]);
        }
      }
    }
  }
	return std::vectorThingy;
}

void Mobility::moveUnitOne() {
  std::vector<Provinces *> provincesCanSelect;
  if (selectedCommander->hasMovedQuestion() == 'N') {
    print ("The coordinates of the chosen unit unit are: (");
    print(translateCoordinate(sCommanderX, 'y', 'O') + ", " + translateCoordinate(sCommanderY, 'x', '0'));
		print(")\n\nYou can only move this unit to one of the provinces adjacent to the province it is in\n")
    provincesCanSelect = moveUnitTwo();

    // The participant slects coordiantes
    std::vector <int> moveTwo = getCoords(2);

    int provinceIndexSelected = 0;
    char provinceIsInList =
        'N'; // Initialize as province is not in list (have to repeat process)
    // Find the province (out of the list) elected using the coordinates chosen
    for (int x = 0; x < provincesCanSelect.size(); x++) {
      if (moveTwo[0] == provincesCanSelect[x]->getCoordinate('X') &&
          moveTwo[1] == provincesCanSelect[x]->getCoordinate('Y')) {
        provinceIndexSelected = x;
        provinceIsInList =
            'Y'; // Province is in list, don't have to repeat process
      }
    }

    // For display
    int moveToX = translateCoordinate(moveTwo[0], 'x', 'O');
    int moveToY = translateCoordinate(moveTwo[1], 'y', 'O');

    std::string confirmMove;
    char attackScenario = 'P'; /*P is for peace, A is for attack*/
    // If province is in the list
    if (provinceIsInList == 'Y') {
      Provinces *provinceSelected = provincesCanSelect[provinceIndexSelected];
			
      if (provinceSelected->getParticipantIndex() !=
          participant->getParticipantIndex()) {
        attackScenario = 'A';
        println ("Moving here will cause your unit to attack any enemy units stationed at this province.");
      }
      std::cout << "Confirm moving your unit to (" << moveToX << ", " << moveToY
                << ")? (Y/N) ";

      // If participants confirms movement
      if (getChar("Replacement", "YN", 2) == 'Y') {
        // If it's peaceful (moving to one of their own provinces)
        if (attackScenario == 'P') {
          selectedCommander->setLocation(moveTwo);

          provinceSelected->addCommanderProvince(indexInList);
        }
        // If scenario is attack
        else {
          AttackMA newAttackMA(unitXCoordinate, unitYCoordinate, moveToXTwo,
                               moveToYTwo, indexInList, belongsToParticipant);
          newAttackMA
              .playerAttack(); // fix this-- don't need to pass unitXCoordinate,
                               // can just use indexInList
        }
      }
    } else {
      std::cout << "Invalid province selected... please try again. " << std::endl;
      // Recursion until suitable coordinates are chosen
      moveUnitOne();
    }
  } else {
    std::cout
        << "This unit has already moved this turn. Please pick another unit. "
        << std::endl;
  }
  std::cout << "Returning to previous menu... " << std::endl << std::endl;
} /* unfinished*/