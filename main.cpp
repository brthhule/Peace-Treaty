#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <string.h>
#include<stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <vector>
#include <math.h>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <time.h>

#include "AllUnits.h"
#include "CommanderProfile.h"
#include "otherFunctions.h"
#include "TrainMA.h"
#include "Provinces.h"
#include "textFunctions.h"
#include "Participants.h"

#include "BuildMA.h"
#include "ArmyDeploymentMA.h"
#include "AttackMA.h"
#include "ScoutMA.h"
#include "MapMA.h"

using namespace std;

char introduction(char startOrResume);
void resumeGame();
void startGame();
void generateNewContinent();
void gamePlay();
void playerAction(int turn);
void endScreen();
void testingSkip();
void pauseGame();

void viewPlayerStats();


/*Enemy turn*/
void AITurn();
int opponentNumber = 0;

/*Miscellaneous*/
int currentParticipantIndex = 0;
vector <vector <Provinces>> provincesMap;
vector <vector <CommanderProfile>> allCommanders;
vector <Participants> participantsList;
int turn = 1;

/*other important stuff*/
int continentSize = 0;
int enemyDifficulty = 0;

/*building stuff*/
int provinceBuildingsProductionNumbers[6] = { 5,4,3,2,1,2 };

/*Army stuff*/
int troopsCP[5] = { 1,2,4,8,16 };
std::string troopNames[5] = { "Militia", "Guards", "Cavalry", "Knights", "Paladins" };
std::string buildingNames[6] = { "Farm", "Lumber Mill", "Quarry", "Mine", "Church" };

/*Army commander stuff*/
int maxAmountOfCommanders = 0;

/*train troops*/
const int troopCost[5] = { 5, 4, 3, 2, 1 };
int totalPlayerResources[5] = { 0,0,0,0,0 };

/*Resource stuff*/
int initialResources[5] = { 5, 4, 3, 2, 1 };
string provinceResourcesNames[5] = { "Food", "Wood", "Ore", "Gold", "Mana" };
char continueGame = 'Y';



