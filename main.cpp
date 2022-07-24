/*7/23/22 @ 10:10 pm*/
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
//#include <windows.h> //WO
#include <stdlib.h>
/*#include <iomanip>
*/

#include "AllUnits.h"
#include "CommanderProfile.h"
#include "otherFunctions.h"
#include "TrainMA.h"
#include "Provinces.h"
#include "textFunctions.h"

#include "BuildMA.h"
#include "ArmyDeploymentMA.h"
#include "AttackMA.h"

using namespace std;

/*Beginning functions*/
char introduction(char startOrResume);
void resumeGame();
void startGame();
void generateNewContinent(int opponentNumber);
void gamePlay();
void playerAction(int turn);
void endScreen();
void testingSkip();
void pauseGame();
/*scouting functions*/
void playerScout(int xCoordinate, int yCoordinate);
vector <int> showUnitsCanScout(vector <Provinces> &provincesCanSelect);
int findUnitLevel(int xCoordinate, int yCoordinate, char identifier);
void scoutLogCalculationsCommander(int whichParticipant, int commanderIndex, int accuracyy); /*Fix this--- need to write this*/
void scoutLogCalculationsProvince(int xCoordinate, int yCoordinate, int accuracy);
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
void addNewCommander(vector <CommanderProfile>& playerCommandersList); /*Fill vector with commander objects*/

/*map stuff & coordinates*/
//char *mapCharacters[15][15];
vector <Provinces> provincesCanSelect;
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
string troopNames[5] = { "Militia", "Guards", "Cavalry", "Knights", "Paladins" };
string buildingNames[6] = { "Farm", "Lumber Mill", "Quarry", "Mine", "Church" };

