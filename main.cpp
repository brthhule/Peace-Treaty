//Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <string.h>
#include<stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <time.h>


//Player infrastructure
#include "Participants.h"
#include "AllUnits.h"
#include "Provinces.h"
#include "CommanderProfile.h"

//Miscellaneous
#include "coordinateFunctions.h"
#include "otherFunctions.h"
#include "textFunctions.h"
#include "Lists.h"

//Main Actions
#include "BuildMA.h"
#include "ArmyDeploymentMA.h"
#include "AttackMA.h"
#include "ScoutMA.h"
#include "MapMA.h"
#include "TrainMA.h"
#include "PlayerAction.h"

using namespace std;

char introduction();
void resumeGame();
void startGame(string kingdomName);
void generateNewContinent(string kingdomName);
void gamePlay();
void playerAction(int turn);
void endScreen();
void pauseGame();
void viewPlayerStats();
char randomPlayerActionChar();


void AITurn();
int pNum = 0;

/*Miscellaneous*/
int currentParticipantIndex = 0;
vector <vector <Provinces*>> provincesMap;
vector <Participants*> participantsList;
int turn = 1;

/*other important stuff*/
int continentSize = 0;
int enemyDifficulty = 0;

std::string troopNames[5] = { "Militia", "Guards", "Cavalry", "Knights", "Paladins" };
std::string buildingNames[6] = { "Farm", "Lumber Mill", "Quarry", "Mine", "Church" };
string provinceResourcesNames[5] = { "Food", "Wood", "Ore", "Gold", "Mana" };

const int troopCost[5] = { 5, 4, 3, 2, 1 };
int totalPlayerResources[5] = { 0,0,0,0,0 };
int initialResources[5] = { 5, 4, 3, 2, 1 };
int troopsCP[5] = { 1,2,4,8,16 };
int provinceBuildingsProductionNumbers[6] = { 5,4,3,2,1,2 };

char continueGame = 'Y';
string kingdomName = " ";
int totalMaxCommanders = 0;



int main()/*main code*/
{
    srand(time(0));
    char startOrResume = introduction();

    switch (startOrResume)
    {
    case 'R':
        resumeGame();
        break;
    case 'S':
    {
        std::cout << "What is your kingdom name? \033[31m";
        std::getline(cin, kingdomName);
        std::cout << "\n \033[0mThe kingdom of \033[31m" << kingdomName << "\033[0m has been created! " << endl;
        startGame(kingdomName);
        break;
    }
    case 'H':
    {
        Lists newLists (3);
        newLists.listOfHelp();
        break;
    }
    }
    gamePlay();
}
char introduction()/*introduce player to game synopsis*/
{
    synopsis();
		Lists newList (3);
    return newList.listOfActions();
}
void resumeGame() /*download data from previous game fix this*/
{
    string gameCode;
    std::cout << "Please enter the game code of your previous game: \033[31m";
    std::getline(cin, gameCode);
    cout << "\033[0m";
    /*use global variables to figure out code*/
}
void startGame(string kingdomName)
{
	continentSize = getInt("What continent size will you descend upon? (5, 10, 15) ", { 5, 10, 15 }, 1);
	std::cout << endl;

	pNum = getInt("How many kingdoms will you fight? (1, 2, 3) ", { 1, 2, 3 }, 1) + 1;

	totalMaxCommanders = continentSize;
	
	enemyDifficulty = getInt("What gameplay difficulty do you want (1-3): ", { 1,2,3 }, 1); 
	std::cout << "Gameplay difficulty " << enemyDifficulty << " selected. " << endl << endl;

	generateNewContinent(kingdomName);
}
void generateNewContinent(string kingdomName)
{
    createMap();
    for (int x = 0; x <= pNum; x++)
    {
        Participants newParticipant;
        participantsList.push_back(&newParticipant);
    }
}
void gamePlay()
{
	string literallyAnything = " ";
	getInt ("Enter '0' to proceed (screen will clear): \033[31m", {0}, 1);
	cout << "\033[0m";
	while (findAmountOfEnemyProvinces () > 0 && participantsList[0]->commandersNum() > 0 && continueGame == 'Y')
	{
		for (int x = 0; x < pNum; x++)
		{
			PlayerAction newPlayerAction (x);
		}
		playerAction();
		AITurn();
		turn++;
		updateprovinceResources();
	}
	endScreen();
}
void endScreen()
{
    if (findAmountOfEnemyProvinces() == 0)
    {
        std::cout << "Congratulations, you have successfully conquered your enemies and now reign as the Emporer!";
    }
    if (participantsList[0]->provincesNum() == 0)
    {
        std::cout << "Your enemies have defeated you.";
    }
    std::cout << endl;
    char playAgain = getChar("Play again? (Y/N) ", "YN", 1);
    if (playAgain == 'Y')
    {
        main();
    }
}

