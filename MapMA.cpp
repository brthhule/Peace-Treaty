#include <iostream>

#include "otherFunctions.h"
#include "MapMA.h"
#include "textFunctions.h"
#include "Provinces.h"
#include "CommanderProfile.h"
#include "Participants.h"
#include "BuildMA.h"
#include "ScoutMA.h"
#include "AttackMA.h"
#include "TrainMA.h"
#include "Lists.h"
#include "coordinateFunctions.h"

using namespace std;

extern int currentParticipantIndex;
extern vector <vector <Provinces>> provincesMap;
extern vector <vector <CommanderProfile>> allCommanders;
extern vector <Participants> participantsList;
extern string troopNames[5];
extern int troopsCP[5];

MapMA::MapMA ()
{
    xCoordinate = 0;
    yCoordinate = 0;
}
void MapMA::viewPlayerMap()
{
    char whatToDo = ' ';
    showMap();
    char repeatViewPlayerMap = 'Y';

    do
    {
        std::cout << "Welcome to the View Map action menu" << endl;
        Lists newList (8);
        whatToDo = newList.listOfActions();

        switch (whatToDo)
        {
        case 'P':
        {
            getCoordinates(1, xCoordinate, yCoordinate);
            if (xCoordinate != -1 && yCoordinate != -1)
            {
                selectUnitOriginal();
            }
            break;
        }
        case 'H':
        {
            Lists newLists (8);
            newLists.listOfHelp();
            break;
        }
        default:
            std::cout << "Returning to the previous menu." << endl;
            repeatViewPlayerMap = 'N';
            std::cout << endl;
            break;
        }
    } while (repeatViewPlayerMap == 'Y');
}
void MapMA::selectUnitOriginal()
{
    Provinces *newMap = &provincesMap[xCoordinate][yCoordinate];
    if (newMap->getBelongsToParticipant() == currentParticipantIndex)//If belongs to participant
    {
        selectPlayerProvince();
    }
    else if (newMap->getBelongsToParticipant() == -1)//If empty province
    {
        if (newMap->commandersPresentIndex.size() > 0)//If there are more than 0 commnaders
        {
            if (allCommanders[currentParticipantIndex][provincesMap[xCoordinate][yCoordinate].returnCommanderIndex(0)].getBelongsToParticipant() == currentParticipantIndex) //If the army here belongs to the participant
            {
                playerUnitAction();
            }
            else
            {
                selectEnemyAction();
            }
        }
    }
    else //If enemy province
    {
        selectEnemyProvince();
    }
}
void MapMA::selectPlayerProvince()
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

    Lists newList (9);
    char selectPlayerCapitalAction = newList.listOfActions();

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
void MapMA::selectEnemyProvince()
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
    Lists newLists (10);
    char selectUnitEnemyProvinceChar = newLists.listOfActions();

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
        if (provincesMap[xCoordinate][yCoordinate].scoutLogTurnLevel[0] != -1)
        {
            if (getChar("View scout log for this province? (Y/N) ", "YN", 1) == 'Y')/*Ask user if they want to view scout log, get char, go to scoutLogFunction if 'Y'*/
            {
                scoutLogFunction();
            }
        }
        break;
    }
    case 'M':
        std::cout << "Returning to the menu... " << endl;
        break;
    }

}

void MapMA::playerUnitAction()
{
    std::cout << "This is one of your armies " << endl;
    Participants* newParticipant = &participantsList[currentParticipantIndex];

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
                allCommanders[currentParticipantIndex][commanderIndex].moveUnit();/*fix this*/
            }
            else
                std::cout << "This unit has already moved this turn... returning to the View Map action menu " << endl << endl;
            repeatPlayerUnitAction = 'N';
            break;
        }
        case 'H':
            listOfHelp(2);
            break;
        case 'M':
            std::cout << "Returning to menu... " << endl;
            repeatPlayerUnitAction = 'N';
            break;
        }
    } while (repeatPlayerUnitAction == 'Y');
}
void MapMA::selectEnemyAction()/*finish this*/
{
    std::cout << "This is an enmy army. " << endl;
    char repeatSelectEnemyAction = 'Y';
    do
    {
        listOfActions(1);
    } while (repeatSelectEnemyAction == 'Y');
}

void MapMA::scoutLogFunction()
{
    char repeatScoutLog = 'N';
    char whatReportChar;

    std::cout << "Turn of scout report: " << provincesMap[xCoordinate][yCoordinate].scoutLogTurnLevel[0] << "; Level of report: " << provincesMap[xCoordinate][yCoordinate].scoutLogTurnLevel[1] << endl << endl;
    do
    {
        whatReportChar = listOfActions(11);
        provinceReportLog(whatReportChar);

    } while (repeatScoutLog == 'Y');
}
void MapMA::provinceReportLog(char whatReportChar)
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
