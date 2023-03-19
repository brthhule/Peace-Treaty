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
#include "Provinces.h"
#include "Participants.h"
#include "CommanderProfile.h"


//Miscellaneous
#include "OtherFunctions.h"
#include "Lists.h"


//Main Actions
#include "PlayerAction.h"

#define UNIT_AMOUNT 5

char introduction();
void resumeGame();
void startGame(std::string kingdomName);
void generateNewContinent(std::string kingdomName, int pNum);
void gamePlay();
void endScreen();
void updateProvinceResources();
void createMap();

void AITurn();
/*Miscellaneous*/
std::vector <std::vector <Provinces>> provincesMap;
std::vector <Participants> participantsList;
OtherFunctions OF;
int turn = 1;

/*other important stuff*/
int continentSize = 0;
int enemyDifficulty = 0;

const std::array<std::string, UNIT_AMOUNT> TROOP_NAMES = { "Militia", "Guards", "Cavalry", "Knights", "Paladins" };
const std::array<std::string, UNIT_AMOUNT> RESOURCE_BUILDING_NAMES = { "Farm", "Lumber Mill", "Quarry", "Mine", "Church" };
const std::array<std::string, UNIT_AMOUNT> RESOURCE_NAMES = { "Food", "Wood", "Ore", "Gold", "Mana" };

const std::array<int, UNIT_AMOUNT> TROOPS_COST = { 5, 4, 3, 2, 1 };
const std::array<int, UNIT_AMOUNT> INITIAL_VALUES = { 5, 4, 3, 2, 1 };
const std::array<int, UNIT_AMOUNT> TROOPS_CP = { 1,2,4,8,16 };
const std::array<int, UNIT_AMOUNT> RESOURCE_PRODUCTION = { 5,4,3,2,1};
const int BARRACKS_PRODUCTION = 2;

std::string kingdomName = " ";
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
        std::getline(std::cin, kingdomName);
        std::cout << "\n \033[0mThe kingdom of \033[31m" << kingdomName << "\033[0m has been created! \n";
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
    std::string gameCode;
    std::cout << "Please enter the game code of your previous game: \033[31m";
    std::getline(std::cin, gameCode);
    std::cout << "\033[0m";
    /*use global variables to figure out code*/
}
void startGame(std::string kingdomName)
{
	continentSize = stoi(OF.getInput("What continent size will you descend upon? (5, 10, 15) ", { "5", "10", "15" }, 1));
	std::cout << std::endl;

	int pNum = stoi(OF.getInput("How many kingdoms will you fight? (1, 2, 3) ", { "1", "2", "3" }, 1)) + 1;

	totalMaxCommanders = continentSize;
	
	enemyDifficulty = stoi(OF.getInput("What gameplay difficulty do you want (1-3): ", { "1","2","3" }, 1)); 
	std::cout << "Gameplay difficulty " << enemyDifficulty << " selected. \n\n";

	generateNewContinent(kingdomName, pNum);
}
void generateNewContinent(std::string kingdomName, int pNum)
{
	createMap();
	int players = stoi(OF.getInput("How many human players are there (including yourself, up to 10)", {"1","2","3","4","5","6","7","8","9","10"}, 1));
	for (int x = 0; x <= pNum; x++)
	{
		Participants newParticipant;
		
		if (x < players)
			newParticipant.createAsPlayer(true);
		else
			newParticipant.createAsPlayer (false);
		
		participantsList.push_back(newParticipant);
	}
}
void gamePlay()
{
	std::string literallyAnything = " ";
	stoi(OF.getInput ("Enter '0' to proceed (screen will clear): \033[31m", {"0"}, 1));
	std::cout << "\033[0m";
	while (participantsList[0].isAlive())
	{
		for (int x = 0; x < participantsList.size(); x++)
		{
			PlayerAction newPlayerAction (&participantsList[x]);
			int nextPlayer = newPlayerAction.initialDecision();
			if (nextPlayer == -2)
			{
				main();
			}
		}
		turn++;
		for (int x = 0; x < provincesMap.size(); x++)
		{
			for (int y = 0; y < provincesMap[0].size(); y++)
			{
				provincesMap[x][y].updateProvinceResources();
			}
		}
	}
	endScreen();
}

void endScreen()
{
	for (int x = 0; x <= participantsList.size(); x++)
	{
		if (participantsList[x].isAlive())
			std::cout << "Congratulatios to kingdom " << participantsList[x].getKingdomName() << " for winning. You have successfully conquered your enemies and now reign as the Emperor! \n";
	}
	char playAgain = OF.getInput("Play again? (Y/N) ", {"Y", "N"}, 1).at(0);
	if (playAgain == 'Y')
	{
			main();
	}
}

void updateprovinceResources() {
  for (int x = 0; x < continentSize; x++) {
    for (int y = 0; y < continentSize; y++) {
      provincesMap[x][y].updateBuildingsProduction();
      provincesMap[x][y].updateProvinceResources();
    }
  }
}

void createMap() {
  /*Basically create the map-- make each province an object of Provinces*/
  for (int x = 0; x < continentSize; x++) {
    std::vector<Provinces> vectorThingy;
    provincesMap.push_back(vectorThingy);
    for (int y = 0; y < continentSize; y++) {
      Provinces newProvince(x, y, -1);
      provincesMap[x].push_back(newProvince);
    }
  }
}

