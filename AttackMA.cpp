#include "AttackMA.h"
#include <iostream>
#include <vector>
#include <string>
#include "CommanderProfile.h"
using namespace std;


extern int continentSize;
extern int enemyDifficulty;

extern vector <vector <CommanderProfile>> commandersList;
extern vector <vector <Provinces>> provincesList;



AttackMA::AttackMA()
{}
AttackMA::AttackMA(int xCoordinatearg, int yCoordinatearg, int enemyXarg, int enemyYarg, int participantIndexarg, int commanderIndexarg)
{
    int unitAttackingX = xCoordinatearg;
    int unitAttackingY = yCoordinatearg;
    int unitBeingAttackedX = enemyXarg;
    int unitBeingAttackedY = enemyYarg;
    int participantIndex = participantIndexarg;
    int commanderIndex = commanderIndexarg;
}
void AttackMA::playerAttack() /*fix this*/
{
    if (commanderIndex == -1)
    {
        char canAttack = 'N';
        int amountOfHeros = 0;
        int herosCanAttack[2][4] = { 0 };
        int z = 0;
        int attackUnitWithX = 0;
        int attackUnitWithY = 0;

        int forLoopX;
        int forLoopY;

        for (int x = -1; x < 2; x++)
        {
            for (int y = -1; y < 2; y++)
            {
                forLoopX = unitBeingAttackedX + x;
                forLoopY = unitBeingAttackedY + y;
                if (forLoopX >= 0 && forLoopX < continentSize)
                {
                    if (forLoopY >= 0 && forLoopY < continentSize)
                    {
                        if (commandersList[forLoopX][forLoopY].getCommanderIdentifier() == 'H')
                        {
                            amountOfHeros++;
                            canAttack = 'Y';
                            herosCanAttack[0][z] = unitAttackingX + x;
                            herosCanAttack[1][z] = unitAttackingY + y;
                            z++;
                        }
                    }
                }
            }
        }

        if (amountOfHeros == 0)
        {
            std::cout << "There are no armies available to attack the enemy. Please move an army unit to one of the provinces around the target. ";
            std::cout << endl;
            std::cout << endl;
        }
        if (amountOfHeros < 0)
        {
            std::cout << "The following armies can attack the target: " << endl;
            std::cout << "Amount of heros: " << amountOfHeros << endl;
            for (int x = 0; x < amountOfHeros; x++)
            {
                std::cout << "1: (" << herosCanAttack[0][x] << ", " << herosCanAttack[1][x] << ") ";
            }
            char repeatVerifyCanAttack = 'Y';

            do
            {
                vector <int> XYCoordinates = getCoordinates(3);
                attackUnitWithX = XYCoordinates[0];
                attackUnitWithY = XYCoordinates[1];
                std::cout << endl;
                if (attackUnitWithX == -1 || attackUnitWithY == -1)
                {
                    std::cout << "Returning to previous menu... " << endl << endl;
                    repeatVerifyCanAttack = 'N';
                }
                else
                {
                    char verifyCanAttack = ' ';

                    for (int b = 0; b < amountOfHeros; b++)
                    {
                        if (attackUnitWithX == herosCanAttack[0][b] && attackUnitWithY == herosCanAttack[1][b]) /*fix this*/
                        {
                            verifyCanAttack = 'Y';
                        }
                    }

                    if (verifyCanAttack == 'Y')
                    {
                        for (int playerCommanderIndex = 0; playerCommanderIndex < commandersList[participantIndex].size(); playerCommanderIndex++)
                        {
                            if (attackUnitWithX == commandersList[participantIndex][playerCommanderIndex].getCoordinate('X') && 
                                attackUnitWithY == commandersList[participantIndex][playerCommanderIndex].getCoordinate('Y'))
                            {
                                return playerCommitAttack(); /*May have to fix this at some point*/
                            }
                        }
                    }
                    else
                    {
                        std::cout << "Invalid unit selected. Please try again" << endl;
                        break;
                    }
                }
            } while (repeatVerifyCanAttack == 'Y');
        }
    }
    else
    {
        playerCommitAttack();
    }
}
void AttackMA::playerCommitAttack()
{
    CommanderProfile* ptrCommanderProfile;
    ptrCommanderProfile = &commandersList[participantIndex][commanderIndex];
    vector <char> targetEnemyCommanders;

    int oldResources[5] = { 0 };
    for (int x = 0; x < 5; x++)
    {
        oldResources[x] = ptrCommanderProfile->getResource(x);
    }
    int whichEnemy = 0;//fix this-- have to add some function to determine which enemy is being attacked (if there are multiple enemies) and which
    //enemy commander/army is being atacked
    int whichCommander = 0;
    if (commandersList[whichEnemy][whichCommander].getCommanderArmyCP() < ptrCommanderProfile->getCommanderArmyCP()) /*if the enemy defender has less CP than attacking player army*/
    {
        ;
        std::cout << "You won! ";
        playerCommitAttackWin(oldResources);
    }
    else if (commandersList[whichEnemy][whichCommander].getCommanderArmyCP() > ptrCommanderProfile->getCommanderArmyCP()) /*if defending enemy has more CP than attacking player*/
    {/*fix this-- add on to this*/
    }
}
void AttackMA::playerCommitAttackWin(int oldResources[5])
{
    CommanderProfile* ptrCommanderProfile;
    ptrCommanderProfile = &commandersList[participantIndex][commanderIndex];
    int whichEnemy = 0;//fix this
    int whichCommander = 0;
    for (int x = 0; x < 5; x++)
    {
        ptrCommanderProfile->addResources(x, commandersList[whichEnemy][whichCommander].getResource(x));
    }
    int difference = ptrCommanderProfile->getCommanderArmyCP() / commandersList[whichEnemy][whichCommander].getCommanderArmyCP();
    int lostCombatPower = commandersList[whichEnemy][whichCommander].getCommanderArmyCP() * (1 / difference);
    int deadTroops[5] = { 0 };
    int injuredTroops[5] = { 0 };

    for (int a = 0; lostCombatPower > 0; a++)
    {
        battleCalculations(lostCombatPower, deadTroops, playerTroopsLost, a);
        for (int x = 0; x < 5; x++)
        {
            injuredTroops[x] = deadTroops[x] / (2 * enemyDifficulty);
            deadTroops[x] -= injuredTroops[x];
        }
        for (int x = 10; x < 15; x++)
        {
            ptrCommanderProfile->addInjuredTroops(x, injuredTroops[x - 10]);/*fix this?*/
        }

        std::cout << "  Results: " << endl << endl;
        std::cout << "Resources gained: " << endl;
        for (int x = 0; x < 5; x++) /*print out resources*/
        {
            std::cout << provinceResourcesNames[x] << " gained: " << ptrCommanderProfile->getResource(x) - oldResources[x] << endl;
        }
        casualtyReport(deadTroops, injuredTroops);

        char viewAllArmyStats = ' ';
        char repeatViewAllArmyStats = 'N';
        string viewAllArmyStatsString;

        provincesList[unitAttackingX][unitAttackingY].addCommandersPresent(1);
        provincesList[unitAttackingX][unitAttackingY].setProvinceIdentifier('H');

        do
        {
            repeatViewAllArmyStats = 'N';
            viewAllArmyStats = getChar("View all army stats? (Y/N) ", "YN", 1);
            std::cout << endl;

            switch (viewAllArmyStats)
            {
            case 'Y':
            {
                ptrCommanderProfile->printCommanderStats();
                break;
            }
            case 'N':
                break;
                std::cout << endl;
            default:
                repeatViewAllArmyStats = 'Y';
                std::cout << "Invalid character entered. Please try again." << endl;
                break;
            }
        } while (repeatViewAllArmyStats == 'Y');

        /*fix this-- add attack functionality, differences in CP and stuff*/
    }
}
void AttackMA::battleCalculations(int lostCombatPower, int deadTroops[5], int playerTroopsLost[5], int a)
{
    CommanderProfile* ptrCommanderProfile;
    ptrCommanderProfile = &commandersList[participantIndex][commanderIndex];
    switch (a)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    {
        int b = a + 5;
        battleCalculationsTwo(lostCombatPower, deadTroops, playerTroopsLost, b);
        break;
    }
    case 4:
        if (ptrCommanderProfile->getTroopsPresent(9) > 0)
        {
            if (lostCombatPower > 0)
            {
                lostCombatPower -= troopsCP[a];
                deadTroops[a] ++;
                ptrCommanderProfile->removeTroops(9, 1);
                playerTroopsLost[a] += 1;
            }
        }
        a = -1;
        break;
    }
}
void AttackMA::battleCalculationsTwo(int& lostCombatPower, int deadTroops[5], int playerTroopsLost[5], int identifier)/*fix this*/
{
    CommanderProfile* ptrCommanderProfile;
    ptrCommanderProfile = &commandersList[participantIndex][commanderIndex];
    int z = abs(4 - identifier);

    for (int b = 0; b < troopsCP[z]; b++)
    {
        if (ptrCommanderProfile->getTroopsPresent(5) > 0)
        {
            b = troopsCP[z];
        }
        else
        {
            if (lostCombatPower > 0)
            {
                lostCombatPower -= troopsCP[identifier];
                deadTroops[identifier] ++;
                ptrCommanderProfile->removeTroops(identifier, 1);
                playerTroopsLost[identifier] += 1;
            }
            else
                b = troopsCP[z];
        }
    }
}