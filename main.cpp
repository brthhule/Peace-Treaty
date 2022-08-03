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
#include <stdlib.h>
#include <iomanip>

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

using namespace std;

/*Beginning functions*/
char introduction(char startOrResume);
void resumeGame();
void startGame();
void generateNewContinent();
void gamePlay();
void playerAction(int turn);
void endScreen();
void testingSkip();
void pauseGame();
/*scouting functions*/


/*view player stats*/
void viewPlayerStats();
void viewAllStatsFunction();
/*map action functions*/
void viewPlayerMap();
void selectUnitOriginal(int xCoordinate, int yCoordinate);
void selectPlayerProvince(int xCoordinate, int yCoordinate);
void playerUnitAction(int xCoordinate, int yCoordinate);
void selectEnemyAction(int xCoordinate, int yCoordinate);
void selectEnemyProvince(int xCoordinate, int yCoordinate);
void scoutLogFunction(int xCoordinate, int yCoordinate);
void provinceReportLog(char whatReportChar, int xCoordinate, int yCoordinate);
/*Enemy turn*/
void AITurn();
int opponentNumber = 0;
/*Miscellaneous functions*/

void initializeValues();
void addNewCommander(); /*Fill vector with commander objects*/
int findProvinceIndex(int xCoordinate, int yCoordinate);

int currentParticipantIndex = 0;
int* pAParticipantIndex = &currentParticipantIndex;
/*map stuff & coordinates*/
//char *mapCharacters[15][15];
vector <vector <Provinces>> provincesMap;
vector <vector <CommanderProfile>> allCommanders;
vector <Participants> participantsList;
int participantCoordinates[4][2] = { 0 }; /*first number is for the participant (0 = player; 1,2,3 = AI), second number is which coordinate
(0 = x coordinate, 1 = y coordinate) these coordinates are the computer coordinates, not player coordinates
*/
int* playerCapitalProvinceX = &participantCoordinates[0][0];
int* playerCapitalProvinceY = &participantCoordinates[0][1];
int turn = 1;
/*other important stuff*/
int continentSize = 0;
int enemyDifficulty = 0;
int playerProvinces = 0;
int enemyProvinces = 0;
/*building stuff*/
int provinceBuildingsProductionNumbers[6] = { 5,4,3,2,1,2 };
/*Army stuff*/
int troopsCP[5] = { 1,2,4,8,16 };
std::string troopNames[5] = { "Militia", "Guards", "Cavalry", "Knights", "Paladins" };
std::string buildingNames[6] = { "Farm", "Lumber Mill", "Quarry", "Mine", "Church" };

int scoutLogTurnLevel[15][15][2] = { 0 };
/*Army commander stuff*/
int maxAmountOfCommanders = 0;
/*other*/

char mapMoveUnit[15][15] = { 'N' };
/*train troops*/
const int troopCost[5] = { 5, 4, 3, 2, 1 };
int totalPlayerResources[5] = { 0,0,0,0,0 };
/*stats*/
int playerTroopsLost[5] = { 0,0,0,0,0 };
int totalPlayerUnits[5] = { 0,0,0,0,0 }; /*0) Militia, 1) Guards, 2) Cavalry, 3) Knights, 4) Paladins*/
/*Resource stuff*/
int initialResources[5] = { 5, 4, 3, 2, 1 };
string provinceResourcesNames[5] = { "Food", "Wood", "Ore", "Gold", "Mana" };
//int provinceResources[15][15][5] = { 0 }; /*food, wood, ore, gold, mana*/



