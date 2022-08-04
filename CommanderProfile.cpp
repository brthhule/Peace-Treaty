#include "CommanderProfile.h"
#include "AllUnits.h"
#include "AttackMA.h"

extern vector <vector <Provinces>> provincesMap;
extern vector <Participants> participantsList;
extern string provinceResourcesNames[5];
extern string troopNames[5];
extern int turn;
extern int continentSize;
extern int currentParticipantIndex;

/*Constructors*/
CommanderProfile::CommanderProfile()
{
    for (int x = 0; x < 20; x++)
    {
        commanderArmyStats[x] = 0;
    }
    commanderLevel = 1;
    for (int x = 0; x < 22; x++)
    {
        commanderScoutReport[x] = 0;
    }
    hasMoved = 'N';
    maxTroops = 0;
    totalMaxResources = 0;
    indexInList = 0;
    changeUnitName("Unnamed");

}
CommanderProfile::CommanderProfile(int level, string name, int index)
{
    for (int x = 0; x < sizeof(commanderScoutReport) / sizeof(int); x++)
    {
        commanderScoutReport[x] = 0;
    }

    commanderLevel = level;

    for (int x = 0; x < 5; x++)
    {
        commanderArmyStats[x] = &resourcesPresent[x];
        commanderArmyStats[x + 5] = &troopsPresent[x];
        commanderArmyStats[x + 10] = &troopsInjured[x];
    }
    commanderArmyStats[15] = &totalTroops;
    commanderArmyStats[16] = &totalCP;
    commanderArmyStats[17] = &commanderLevel;
    commanderArmyStats[18] = &maxTroops;
    commanderArmyStats[19] = &foodConsumption;

    for (int x = 0; x < 5; x++)
    {
        namesOfMAN[x] = provinceResourcesNames[x];
        namesOfMAN[x + 5] = troopNames[x];
        namesOfMAN[x + 10] = troopNames[x];
    }
    namesOfMAN[15] = "Total Troops";
    namesOfMAN[16] = "Total Army CP";
    namesOfMAN[17] = "Commander Level";
    namesOfMAN[18] = "Max Troops this army can have";
    namesOfMAN[19] = "Army Food consumption";
    maxTroops = commanderLevel * 10;
    totalMaxResources = 0;
    indexInList = index;
    changeUnitName(name);
}
/*Destructor*/
CommanderProfile::~CommanderProfile()
{

}

/*Accessor Functions*/
void CommanderProfile::printCommanderStats()
{
    //print out stats
    cout << "\033[;34m";
    int c = 0;
    for (int a = 0; a < 4; a++)
    {
        std::cout << MANDescriptions[a] << " this army: " << endl;
        for (int b = 0; b < 5; b++)
        {
            std::cout << "- " << namesOfMAN[c] << ": " << commanderArmyStats[c] << endl;
            c++;
        }
    }
    cout << endl;
    cout << "\033[;0m";
}
int CommanderProfile::getCommanderStat(int index)
{
    return *commanderArmyStats[index];
}
int CommanderProfile::printCommanderScoutReport(int index)
{
    return commanderScoutReport[index];
}
int CommanderProfile::getCommanderLevel()
{
    return commanderLevel;
}
char CommanderProfile::hasCommanderMoved()
{
    return hasMoved;
}

/*Mutator Functions*/
void CommanderProfile::changeCommanderStat(int index, int amount)
{
    commanderArmyStats[index] += amount;
}

void CommanderProfile::updateCommanderScoutReport(int index, int value)
{
    commanderScoutReport[index] = value;
}
void CommanderProfile::addCommanderLevel(int amount)
{
    commanderLevel += amount;
}
void CommanderProfile::resetCommanderMoved()
{
    hasMoved = 'N';
}

