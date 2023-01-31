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
void endScreen();


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
	int players = getInt("How many human players are there (including yourself, up to 10)", {1,2,3,4,5,6,7,8,9,10}, 1);
	for (int x = 0; x <= pNum; x++)
	{
		Participants newParticipant;
		
		if (x < players)
			newParticipant.createAsPlayer(true);
		else
			newParticipant.createAsPlayer (false);
		
		participantsList.push_back(&newParticipant);
	}
}
void gamePlay()
{
	string literallyAnything = " ";
	getInt ("Enter '0' to proceed (screen will clear): \033[31m", {0}, 1);
	cout << "\033[0m";
	while (participantsList[0]->isAlive())
	{
		for (int x = 0; x < pNum; x++)
		{
			PlayerAction newPlayerAction (participantsList[x]);
			int nextPlayer = newPlayerAction.initialDecision();
			if (nextPlayer == -2)
			{
				main();
			}
		}
		turn++;
		updateprovinceResources();
	}
	endScreen();
}

void endScreen()
{
	for (int x = 0; x <= pNum; x++)
	{
		if (participantsList[x]->isAlive())
			std::cout << "Congratulatios to kingdom " << participantsList[x]->getKingdomName() << " for winning. You have successfully conquered your enemies and now reign as the Emperor! \n";
	}
	char playAgain = getChar("Play again? (Y/N) ", "YN", 1);
	if (playAgain == 'Y')
	{
			main();
	}
}