int main()/*main code*/
{
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
    enemyProvinces = opponentNumber;
    playerProvinces = 1;

    maxAmountOfCommanders = continentSize;
    
    enemyDifficulty = getInt("What gameplay difficulty do you want (1-3): ", { 1,2,3 }, 1); 
    std::cout << "Gameplay difficulty " << enemyDifficulty << " selected. " << endl << endl;

    generateNewContinent();
}
void generateNewContinent()
{
    initializeValues();
    char repeatMap = 'Y';
    int xCoordinate = 0;
    int yCoordinate = 0;

    for (int v = 0; v < opponentNumber; v++)
    {
        Participants newParticipant;
        participantsList.push_back(newParticipant);
    }
    cout << "Create capitals" << endl;
    showMap();
    /*For each participant, generate random x and y values, see if the province associated with these values (coordinates) is empty. If it's empty, change the province identifier and add it to a partipant's
    list of provinces. If it's not empty, repeatMap is 'Y' and the process repeats*/
    for (int participantIndexTemp = 0; participantIndexTemp <= opponentNumber; participantIndexTemp++)
    {
        do
        {
            repeatMap = 'N';
            srand(static_cast<int>(time(0)));
            xCoordinate = rand() % (continentSize - 1);
            yCoordinate = rand() % (continentSize - 1);

            cout << "Coordinates have been created" << endl;
            if (provincesMap[xCoordinate][yCoordinate].getBelongsToParticipant() == -1)
            {
                //Cout can choose this province to be a capital
                provincesMap[xCoordinate][yCoordinate].changeBelongsToParticipant(participantIndexTemp);
                provincesMap[xCoordinate][yCoordinate].provinceIsACapital();
                participantsList[participantIndexTemp].addProvince(xCoordinate, yCoordinate);
            }
            else
            {
                repeatMap = 'N';
            }
        } while (repeatMap == 'Y');
    }
    cout << "Create commanders" << endl;
    //create initial commander object for each participant, add it to that participant's list of commanders
    for (int participantIndexTemp = 0; participantIndexTemp <= opponentNumber; participantIndexTemp++)
    {
        Participants* newParticipant = &participantsList[participantIndexTemp];
        CommanderProfile newCommander(1, getNewName(), 1);
        newCommander.changeCoordinates(newParticipant->getCapitalCoordinate('X'), newParticipant->getCapitalCoordinate('Y'));
        allCommanders[currentParticipantIndex].push_back(newCommander);
    }

    cout << "Initialize resources " << endl;
    //Add resources to enemy participants/players based on difficulty
    for (int x = 1; x <= opponentNumber; x++)
    {
        cout << "X: " << x << endl;
        for (int y = 0; y < 5; y++)
        {
            cout << "Y: " << y << endl;
            //Select a province from a participant, select resource index y and add amount of resources (last parameter)
            //[x][0] is the x coordinate, [x][1] is the y coordinate
            int xCoordinate = participantsList[x].listOfProvincesX[0];
            int yCoordinate = participantsList[x].listOfProvincesY[0];
            provincesMap[xCoordinate][yCoordinate].addResources(y, initialResources[y] * enemyDifficulty);
        }
    }
}
void gamePlay()
{
    while (enemyProvinces > 0 && playerProvinces > 0)
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
    if (enemyProvinces == 0)
    {
        std::cout << "Congratulations, you have successfully conquered your enemies and now reign as the Emporer!";
    }
    if (playerProvinces == 0)
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
            viewPlayerMap();
            break;
        case 'A':
        {
            ArmyDeploymentMA newArmyDeploymentMA(*playerCapitalProvinceX, *playerCapitalProvinceY);
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
                playerProvinces = -1;
            }
            std::cout << "Returning to the Main menu... " << endl;
            break;
        }
        }
    } while (repeatPlayerAction == 'Y');
}




