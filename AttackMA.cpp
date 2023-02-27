#include "AttackMA.h"

AttackMA::AttackMA(Provinces *defendingProvinceArg, Participants* attackingParticipantArg) {
  // Given a province to attack, see if you can attack with anything nearby
	attackingParticipant = attackingParticipantArg;
  defendingProvince = defendingProvinceArg;
  int DPX = defendingProvince->getCoordinate('X');
  int DPY = defendingProvince->getCoordinate('Y');
  std::vector<CommanderProfile *> commandersCanAttack;

  for (int x = -1; x < 2; x++) {
    for (int y = -1; y < 2; y++) {
      int candidateX = DPX + x;
      int candidateY = DPY + y;
      // check that coordinates are inbound
      if (DPX >= 0 && DPY >= 0 && DPY < continentSize && DPX < continentSize) {
        Provinces *newProvince = &provincesMap[DPX][DPY];
        for (int x = 0; x < newProvince->commandersNum(); x++) {
          commandersCanAttack.push_back(newProvince->returnCommander(x));
        }
      }
    }
  }

  if (commandersCanAttack.size() == 0) {
    std::cout
        << "There are no armies available to attack the enemy. Please move "
           "an army unit to one of the provinces around the target. \n\n";
  } else
    findCommander(commandersCanAttack);
}

void AttackMA::findCommander(std::vector <CommanderProfile *> commandersCanAttack) {
	std::string commanderName;
  std::cout << "The following commanders can attack the target: \n";
  std::cout << "Amount of commanders: " << commandersCanAttack.size() << std::endl;
  for (int x = 0; x < commandersCanAttack.size(); x++) {
    std::cout << "Commander " << commandersCanAttack[x]->getUnitName() << ", Level: " << commandersCanAttack[x]->getLevel();
  }
	std::cout << "Enter the name of the commander you would like to select: ";
	getline(std::cin, commanderName);
	if (attackingParticipant->hasCommander(commanderName) == false)
	{
		findCommander(commandersCanAttack);
	}
	attackingCommander = attackingParticipant -> getCommanderName(commanderName);
	defendingParticipant = &participantsList[defendingProvince->getParticipantIndex()];
	playerCommitAttack();
}

AttackMA::AttackMA(Provinces *attackerProvinceArg,
                   Provinces *defenderProvinceArg,
                   Participants *attackingParticipantArg,
                   CommanderProfile *commanderArg) {
  attackingProvince = attackerProvinceArg;
  defendingProvince = defenderProvinceArg;
  attackingParticipant = attackingParticipantArg;
  attackingCommander = commanderArg;
  playerCommitAttack();
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
        std::cout << "Invalid character entered. Please try again."
                  << std::endl;
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