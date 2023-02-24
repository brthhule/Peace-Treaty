#include "PlayerAction.h"


using namespace std;
extern int turn;

PlayerAction::PlayerAction ()
{
	
}

PlayerAction::PlayerAction(Participants *newP)
{
	participant = newP;
}

int PlayerAction::initialDecision()
{

	clearScreen();

	std::cout << "Turn: " << turn << endl << endl;
	std::cout << "Welcome to the Main menu " << endl;
	showMap();
	char courseOfAction = ' ';
	if (participant->isPlayer()) //If the participant is the player
	{
		Lists newList (4);
		courseOfAction = newList.listOfActions();
	}
	else //If the participant is the AI
	{
		courseOfAction = randomAction();
	}

	std::cout << endl;
	clearScreen();

	switch (courseOfAction)
	{
	case 'B':
	{
			BuildMA newBuildMA();
			newBuildMA.findProvinceCoordinates();
			break;
	}
	case 'T':
	{
			TrainMA newTrainMA(1, 1);/*Constructor with no arguments didn't work (???)*/
			newTrainMA.findProvinceCoordinates();
			newTrainMA.TrainMAFunction();
			break;
	}
	case 'S':
			participant->viewStats();
			break;
	case 'U':
	{
			MapMA newMap;
			newMap.viewPlayerMap();
			break;
	}
	case 'D':
	{
			ArmyDeploymentMA newArmyDeploymentMA;
			newArmyDeploymentMA.armyDeploymentMF();
			break;
	}
	case 'N':
			return -1;
	case 'H':
	{
		Lists newList (4);
		newList.listOfHelp();
		char whenYouDoneChar = getChar(" ", "P", 2);
		break;
	}
	case 'P':
	{
		char pauseGameQuestionChar = getChar("Pausing the game will end this session of gameplay. Proceed? (Y/N): ", "YN", 1);
		if (pauseGameQuestionChar == 'Y')
		{
			pauseGame();
		}
		std::cout << "Returning to the Main menu... " << endl;
		return -2;
	}
	}
	initialDecision();
}

char PlayerAction::randomAction()
{
    int randomNumber = rand() % 6;//Random number 0 to 5 (inclusive)
    char randomChar = ' ';
    switch (randomNumber)
    {
    case 0:
        randomChar = 'B';
        break;
    case 1:
        randomChar = 'T';
        break;
    case 2:
        randomChar = 'V';
        break;
    case 3:
        randomChar = 'M';
        break;
    case 4:
        randomChar = 'A';
        break;
    case 5:
        randomChar = 'G';
        break;
    }
    return randomChar;
}