void viewPlayerMap()
{
    int xCoordinate;
    int yCoordinate;
    char whatToDo = ' ';
    showMap();
    char repeatViewPlayerMap = 'Y';

    do
    {
        std::cout << "Welcome to the View Map action menu" << endl;
        whatToDo = listOfActions(8);

        switch (whatToDo)
        {
        case 'P':
        {
            vector <int> XYCoordinates = getCoordinates(1);
            xCoordinate = XYCoordinates[0];
            yCoordinate = XYCoordinates[1];
            if (xCoordinate != -1 && yCoordinate != -1)
            {
                selectUnitOriginal(xCoordinate, yCoordinate);
            }
            break;
        }
        case 'H':
            playerMapHelp();
            break;
        default:
            std::cout << "Returning to the previous menu." << endl;
            repeatViewPlayerMap = 'N';
            std::cout << endl;
            break;
        }
    } while (repeatViewPlayerMap == 'Y');
}
void selectUnitOriginal(int xCoordinate, int yCoordinate)
{
    if (provincesMap[xCoordinate][yCoordinate].getBelongsToParticipant() == currentParticipantIndex)//If belongs to participant
    {
        selectPlayerProvince(xCoordinate, yCoordinate);
    }
    else if (provincesMap[xCoordinate][yCoordinate].getBelongsToParticipant() == -1)//If empty province
    {
        if (provincesMap[xCoordinate][yCoordinate].commandersPresentIndex.size() > 0)//If there are more than 0 commnaders
        {
            if (allCommanders[currentParticipantIndex][provincesMap[xCoordinate][yCoordinate].returnCommanderIndex(0)].returnBelongsToParticipant() == currentParticipantIndex) //If the army here belongs to the participant
            {
                playerUnitAction(xCoordinate, yCoordinate);
            }
            else
            {
                selectEnemyAction(xCoordinate, yCoordinate);
            }
        }
    }
    else //If enemy province
    {
        selectEnemyProvince(xCoordinate, yCoordinate);
    }
}
void selectPlayerProvince(int xCoordinate, int yCoordinate)
{
    if (participantsList[provincesMap[xCoordinate][yCoordinate].getBelongsToParticipant()].findProvinceIndexWithCoordinates(xCoordinate, yCoordinate)
        == 0)
    { 
        std::cout << "This is your capital province ";
    }
    else
    {
        std::cout << "This is one of your provinces ";;
    }
    std::cout << endl << endl;

    char selectPlayerCapitalAction = listOfActions(9);

    switch (selectPlayerCapitalAction)
    {
    case 'B':
    {
        BuildMA newBuildMA(xCoordinate, yCoordinate);
        newBuildMA.playerBuildFunction();
        break;
    }
    case 'T':
    {
        TrainMA newTrainMA(xCoordinate, yCoordinate);
        newTrainMA.findProvinceCoordinates();
        break;
    }
    case 'M':
        std::cout << "Returning to the map..." << endl;
        std::cout << endl;
        break;
    }
}
void selectEnemyProvince(int xCoordinate, int yCoordinate)
{

    if (participantsList[provincesMap[xCoordinate][yCoordinate].getBelongsToParticipant()].findProvinceIndexWithCoordinates(xCoordinate, yCoordinate)
        == 0)
    {
        std::cout << "This is an enemy capital province ";
    }
    else
    {
        std::cout << "This is one of the enemy's provicnes" << endl;
    }
    std::cout << endl << endl;

    std::cout << "Welcome to the Enemy Provinces Action Selection menu " << endl;
    char selectUnitEnemyProvinceChar = listOfActions(10);

    switch (selectUnitEnemyProvinceChar)
    {
    case 'A':
    {
        AttackMA newAttackMA(0, 0, xCoordinate, yCoordinate, -1, -1);
        newAttackMA.playerAttack();
        break;
    }
    case 'S':
    {
        ScoutMA newScout(xCoordinate, yCoordinate);
        newScout.selectTargetToScout();
        break;
    }
    case 'V':
    {
        if (scoutLogTurnLevel[xCoordinate][yCoordinate][0] != -1)
        {
            if (getChar("View scout log for this province? (Y/N) ", "YN", 1) == 'Y')/*Ask user if they want to view scout log, get char, go to scoutLogFunction if 'Y'*/
            {
                scoutLogFunction(xCoordinate, yCoordinate);
            }
        }
        break;
    }
    case 'M':
        std::cout << "Returning to the menu... " << endl;
        break;
    }

}
void scoutLogFunction(int xCoordinate, int yCoordinate)
{
    char repeatScoutLog = 'N';
    char whatReportChar;

    std::cout << "Turn of scout report: " << scoutLogTurnLevel[xCoordinate][yCoordinate][0] << "; Level of report: " << scoutLogTurnLevel[xCoordinate][yCoordinate][1] << endl << endl;
    do
    {
        whatReportChar = listOfActions(11);
        provinceReportLog(whatReportChar, xCoordinate, yCoordinate);

    } while (repeatScoutLog == 'Y');
}
void provinceReportLog(char whatReportChar, int xCoordinate, int yCoordinate)
{
    int totalGarrisonedCP = 0;
    switch (whatReportChar)
    {
    case 'G':
    {
        std::cout << "Garrisoned troops: " << endl;
        for (int x = 0; x < 5; x++)
        {
            std::cout << "-" << troopNames[x] << ": " << provincesMap[xCoordinate][yCoordinate].getTroopsPresent(x) << endl;
            totalGarrisonedCP += (provincesMap[xCoordinate][yCoordinate].getTroopsPresent(x) * troopsCP[x]);
        }
        std::cout << "Total Garrison Combat Power: " << totalGarrisonedCP << endl << endl;
        break;
    }
    case 'R':
        provincesMap[xCoordinate][yCoordinate].printResources();
        break;
    case 'B':
        provincesMap[xCoordinate][yCoordinate].printBuildingStats();
        break;
    case 'M':
        break;
    }
}
void playerUnitAction(int xCoordinate, int yCoordinate)
{
    std::cout << "This is one of your armies " << endl;
    Participants* newParticipant = &participantsList[*pAParticipantIndex];

    char repeatPlayerUnitAction = 'Y';
    do
    {
        char playerUnitActionChar = listOfActions(2);
        switch (playerUnitActionChar)
        {
        case 'P':
        {
            //find index of commander unit
            int commanderIndex = 0;
            for (int x = 0; x < newParticipant->howManyCommanders(); x++)
            {
                if (newParticipant->listOfProvincesX[x] == xCoordinate && newParticipant->listOfProvincesY[x] == yCoordinate)
                {
                    commanderIndex = x;
                    x = newParticipant->howManyCommanders();
                }
            }
            if (allCommanders[currentParticipantIndex][commanderIndex].hasCommanderMoved() == 'N')
            {
                allCommanders[currentParticipantIndex][commanderIndex].moveUnit(participantCoordinates[0][0], participantCoordinates[0][1]);/*fix this*/
            }
            else
                std::cout << "This unit has already moved this turn... returning to the View Map action menu " << endl << endl;
            repeatPlayerUnitAction = 'N';
            break;
        }
        case 'H':
            playerUnitActionHelp();
            break;
        case 'M':
            std::cout << "Returning to menu... " << endl;
            repeatPlayerUnitAction = 'N';
            break;
        }
    } while (repeatPlayerUnitAction == 'Y');
}
void selectEnemyAction(int xCoordinate, int yCoordinate)/*finish this*/
{
    std::cout << "This is an enmy army. " << endl;
    char repeatSelectEnemyAction = 'Y';
    do
    {
        listOfActions(1);
    } while (repeatSelectEnemyAction == 'Y');
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
    std::cout << "Your numnber of provinces: " << playerProvinces << endl << endl;

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
    enemyProvinces = 1;
    playerProvinces = 1;

    continentSize = 5;
    opponentNumber = 2;
    enemyDifficulty = 2;
    generateNewContinent();
}

