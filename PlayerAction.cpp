#include "PlayerAction.h"

extern int turn;

PlayerAction::PlayerAction() {}

PlayerAction::PlayerAction(Participants *newP) { participant = newP; }

int PlayerAction::initialDecision() {

  OF.clearScreen();

  std::cout << "Turn: " << turn << std::endl << std::endl;
  std::cout << "Welcome to the Main menu " << std::endl;
  participant->showMap();
  char courseOfAction = ' ';
  if (participant->getParticipantIndex() != -1) // If the participant is the player
  {
    Lists newList(4);
    courseOfAction = newList.listOfActions();
  } else // If the participant is the AI
  {
    courseOfAction = randomAction();
  }

  std::cout << std::endl;
  OF.clearScreen();

  switch (courseOfAction) {
  case 'B': {
		Provinces *newProvince = participant->getYourProvince(1);
    BuildMA newBuildMA(newProvince, participant);
    break;
  }
  case 'T': {
		Provinces *newProvince = participant->getYourProvince(1);
    TrainMA newTrainMA(newProvince);
    newTrainMA.TrainMAFunction();
    break;
  }
  case 'S':
    participant->viewStats();
    break;
  case 'U': {
    MapMA newMap(participant);
    newMap.viewPlayerMap();
    break;
  }
  case 'D': {
    ArmyOverviewMA newArmyOverview(participant);
    newArmyOverview.armyDeploymentMF();
    break;
  }
  case 'N':
    return -1;
  case 'H': {
    Lists newList(4);
    newList.listOfHelp();
    char whenYouDoneChar = OF.getInput(" ", {"P"}, 2).at(0);
    break;
  }
  case 'P': {
    char pauseGameQuestionChar = OF.getInput(
        "Pausing the game will end this session of gameplay. Proceed? (Y/N): ",
		{"Y", "N"}, 1).at(0);
    if (pauseGameQuestionChar == 'Y') {
      pauseGame();
    }
    std::cout << "Returning to the Main menu... " << std::endl;
    return -2;
  }
  }
  initialDecision();
}

char PlayerAction::randomAction() {
  int randomNumber = rand() % 6; // Random number 0 to 5 (inclusive)
	std::vector<char> newVector = {'B', 'T', 'V', 'M', 'A', 'G'};
  return newVector[randomNumber];
}


void PlayerAction::pauseGame() {
  std::string gameCode;
  gameCode += continentSize;

  for (int x = 0; x < continentSize; x++) {
    for (int y = 0; y < continentSize; y++) {
      gameCode += provincesMap[x][y].getParticipantIndex();
    }
  }
  std::cout << "Game ended... \nHere is your game code (Copy this code and "
               "paste it when using the 'Resume Game' functionality): "
            << gameCode << "\n\n";
}