void CommanderProfile::completeCommanderScoutReport(int accuracy)
{
    /*Higher accuracy = more accurate scout log-- default is 50% accuracy (if there are 10 food resources in a province,
    the margin is 50%-- 5-15 units. 100 accuracy is the most accurate, 0 accuracy is the least accurate*/
    double newAccuracy = (double)accuracy / 100;
    newAccuracy = 1 - newAccuracy;
    double accuracyAdjustedValueOne;
    int accuracyAdjustedValueTwo;
    int fooOne;
    int fooTwo;
    int findRange;
    srand(time(NULL));
    for (int x = 0; x < 20; x++)
    {
        findRange = getCommanderStat(x);
        accuracyAdjustedValueOne = findRange * newAccuracy;
        fooOne = findRange - (int)accuracyAdjustedValueOne;
        fooTwo = findRange + (int)accuracyAdjustedValueOne;
        accuracyAdjustedValueTwo = rand() % fooOne + fooTwo;
        updateCommanderScoutReport(x, accuracyAdjustedValueTwo);
    }
    updateCommanderScoutReport(20, turn);
    updateCommanderScoutReport(21, accuracy);
}


void CommanderProfile::moveUnit()
{
    vector <Provinces*> provincesCanSelect;
    if (hasCommanderMoved() == 'N')
    {
        std::cout << "The coordinates of the chosen unit unit are: ";
        std::cout << "(" << translateCoordinate(unitXCoordinate, 'y', 'O') << ", " << translateCoordinate(unitYCoordinate, 'x', 'O') << ") " << endl;
        std::cout << endl;
        std::cout << "You can only move this unit to one of the provinces adjacent to the province it is in. " << endl;

        for (int x = -1; x <= 1; x++) /*Identify all the provinces that the player can move a unit to*/
        {
            for (int y = -1; y <= 1; y++)
            {
                //Check to see if the coordinates are in bounds (not outside of the map size)
                if (/*X coordinate stuff*/x >= 0 && x < continentSize && /*Y coordinate stuff*/y >= 0 && y < continentSize)
                {
                    //Make sure province isn't the starting province
                    if (x != 0 || y != 0)
                    {
                        //Add province to list of provinces can move to
                        provincesCanSelect.push_back(&provincesMap[x + unitXCoordinate][y + unitYCoordinate]);
                    }
                }
            }
        }
        
        //The participant slects coordiantes
        vector<int> XYCoordinates = getCoordinates(2);
        int moveToXTwo = XYCoordinates[0];
        int moveToYTwo = XYCoordinates[1];
        int provinceIndexSelected = 0;
        char provinceIsInList = 'N'; //Initialize as province is not in list (have to repeat process)
        //Find the province (out of the list) elected using the coordinates chosen
        for (int x = 0; x < provincesCanSelect.size(); x++)
        {
            if (moveToXTwo == provincesCanSelect[x]->getCoordinate('X') && moveToXTwo == provincesCanSelect[x]->getCoordinate('Y'))
            {
                provinceIndexSelected = x;
                provinceIsInList = 'Y';//Province is in list, don't have to repeat process
            }
        }

        //For display
        int moveToX = translateCoordinate(moveToXTwo, 'x', 'O');
        int moveToY = translateCoordinate(moveToYTwo, 'y', 'O');

        string confirmMove;
        char attackScenario = 'P';/*P is for peace, A is for attack*/
        //If province is in the list
        if (provinceIsInList == 'Y')
        {
            Provinces* provinceSelected = provincesCanSelect[provinceIndexSelected];
            if (provinceSelected->getBelongsToParticipant() != currentParticipantIndex)
            {
                attackScenario = 'A';
                std::cout << "Moving here will cause your unit to attack any enemy units stationed at this province." << endl;
            }
            std::cout << "Confirm moving your unit to (" << moveToX << ", " << moveToY << ")? (Y/N) ";

            //If participants confirms movement
            if (getChar("Replacement", "YN", 2) == 'Y')
            {
                //If it's peaceful (moving to one of their own provinces)
                if (attackScenario == 'P')
                {
                    changeCoordinates(moveToXTwo, moveToYTwo);

                    provinceSelected->addCommanderProvince(indexInList);
                }
                //If scenario is attack
                else
                {
                    AttackMA newAttackMA(unitXCoordinate, unitYCoordinate, moveToXTwo, moveToYTwo, indexInList, belongsToParticipant);
                    newAttackMA.playerAttack();//fix this-- don't need to pass unitXCoordinate, can just use indexInList
                }
            }
        }
        else
        {
            cout << "Invalid province selected... please try again. " << endl;
            //Recursion until suitable coordinates are chosen
            moveUnit();
        }
    }
    else
    {
        std::cout << "This unit has already moved this turn. Please pick another unit. " << endl;
    }
    std::cout << "Returning to previous menu... " << endl << endl;
}/* unfinished*/
