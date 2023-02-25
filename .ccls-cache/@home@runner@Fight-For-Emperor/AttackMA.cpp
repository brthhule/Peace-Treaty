#include "AttackMA.h"

AttackMA::AttackMA(std::vector<int> unitAttackingArg, std::vector <int> unitAttackedArg, Participants * attackingParticipantArg, CommanderProfile* commanderArg) {
	unitAttacking = unitAttackingArg;
	unitAttacked = unitAttackedArg;
	attackingParticipant = attackingParticipantArg;
	commander = commanderArg;
	attackedParticipant = &participantsList[provincesMap[unitAttacked[0]][unitAttacked[1]].getParticipantIndex()];
}

void AttackMA::playerAttack() /*fix this*/
{
  Participants *newParticipant = &participantsList[currentParticipantIndex];
  if (commanderIndex == -1) {
    char canAttack = 'N';
    int amountOfHeros = 0;
    int herosCanAttack[2][4] = {0};
    int z = 0;
    int attackUnitWithX = 0;
    int attackUnitWithY = 0;

    int forLoopX;
    int forLoopY;

    for (int x = -1; x < 2; x++) {
      for (int y = -1; y < 2; y++) {
        forLoopX = unitAttacked[0] + x;
        forLoopY = unitAttacked[1] + y;
        if (forLoopX >= 0 && forLoopX < continentSize) {
          if (forLoopY >= 0 && forLoopY < continentSize) {
            if (provincesMap[forLoopX][forLoopY].commanders.size() >
                0) {
              amountOfHeros++;
              canAttack = 'Y';
              herosCanAttack[0][z] = unitAttacking[0] + x;
              herosCanAttack[1][z] = unitAttacking[y] + y;
              z++;
            }
          }
        }
      }
    }

    if (amountOfHeros == 0) {
      std::cout
          << "There are no armies available to attack the enemy. Please move "
             "an army unit to one of the provinces around the target. \n\n";
    }
    if (amountOfHeros < 0) {
      std::cout << "The following armies can attack the target: \n";
      std::cout << "Amount of heros: " << amountOfHeros << std::endl;
      for (int x = 0; x < amountOfHeros; x++) {
        std::cout << "1: (" << herosCanAttack[0][x] << ", "
                  << herosCanAttack[1][x] << ") ";
      }
      char repeatVerifyCanAttack = 'Y';

      do {
        attackingParticipant->getCoordinates(3, attackUnitWithX, attackUnitWithY);
        std::cout << std::endl;
        if (attackUnitWithX == -1 || attackUnitWithY == -1) {
          std::cout << "Returning to previous menu... " << std::endl << std::endl;
          repeatVerifyCanAttack = 'N';
        } else {
          char verifyCanAttack = ' ';

          for (int b = 0; b < amountOfHeros; b++) {
            if (attackUnitWithX == herosCanAttack[0][b] &&
                attackUnitWithY == herosCanAttack[1][b]) /*fix this*/
            {
              verifyCanAttack = 'Y';
            }
          }

          if (verifyCanAttack == 'Y') {
            for (int playerCommanderIndex = 0;
                 playerCommanderIndex < newParticipant->commandersNum();
                 playerCommanderIndex++) {
              if (attackUnitWithX == allCommanders[currentParticipantIndex]
                                                  [playerCommanderIndex]
                                                      .getCoordinate('X') &&
                  attackUnitWithY == allCommanders[currentParticipantIndex]
                                                  [playerCommanderIndex]
                                                      .getCoordinate('Y')) {
                return playerCommitAttack(); /*May have to fix this at some
                                                point*/
              }
            }
          } else {
            std::cout << "Invalid unit selected. Please try again" << std::endl;
            break;
          }
        }
      } while (repeatVerifyCanAttack == 'Y');
    }
  } else {
    playerCommitAttack();
  }
}
void AttackMA::playerCommitAttack() {
  Participants *newParticipant = &participantsList[currentParticipantIndex];
  std::vector<char> targetEnemyCommanders;

  int oldResources[5] = {0};
  for (int x = 0; x < 5; x++) {
    oldResources[x] =
        allCommanders[currentParticipantIndex][commanderIndex].getResource(x);
  }

  Provinces *newProvince =
      &provincesMap[unitBeingAttackedX][unitBeingAttackedY];
  enemyParticipantIndex = newProvince->getBelongsToParticipant();

  for (int a = 0; a < newProvince->commandersPresentIndex.size(); a++) {
    commandersBeingAttackedIndices.push_back(
        newProvince->returnCommanderIndex(a));
  }
  // Fix this-- add functionality to go through each commander and province
  // garrison

  Participants *enemyParticipant = &participantsList[enemyParticipantIndex];
  if (allCommanders[enemyParticipantIndex][commandersBeingAttackedIndices[0]]
          .getCommanderArmyCP() <
      allCommanders[currentParticipantIndex][commanderIndex]
          .getCommanderArmyCP()) /*if the enemy defender has less CP than
                                    attacking player army*/
  {
    ;
    std::cout << "You won! ";
    playerCommitAttackWin(oldResources);
  } else if (allCommanders[enemyParticipantIndex]
                          [commandersBeingAttackedIndices[0]]
                              .getCommanderArmyCP() >
             allCommanders[currentParticipantIndex][commanderIndex]
                 .getCommanderArmyCP()) /*if defending enemy has more CP than
                                           attacking player*/
  {                                     /*fix this-- add on to this*/
  }
}
void AttackMA::playerCommitAttackWin(int oldResources[5]) {
  Participants *newParticipant;
  newParticipant = &participantsList[currentParticipantIndex];

  for (int x = 0; x < 5; x++) {
    // Add resources from the first element in the enemy's list of commnaders to
    // the player's commander
    allCommanders[currentParticipantIndex][commanderIndex].addResources(
        x,
        allCommanders[enemyParticipantIndex][commandersBeingAttackedIndices[0]]
            .getResource(x));
  }
  int difference =
      allCommanders[currentParticipantIndex][commanderIndex]
          .getCommanderArmyCP() /
      allCommanders[enemyParticipantIndex][commandersBeingAttackedIndices[0]]
          .getCommanderArmyCP();
  int lostCombatPower =
      allCommanders[enemyParticipantIndex][0].getCommanderArmyCP() *
      (1 / difference);
  int deadTroops[5] = {0};
  int injuredTroops[5] = {0};

  for (int a = 0; lostCombatPower > 0; a++) {
    battleCalculations(lostCombatPower, deadTroops, a);
    for (int x = 0; x < 5; x++) {
      injuredTroops[x] = deadTroops[x] / (2 * enemyDifficulty);
      deadTroops[x] -= injuredTroops[x];
    }
    for (int x = 10; x < 15; x++) {
      allCommanders[currentParticipantIndex][commanderIndex].addInjuredTroops(
          x, injuredTroops[x - 10]); /*fix this?*/
    }

    std::cout << "  Results: " << std::endl << std::endl;
    std::cout << "Resources gained: " << std::endl;
    for (int x = 0; x < 5; x++) /*print out resources*/
    {
      std::cout << provinceResourcesNames[x] << " gained: "
                << allCommanders[currentParticipantIndex][commanderIndex]
                           .getResource(x) -
                       oldResources[x]
                << std::endl;
    }
    casualtyReport(deadTroops, injuredTroops);

    char viewAllArmyStats = ' ';
    char repeatViewAllArmyStats = 'N';
    std::string viewAllArmyStatsString;

    provincesMap[unitAttackingX][unitAttackingY].addCommanderProvince(
        commanderIndex);

    do {
      repeatViewAllArmyStats = 'N';
      viewAllArmyStats = getChar("View all army stats? (Y/N) ", "YN", 1);
      std::cout << std::endl;

      switch (viewAllArmyStats) {
      case 'Y': {
        allCommanders[currentParticipantIndex][commanderIndex]
            .printCommanderStats();
        break;
      }
      case 'N':
        break;
        std::cout << std::endl;
      default:
        repeatViewAllArmyStats = 'Y';
        std::cout << "Invalid character entered. Please try again." << std::endl;
        break;
      }
    } while (repeatViewAllArmyStats == 'Y');

    /*fix this-- add attack functionality, differences in CP and stuff*/
  }
}
void AttackMA::battleCalculations(int lostCombatPower, int deadTroops[5],
                                  int a) {
  Participants *attackingParticipant =
      &participantsList[currentParticipantIndex];

  switch (a) {
  case 0:
  case 1:
  case 2:
  case 3: {
    int b = a + 5;
    battleCalculationsTwo(lostCombatPower, deadTroops, b);
    break;
  }
  case 4:
    if (allCommanders[currentParticipantIndex][commanderIndex].getTroopsPresent(
            9) > 0) {
      if (lostCombatPower > 0) {
        lostCombatPower -= troopsCP[a];
        deadTroops[a]++;
        allCommanders[currentParticipantIndex][commanderIndex].removeTroops(9,
                                                                            1);
        participantsList[currentParticipantIndex].playerTroopsLost[a] += 1;
      }
    }
    a = -1;
    break;
  }
}
void AttackMA::battleCalculationsTwo(int &lostCombatPower, int deadTroops[5],
                                     int troopIndex) /*fix this*/
{
  Participants *playerParticipant = &participantsList[currentParticipantIndex];

  int z = abs(4 - troopIndex);

  for (int b = 0; b < troopsCP[z]; b++) {
    if (allCommanders[currentParticipantIndex][commanderIndex].getTroopsPresent(
            5) > 0) {
      b = troopsCP[z];
    } else {
      if (lostCombatPower > 0) {
        lostCombatPower -= troopsCP[troopIndex];
        deadTroops[troopIndex]++;
        allCommanders[currentParticipantIndex][commanderIndex].removeTroops(
            troopIndex, 1);
        participantsList[currentParticipantIndex]
            .playerTroopsLost[troopIndex] += 1;
      } else
        b = troopsCP[z];
    }
  }
}