void playerAction()
{
	char repeatPlayerAction = 'Y';
	do
	{
			clearScreen();

			std::cout << "Turn: " << turn << endl << endl;
			std::cout << "Welcome to the Main menu " << endl;
			showMap();
			char courseOfAction = ' ';
			if (currentParticipantIndex == 0) //If the participant is the player
			{
				Lists newList (4);
				courseOfAction = newList.listOfActions();
			}
			else //If the participant is the AI
			{
					courseOfAction = randomPlayerActionChar();
			}

			std::cout << endl;
			clearScreen();

			switch (courseOfAction)
			{
			case 'B':
			{
					BuildMA newBuildMA(-1, -1);
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
					viewPlayerStats();
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
					repeatPlayerAction = 'N';
					break;
			case 'H':
			{
					listOfHelp(4);
					char whenYouDoneChar = getChar(" ", "P", 2);
					break;
			}
			case 'P':
			{
					char pauseGameQuestionChar = getChar("Pausing the game will end this session of gameplay. Proceed? (Y/N): ", "YN", 1);
					if (pauseGameQuestionChar == 'Y')
					{
							pauseGame();
							repeatPlayerAction = 'N';
							continueGame = 'N';
					}
					std::cout << "Returning to the Main menu... " << endl;
					break;
			}
			}
	} while (repeatPlayerAction == 'Y');
}

void AITurn()
{
    for (int x = 1; x <= opponentNumber; x++)
    {
        //Execute AI turn stuff here
    }
}

void viewPlayerStats()
{
    cout << "Kingdom name: " << kingdomName << endl << endl;
    int totalPlayerUnits[5];
    findTotalPlayerUnits(totalPlayerUnits);
    
    for (int x = 0; x < 5; x++){
        std::cout << "Total " << provinceResourcesNames[x] << ": " << totalPlayerResources[x] << endl;}
    
    std::cout << endl;
    
    for (int x = 0; x < 5; x++){
        std::cout << "Total " << troopNames[x] << " alive: " << totalPlayerUnits[x] << endl;}
    
    std::cout << "Your total army combat power: " << calculatePlayerValues(1) << endl;
    std::cout << "Your numnber of provinces: " << participantsList[0]->provincesNum() << "\n\n";

    switch (getChar("View all stats? (Y/N) ", "YN", 1)){
    case 'Y':
        viewAllStatsFunction();
    case 'N':
        std::cout << "Returning to menu" << endl;
        break;}
}
void pauseGame(){
    string gameCode; gameCode += continentSize;
    
    for (int x = 0; x < continentSize; x++){
        for (int y = 0; y < continentSize; y++){
            gameCode += provincesMap[x][y].getBelongsToParticipant();
        }
    }
    std::cout << "Game ended... \nHere is your game code (Copy this code and paste it when using the 'Resume Game' functionality): " << gameCode << endl << endl;
}


char randomPlayerActionChar()
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

