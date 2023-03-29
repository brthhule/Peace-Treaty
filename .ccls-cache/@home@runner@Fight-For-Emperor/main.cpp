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
#include "ConstValues.h"


//Main Actions
#include "PlayerAction.h"


#define UNIT_AMOUNT 5
#define RED "\033[31m"
#define WHITE "\033[0m"

char introduction();
void resumeGame();
void startGame();
void generateNewContinent(int pNum);
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


ConstValues CV;

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
    std::cout << "New game started...\n\n";
    // std::cout << "What is your kingdom name? " << RED;
    // std::getline(std::cin, kingdomName);
    // std::cout << WHITE << "The kingdom of " << RED << kingdomName << WHITE << " has been created! \n\n";
    startGame();
    break;
  }
  case 'H':
  {
      Lists newLists (3);
      newLists.listOfHelp();
      break;
  }
  }

  // for (Participants thingy: participantsList)
  //   std::cout << "Participant index: " << thingy.getParticipantIndex() << std::endl;
  
  std::string literallyAnything = " ";
  std::cout << "Enter anything to proceed to the game: " << RED;
	getline(std::cin, literallyAnything);
  std::cout << WHITE;
	OF.clearScreen();
  
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
void startGame()
{
	std::string text = "What continent size do you want to play on?\n- 5 (Recommended for mobile devices)\n- 10 (Medium-sized map)\n- 15 (Full experienced, recommended for a monitor)\nEnter the number here: ";
	//"What continent size do you want to play on? (5, 10, 15) "
  std::string input = OF.getInput(text, {"number", "5", "10", "15" }, false);
	continentSize = stoi(input);
  std::cout << "Continent size " << RED << continentSize << WHITE << " created..\n\n";

	int pNum = stoi(OF.getInput("How many AI kingdoms will you fight? (1, 2, 3) ", {"number", "1", "2", "3" }, false));
  std::cout << RED << pNum << WHITE << " opponent kingdoms generated... \n\n";
	totalMaxCommanders = continentSize;
	
	enemyDifficulty = stoi(OF.getInput("What gameplay difficulty do you want (1-3): ", {"number","1","2","3" }, false)); 
	std::cout << "Gameplay difficulty " << RED << enemyDifficulty << WHITE << " selected. \n\n";

	generateNewContinent(pNum);
}
void generateNewContinent(int pNum)
{
	createMap();
  std::vector<std::string> howManyPlayers = {"number"};
  for (int x = 1; x <= 3; x++)
    howManyPlayers.push_back(std::to_string(x));
  
	int players = stoi(OF.getInput("How many human players are there (1/2/3; 1 is recommended for single player experience)): ", howManyPlayers, false));
  std::cout << RED << players << WHITE << " players initialized...\n\n";
  pNum += players;
	
  
  for (int x = 0; x < pNum; x++)
	{
		Participants newParticipant (x);
		//Create x + 1 many players
		if (x < players)
    {
      //std::cout << "New participant created... \n";
      newParticipant.createAsPlayer(true);
    }
    //Everyone else is enemy AI
		else
			newParticipant.createAsPlayer (false);

  //   std::cout << "Participant index: " << newParticipant.getParticipantIndex() << std::endl;
		participantsList.push_back(newParticipant);
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

void endScreen()
{
	for (int x = 0; x <= participantsList.size(); x++)
	{
		if (participantsList[x].isAlive())
			std::cout << "Congratulatios to player " << participantsList[x].getKingdomName() << " for winning. You have successfully conquered your enemies and now reign as the Emperor! \n";
	}
	char playAgain = OF.getInput("Play again? (Y/N) ", {"letter", "Y", "N"}, false).at(0);
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

void gamePlay()
{
  bool gameEnd = false;
	
  //Iterate through partiicpants by reference
  for (Participants &newParticipant: participantsList)
  {		
    if (newParticipant.isAlive())
    {
      PlayerAction newPlayerAction (&newParticipant);
      newPlayerAction.initialDecision();  
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

  //Check game end
  //If there are more than one players, keep playing
  int participantsAlive = 0;
  for (Participants newParticipant: participantsList)
    if (newParticipant.isAlive() == true)
      participantsAlive ++;

  if (participantsAlive > 1)
    gamePlay ();
  
	endScreen();
}