int main()/*main code*/
{
    srand(time(0));
    string kingdomName = " ";
    char startOrResume = ' ';
    startOrResume = introduction(startOrResume);

    switch (startOrResume)
    {
    case 'R':
        resumeGame();
        break;
    case 'S':
        std::cout << "What is your kingdom name? ";
        std::getline(cin, kingdomName);
        std::cout << endl;
        std::cout << "The kingdom of " << kingdomName << " has been created! " << endl;
        startGame();
        break;
    case '1':
        testingSkip();
        break;
    }
    gamePlay();
}
char introduction(char startOrResume)/*introduce player to game synopsis*/
{
    synopsis();
    return listOfActions(3);
}
void resumeGame() /*download data from previous game fix this*/
{
    string gameCode;
    std::cout << "Please enter the game code of your previous game: ";
    std::getline(cin, gameCode);
    /*use global variables to figure out code*/
}
void startGame()
{
    std::string continentSizeString;
    vector<int> continentSizeAVTwo = { 5, 10, 15 };
    std::string opponentNumberString;
    string userInput = " ";

    //vector <int> continentSizeList = { 5, 10, 15 };
    continentSize = getInt("What continent size will you descend upon? (5, 10, 15) ", { 5, 10, 15 }, 1);
    std::cout << endl;

    opponentNumber = getInt("How many kingdoms will you fight? (1, 2, 3) ", { 1, 2, 3 }, 1);

    maxAmountOfCommanders = continentSize;
    
    enemyDifficulty = getInt("What gameplay difficulty do you want (1-3): ", { 1,2,3 }, 1); 
    std::cout << "Gameplay difficulty " << enemyDifficulty << " selected. " << endl << endl;

    generateNewContinent();
}
void generateNewContinent()
{
    initializeValues();
    char repeatMap = 'N';

    for (int v = 0; v <= opponentNumber; v++)
    {
        Participants newParticipant (v);
        participantsList.push_back(newParticipant);
    }
    /*For each participant, generate random x and y values, see if the province associated with these values (coordinates) is empty. If it's empty, change the province identifier and add it to a partipant's
    list of provinces. If it's not empty, repeatMap is 'Y' and the process repeats*/
    for (int participantIndexTemp = 0; participantIndexTemp <= opponentNumber; participantIndexTemp++)
    {
        do
        {
            repeatMap = 'N';
            int xCoordinate = getRandomCoordinate();
            int yCoordinate = getRandomCoordinate();
            if (provincesMap[xCoordinate][yCoordinate].getBelongsToParticipant() == -1)
            {
                //Cout can choose this province to be a capital
                provincesMap[xCoordinate][yCoordinate].changeBelongsToParticipant(participantIndexTemp);
                provincesMap[xCoordinate][yCoordinate].provinceIsACapital();
                participantsList[participantIndexTemp].addProvince(xCoordinate, yCoordinate);
                participantsList[participantIndexTemp].updateCapitalCoordinates(xCoordinate, yCoordinate);
            }
            else
            {
                repeatMap = 'Y';
            }
        } while (repeatMap == 'Y');
    }

    //cout << "Create commanders 1" << endl;
    //create initial commander object for each participant, add it to that participant's list of commanders
    for (int x = 0; x <= opponentNumber; x++)
    {
        vector <CommanderProfile> listOfCommandersList;
        allCommanders.push_back(listOfCommandersList);
    }
    //cout << "Create commanders 2" << endl;
    for (int participantIndexTemp = 0; participantIndexTemp <= opponentNumber; participantIndexTemp++)
    {
        CommanderProfile newCommander(1, getNewName(), 1);
        allCommanders[participantIndexTemp].push_back(newCommander);
        allCommanders[participantIndexTemp][0].changeCoordinates(participantsList[participantIndexTemp].getCapitalCoordinate('X'), 
            participantsList[participantIndexTemp].getCapitalCoordinate('Y'));
    }


    int xCoordinate = 0;
    int yCoordinate = 0;
    //cout << "Initialize resources " << endl;
    //Add resources to enemy participants/players based on difficulty
    for (int participantIndexTemp = 1; participantIndexTemp <= opponentNumber; participantIndexTemp++)
    {
        //Select a province from a participant, select resource index y and add amount of resources (last parameter)
//[x][0] is the x coordinate, [x][1] is the y coordinate
        xCoordinate = participantsList[participantIndexTemp].listOfProvincesX[0];
        yCoordinate = participantsList[participantIndexTemp].listOfProvincesY[0];

        for (int resourceIndex = 0; resourceIndex < 5; resourceIndex++)
        {
            provincesMap[xCoordinate][yCoordinate].addResources(resourceIndex, initialResources[resourceIndex] * enemyDifficulty);
        }
    }
}
void gamePlay()
{
    //cout << "Start gameplay" << endl;
    while (findAmountOfEnemyProvinces () > 0 && participantsList[0].howManyCommanders() > 0 && continueGame == 'Y')
    {
        playerAction(turn);
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
    if (participantsList[0].howManyProvinces() == 0)
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

void playerAction(int turn)
{
    char repeatPlayerAction = 'Y';
    do
    {
        std::cout << "Clearing screen. " << endl;
        chrono::seconds dura(1);
        this_thread::sleep_for(dura);
        system("cls"); /*Windows only*/
        //system("clear"); /*Non-Windows*/

        std::cout << "Turn: " << turn << endl << endl;
        std::cout << "Welcome to the Main menu " << endl;
        char courseOfAction = listOfActions(4);
        std::cout << endl;

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
        case 'V':
            viewPlayerStats();
            break;
        case 'M':
        {
            MapMA newMap;
            newMap.viewPlayerMap();
            break;
        }
        case 'A':
        {
            ArmyDeploymentMA newArmyDeploymentMA;
            newArmyDeploymentMA.armyDeploymentMF();
            break;
        }
        case 'G':
            repeatPlayerAction = 'N';
            break;
        case 'H':
        {
            playerActionHelp();
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
    int totalPlayerUnits[5];
    findTotalPlayerUnits(totalPlayerUnits);
    for (int x = 0; x < 5; x++)
    {
        std::cout << "Total " << provinceResourcesNames[x] << ": " << totalPlayerResources[x] << endl;
    }
    std::cout << endl;
    for (int x = 0; x < 5; x++)
    {
        std::cout << "Total " << troopNames[x] << " alive: " << totalPlayerUnits[x] << endl;
    }
    int playerCP = calculatePlayerValues(1);
    std::cout << "Your total army combat power: " << playerCP << endl;
    std::cout << endl;
    std::cout << "Your numnber of provinces: " << participantsList[0].howManyProvinces() << endl << endl;

    switch (getChar("View all stats? (Y/N) ", "YN", 1))
    {
    case 'Y':
        viewAllStatsFunction();
    case 'N':
        std::cout << "Returning to menu" << endl;
        break;
    }
}
void pauseGame()
{
    string gameCode;
    gameCode += continentSize;
    for (int x = 0; x < continentSize; x++)
    {
        for (int y = 0; y < continentSize; y++)
        {
            gameCode += provincesMap[x][y].getBelongsToParticipant();
        }
    }
    std::cout << "Game ended... " << endl;
    std::cout << "Here is your game code (Copy this code and paste it when using the 'Resume Game' functionality): " << gameCode << endl << endl;
}


void testingSkip()
{
    continentSize = 5;
    opponentNumber = 2;
    enemyDifficulty = 2;
    generateNewContinent();
}