vector <vector <CommanderProfile>> commandersList;
vector<vector<Provinces>> provincesList;
int scoutLogTurnLevel[15][15][2] = { 0 };
/*Army commander stuff*/
int maxAmountOfCommanders = 0;
char confirmOpponents[3] = { 'N', 'N', 'N' };
vector <vector <char>> commanderIdentifiers;
vector <vector <char>> commanderIdentifiersList;
/*other*/
char generalCommanderIdentifiers [26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char mapMoveUnit[15][15] = { 'N' };
/*train troops*/
const int troopCost[5] = { 5, 4, 3, 2, 1 };
int provinceGarrisons[15][15][5] = { 0,0,0,0,0 };
int totalPlayerResources[5] = { 0,0,0,0,0 };
/*stats*/
int totalTroops[5] = { 0,0,0,0,0 };
int playerTroopsLost[5] = { 0,0,0,0,0 };
int totalTroopsLost = 0;
int playerCP = 0;
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
    continentSize = 0;
    string continentSizeString;
    vector<int> continentSizeAVTwo = { 5, 10, 15 };
    string opponentNumberString;
    vector<int> opponentNumberAVTwo = { 1, 2, 3 };
    int opponentNumber = 0;

    std::cout << endl << "What continent size will you descend upon? (5, 10, 15) ";
    std::getline(cin, continentSizeString);
    continentSize = checkInt(continentSizeAVTwo, continentSizeString);
    std::cout << endl;


    std::cout << "How many kingdoms will you fight? (1, 2, 3) ";
    std::getline(cin, opponentNumberString);
    opponentNumber = checkInt(opponentNumberAVTwo, opponentNumberString);
    enemyProvinces = opponentNumber;
    playerProvinces = 1;

    maxAmountOfCommanders = continentSize;

    for (int x = 0; x < opponentNumber; x++)
    {
        confirmOpponents[x] = 'Y';
    }

    string input;
    std::cout << "What gameplay difficulty do you want (1-3): ";
    std::getline(cin, input);

    vector<int> inputAVTwo = { 1,2,3 };
    enemyDifficulty = checkInt(inputAVTwo, input);
    std::cout << "Gameplay difficulty " << enemyDifficulty << " selected. " << endl;

    std::cout << endl;


    for (int x = 1; x <= opponentNumber; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            provincesList[participantCoordinates[x][0]][participantCoordinates[x][1]].addResources (y, initialResources[y] * enemyDifficulty);
        }
    }

    generateNewContinent(opponentNumber);
}
void generateNewContinent(int opponentNumber)
{
    initializeValues();
    
    srand(static_cast<int>(time(0)));
    *playerCapitalProvinceX = rand() % (continentSize - 1);
    *playerCapitalProvinceY = rand() % (continentSize - 1);
    Provinces* playerCapitalProvince;
    playerCapitalProvince = &provincesList[*playerCapitalProvinceX][*playerCapitalProvinceY];
    playerCapitalProvince->setCoordinates(*playerCapitalProvinceX, *playerCapitalProvinceY);
    playerCapitalProvince->provinceIsACapital('P');

    char repeatMap = 'Y';

    int enemyX = 0;
    int enemyY = 0;

    for (int x = 1; x <= opponentNumber; x++)
    {
        repeatMap = 'Y';
        while (repeatMap == 'Y')
        {
            repeatMap = 'N';
            enemyX = rand() % (continentSize - 1);
            enemyY = rand() % (continentSize - 1);
            if (provincesList[enemyX][enemyY].getProvinceIdentifier() == '0')
            {
                provincesList[enemyX][enemyY].provinceIsACapital('E');
                participantCoordinates[x][0] = enemyX;
                participantCoordinates[x][1] = enemyY;
            }
            else
            {
                repeatMap = 'Y';
            }
        }
    }
    
    /*Create 2D vector of commander identifiers*/
    for (int x = 0; x <= opponentNumber; x++) 
    {
        
        vector <char> listOfIdentifiers;
        for (int x = 0; x < sizeof(generalCommanderIdentifiers); x++)
        {
            listOfIdentifiers.push_back(generalCommanderIdentifiers[x]);
        }
        commanderIdentifiersList.push_back(listOfIdentifiers);
        vector <char> listOfIdentifiersTwo;
        commanderIdentifiers.push_back(listOfIdentifiersTwo);
    }
    
    /*Create 2D vector of commanders*/
    for (int x = 0; x <= opponentNumber; x++)
    {
        vector <CommanderProfile> listOfCommandersThingy;
        char commanderIdentifier = commanderIdentifiers[x][0];
        CommanderProfile newCommander (1, commanderIdentifier, 1);
        listOfCommandersThingy.push_back(newCommander);
        commandersList.push_back(listOfCommandersThingy);
        commandersList[x][0].changeCoordinates(participantCoordinates[x][0], participantCoordinates[x][1]);

        commanderIdentifiers[x].push_back(commanderIdentifiersList[x][0]);
        commanderIdentifiersList[x].erase(commanderIdentifiersList[x].begin());
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



void playerScout(int xCoordinate, int yCoordinate) /*So much to fix here... truly so much*/
{
    int enemyProvinceLevel = provincesList[xCoordinate][yCoordinate].findProvinceLevel(); 
    std::cout << "Province selected to scout: (" << translateCoordinate(xCoordinate, 'x', 'O') << ", " << translateCoordinate(yCoordinate, 'y', 'O') << ") ";
    std::cout << " Level of this province: " << enemyProvinceLevel << endl << endl;
    string playerScoutString;
    provincesCanSelect.clear();
    std::cout << "You can only scout this unit if one of your provinces or armies is next to it... " << endl;
    for (int a = -1; a <= 1; a++) /*Identify the surrounding units that can scout, add them to vectors (their coordinates)*/
    {
        for (int b = -1; b <= 1; b++)
        {
            if (xCoordinate + a >= 0 && xCoordinate + a < continentSize)
            {
                if (yCoordinate + b >= 0 && yCoordinate + b < continentSize)
                {
                    switch (provincesList[xCoordinate + a][yCoordinate + b].getProvinceIdentifier())
                    {
                    case 'P':
                    case 'p':
                    case 'H':
                    {
                        provincesCanSelect.push_back(provincesList[xCoordinate + a][yCoordinate + b]);
                        break;
                    }
                    }
                }
            }
        }
    }

    if (provincesCanSelect.size() > 0)
    {
        if (provincesList[xCoordinate][yCoordinate].getCommandersPresent() == 1)
        {
            string proceedWithScout;
            std::cout << "You have " << provincesCanSelect.size() << " provinces or armies next to the target. Below is a list of units that can scout the target.";
            std::cout << " Please note that the higher the level of the scouting unit, the more accurate the results of the scout report are (The level of the target unit is " << enemyProvinceLevel << "). " << endl << endl;
            
            vector <int> unitLevels = showUnitsCanScout(provincesCanSelect);
            int cutOffThingy = unitLevels[0];
            unitLevels.erase(unitLevels.begin());
            std::cout << endl;
            std::cout << "Please enter the number of the unit you would like to select: ";
            getline(cin, playerScoutString);
            int scoutWithThis = checkInt(unitLevels, playerScoutString);
            scoutWithThis--;
            int xCoordinateThingy = 0;
            int yCoordinateThingy = 0;
            int unitAccuracyLevel = 0;
            std::cout << "Proceed scout action with unit at (" << translateCoordinate(xCoordinateThingy, 'x', 'O') << ", " << translateCoordinate(yCoordinateThingy, 'y', 'O') << ")? (Y/N) ";
            char proceedWithScoutChar = getChar(" ", "YN", 2);
            if (proceedWithScoutChar == 'Y')
            {
                int accuracy = 50;
                if (unitLevels[scoutWithThis] > enemyProvinceLevel)
                {
                    for (int x = unitLevels[scoutWithThis]; x >= enemyProvinceLevel; x--)
                    {
                        accuracy += 5;
                    }
                }
                if (unitLevels[scoutWithThis] < enemyProvinceLevel)
                {
                    for (int x = unitLevels[scoutWithThis]; x <= enemyProvinceLevel; x++)
                    {
                        accuracy -= 5;
                    }
                }

                if (accuracy > 100)
                {
                    accuracy = 100;
                }
                if (accuracy < 0)
                {
                    accuracy = 0;
                }
                scoutLogCalculationsProvince(xCoordinate, yCoordinate, accuracy);/*fix this-- add functionality to differentiate between province and commander scout stuff*/
            }
        }
        else
        {
            std::cout << "There are multiple enemy units at this location... please pick the enemy unit you would like to scout:" << endl;//fix this--identify which enemy to scout if there are multiple enemies at a province
            //...*code to find the unit, find which enemy pariticipant it belongs to and which army commander if applicable
            int whichParticipant = 0;//fix this
            int accuracy = 0;
            int commanderIndex = 0;//FIX THISSSSSSSSSSSS
            string target;
            if (target == "Commadner")
            {
                scoutLogCalculationsCommander(whichParticipant, commanderIndex, accuracy);
            }
            else
            {
                scoutLogCalculationsProvince(xCoordinate, yCoordinate, accuracy);
            }
        }
    }
    else
    {
        std::cout << "No player provinces or armies are around the target... " << endl;
    }
    std::cout << "Returning to previous menu" << endl << endl;
} /*fix this-- needs to be reviewed*/
vector<int> showUnitsCanScout(vector <Provinces> &provincesCanSelect)
{
    int unitLevel;
    int xReplacement;
    int yReplacement;
    vector <int> unitLevels = {0};
    std::cout << "\033[;34m";
    vector <CommanderProfile> commandersCanSelect;
    char commanderThingy = ' ';
    for (int x = 0; x < provincesCanSelect.size(); x++)
    {
        for (int a = 0; a < provincesCanSelect[x].getCommandersPresent(); a++)
        {
            commandersCanSelect.push_back(commandersList[0][provincesCanSelect[x].returnCommanderIndex(a)]);
        }
    }
    int b = 1;
    std::cout << "Provinces that can scout: " << endl;
    for (int a = 0; a < provincesCanSelect.size(); a++)
    {
        xReplacement = provincesCanSelect[a].getCoordinate('X');
        yReplacement = provincesCanSelect[a].getCoordinate('Y');
        unitLevel = provincesCanSelect[a].findProvinceLevel();

        unitLevels.push_back(unitLevel);
        std::cout << b << ": (" << translateCoordinate(xReplacement, 'x', 'O') << ", " << translateCoordinate(yReplacement, 'y', 'O') << "); ";
        std::cout << "Unit level: " << unitLevel;
        b++;
    }
    int cutOffProvinceCommanderThingy = (int) unitLevels.size() - 1;
    unitLevels[0] = cutOffProvinceCommanderThingy;

    std::cout << "Commanders that can scout: " << endl;
    for (int a = 0; a < provincesCanSelect.size(); a++)
    {
        xReplacement = commandersCanSelect[a].getCoordinate('X');
        yReplacement = commandersCanSelect[a].getCoordinate('Y');
        unitLevel = commandersCanSelect[a].getCommanderLevel();
        unitLevels.push_back(unitLevel);
        std::cout << b << ": (" << translateCoordinate(xReplacement, 'x', 'O') << ", " << translateCoordinate(yReplacement, 'y', 'O') << "); ";
        std::cout << "Unit level: " << unitLevel;
        b++;
    }
    std::cout << endl;
    std::cout << "\033[;0m";
    return unitLevels;
}

int findUnitLevel(int xCoordinate, int yCoordinate, char identifier)
{
    int unitLevel = 0;
    char commanderChar = ' ';
    switch (identifier)
    {
    case 'C':
    {
        if (provincesList[xCoordinate][yCoordinate].getCommandersPresent() == 1)
        {
            for (int x = 0; x < commandersList[0].size(); x++)
            {
                if (xCoordinate == commandersList[0][x].getCoordinate('X'))
                {
                    if (yCoordinate == commandersList[0][x].getCoordinate('Y'))
                    {
                        return commandersList[0][x].getCommanderLevel();
                    }
                }
            }
        }
    }
    case 'P':
    {
        if (provincesList[xCoordinate][yCoordinate].getCommandersPresent() == 0)
        {
            return provincesList[xCoordinate][yCoordinate].findProvinceLevel();
        }
    }
    default:
        return 0;//if something goes wrong
    }
}
void scoutLogCalculationsCommander(int participantIndex, int commanderIndex, int accuracy)/*fix this-- unfinished*/
{
    //figure something out so that does scout log report for object depending on type-- different object needed for province, commander
    /*Higher accuracy = more accurate scout log-- default is 50% accuracy (if there are 10 food resources in a province,
    the margin is 50%-- 5-15 units. 100 accuracy is the most accurate, 0 accuracy is the least accurate*/
    double newAccuracy = (double) accuracy / 100;
    newAccuracy = 1 - newAccuracy;
    double accuracyAdjustedValueOne;
    int accuracyAdjustedValueTwo;
    int fooOne;
    int fooTwo;
    int findRange;
    srand(time(NULL));
    for (int x = 0; x < 20; x++)
    {
        findRange = commandersList[participantIndex][commanderIndex].getCommanderStat(x);
        accuracyAdjustedValueOne = findRange * newAccuracy;
        fooOne = findRange - (int) accuracyAdjustedValueOne;
        fooTwo = findRange + (int) accuracyAdjustedValueOne;
        accuracyAdjustedValueTwo = rand() % fooOne + fooTwo;
        commandersList[participantIndex][commanderIndex].updateCommanderScoutReport(x, accuracyAdjustedValueTwo);
    }
    commandersList[participantIndex][commanderIndex].updateCommanderScoutReport(20, turn);
    commandersList[participantIndex][commanderIndex].updateCommanderScoutReport(21, accuracy);
}
void scoutLogCalculationsProvince(int xCoordinate, int yCoordinate, int accuracy)
{
    double newAccuracy = (double) accuracy / 100;
    newAccuracy = 1 - newAccuracy;
    double accuracyAdjustedValueOne;
    int accuracyAdjustedValueTwo;
    int fooOne;
    int fooTwo;
    int findRange;
    srand(time(NULL));
    for (int x = 0; x < 20; x++) //fix this
    {
        findRange = provincesList[xCoordinate][yCoordinate].getProvinceStats(x);
        accuracyAdjustedValueOne = findRange * newAccuracy;
        fooOne = findRange - (int) accuracyAdjustedValueOne;
        fooTwo = findRange + (int) accuracyAdjustedValueOne;
        accuracyAdjustedValueTwo = rand() % fooOne + fooTwo;
        provincesList[xCoordinate][yCoordinate].updateProvinceScoutLog(x, accuracyAdjustedValueTwo);
    }
    provincesList[xCoordinate][yCoordinate].updateProvinceScoutLog(20, turn);
    provincesList[xCoordinate][yCoordinate].updateProvinceScoutLog(21, accuracy);
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
    char charAtPoint = provincesList[xCoordinate][yCoordinate].getProvinceIdentifier();
    switch (charAtPoint)
    {
    case 'P':
    case 'p':
        selectPlayerProvince(xCoordinate, yCoordinate);
        break;
    case 'E':
    case 'e':
        selectEnemyProvince(xCoordinate, yCoordinate);
        break;
    case 'H':
        std::cout << "This is one of your units " << endl;
        playerUnitAction(xCoordinate, yCoordinate); /*fix this*/
        break;
    case 'V':
        std::cout << "This is an enmy unit. " << endl;
        selectEnemyAction(xCoordinate, yCoordinate);
        break;
    }
}
void selectPlayerProvince(int xCoordinate, int yCoordinate)
{
    if (provincesList[xCoordinate][yCoordinate].getProvinceIdentifier() == 'P')
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
    if (provincesList[xCoordinate][yCoordinate].getProvinceIdentifier() == 'E')
    {
        std::cout << "This is the enemy's capital province ";
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
        playerScout(xCoordinate, yCoordinate);
        break;
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
            std::cout << "-" << troopNames[x] << ": " << provinceGarrisons[xCoordinate][yCoordinate][x] << endl;
            totalGarrisonedCP += (provinceGarrisons[xCoordinate][yCoordinate][x] * troopsCP[x]);
        }
        std::cout << "Total Garrison Combat Power: " << totalGarrisonedCP << endl << endl;
        break;
    }
    case 'R':
        provincesList[xCoordinate][yCoordinate].printResources();
        break;
    case 'B':
        provincesList[xCoordinate][yCoordinate].printBuildingStats();
        break;
    case 'M':
        break;
    }
}
void playerUnitAction(int xCoordinate, int yCoordinate)
{

    char repeatPlayerUnitAction = 'Y';
    do
    {
        char playerUnitActionChar = listOfActions(2);
        switch (playerUnitActionChar)
        {
        case 'P':
        {
            //find index of commander unit
            int commanderIdentifier = 0;
            for (int x = 0; x < commandersList[0].size(); x++)
            {
                if (commandersList[0][x].getCoordinate('X') == xCoordinate && commandersList[0][x].getCoordinate('Y') == yCoordinate)
                {
                    commanderIdentifier = x;
                    x = (int) commandersList[0].size();
                }
            }
            if (commandersList[0][commanderIdentifier].hasCommanderMoved() == 'N')
            {
                moveUnit(participantCoordinates[0][0], participantCoordinates[0][1], 0, commanderIdentifier);/*fix this*/
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
    for (int x = 0; x < 5; x++)
    {
        std::cout << "Total " << provinceResourcesNames[x] << ": " << totalPlayerResources[x] << endl;
    }
    std::cout << endl;
    for (int x = 0; x < 5; x++)
    {
        std::cout << "Total " << troopNames[x] << " alive: " << totalPlayerUnits[x] << endl;
    }
    playerCP = calculatePlayerValues(1);
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
            gameCode += provincesList[x][y].getProvinceIdentifier();
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
    generateNewContinent(opponentNumber);
}

void initializeValues()
{
    /*Basically create the map-- make each province an object of Provinces*/
    char fooThingyChar = ' ';
    for (int x = 0; x < continentSize; x++)
    {
        vector <Provinces> vectorThingy;
        for (int y = 0; y < continentSize; y++)
        {
            Provinces newProvince;
            vectorThingy.push_back(newProvince);
        }
        provincesList.push_back(vectorThingy);
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

void addNewCommander(vector <CommanderProfile>& playerCommandersList)
{
    char commanderIdentifier = commanderIdentifiersList[0][0];
    int commanderIndex = (int) commandersList[0].size();
    CommanderProfile newCommander(1, commanderIdentifier, commanderIndex);
    playerCommandersList.push_back(newCommander);
}