void initializeValues()
{
    /*Basically create the map-- make each province an object of Provinces*/
    for (int x = 0; x < continentSize; x++)
    {
        vector <Provinces> vectorThingy;
        provincesMap.push_back(vectorThingy);
        for (int y = 0; y < continentSize; y++)
        {
            Provinces newProvince(x, y, -1);
            provincesMap[x].push_back(newProvince);
        }

    }

    /*Initialize scoutLogTurnLevel such that there are no values in them at first*/
    for (int a = 0; a < continentSize; a++)
    {
        for (int b = 0; b < continentSize; b++)
        {
            for (int d = 0; d <= 1; d++)
            {
                scoutLogTurnLevel[a][b][d] = -1;
            }
        }
    }
}

void addNewCommander()
{
    //Creates new participant
    Participants* newParticipant = &participantsList[currentParticipantIndex];

    CommanderProfile newCommander(1, getNewName(), 1);
    newCommander.changeCoordinates(newParticipant->getCapitalCoordinate('X'), newParticipant->getCapitalCoordinate('Y'));
    allCommanders[currentParticipantIndex].push_back(newCommander);
}


int findProvinceIndex(int xCoordinate, int yCoordinate)
{
    Participants* newParticipant;
    newParticipant = &participantsList[*pAParticipantIndex];
    //For each province the participant has
    for (int x = 0; x < newParticipant->howManyProvinces(); x++)
    {
        //If the coordinates passed to the function are equal to a province's coordinates from the list
        if (xCoordinate == newParticipant->listOfProvincesX[x] &&
            yCoordinate == newParticipant->listOfProvincesY[x])
        {
            //This is the province's index in listOfProvinces
            return x;
        }
    }
    return -1;//In case something goes wrong
}

