#include "ArmyDeploymentMA.h"
#include "textFunctions.h"
#include <iostream>
#include <vector>
#include "textFunctions.h"
#include "otherFunctions.h"
#include "CommanderProfile.h"

using namespace std;
extern int maxAmountOfCommanders;

extern vector < vector <CommanderProfile>> commandersList;
extern vector <vector <Provinces>> provincesList;
extern vector <vector <char>>commanderIdentifiers;
extern vector <vector <char>> commanderIdentifiersList;
extern int initialResources[5];
extern string provinceResourcesNames[5];


ArmyDeploymentMA::ArmyDeploymentMA(int xCoordinate, int yCoordinate)
{
    capitalX = xCoordinate;
    capitalY = yCoordinate;
}
void ArmyDeploymentMA::armyDeploymentMF()
{
    char armyDeploymentActionChar;
    char repeatArmyDeployment = 'Y';
    std::cout << endl;

    do
    {
        std::cout << "Welcome to the Army Deployment action menu" << endl;
        armyDeploymentActionChar = listOfActions(5);
        std::cout << endl;

        switch (armyDeploymentActionChar)
        {
        case 'T':
            trainCommanders();
            break;
        case 'U':
            upgradeCommanders();
            break;
        case 'V':
            viewArmyOverview();
            break;
        case 'D':
        {
            deployCommanderMF();
            break;
        }
        case 'H':
            armyDeploymentHelp(maxAmountOfCommanders);
            break;
        case 'M':
            repeatArmyDeployment = 'N';
            break;
        }
    } while (repeatArmyDeployment == 'Y');
}
void ArmyDeploymentMA::upgradeCommanders() /*fix this-- finish making it*/
{
    Provinces* newProvince;
    newProvince = &provincesList[capitalX][capitalY];
    string upgradeCommanderAV = convertPCIToString(commanderIdentifiers[0]);
    std::cout << "You have " << commandersList[0].size() << " army commanders." << endl;

    if (commandersList[0].size() > 0)
    {
        std::cout << "Here is list of your commanders: " << endl;

        for (int x = 0; x < commandersList[0].size(); x++)
        {
            std::cout << "Army commander " << commandersList[0][x].getCommanderIdentifier() << "; Level: " << commandersList[0][x].getCommanderLevel() << endl;
        }
        std::cout << endl;
        //gets the char of the commander the participant wants to select, compares that against the list of commanders
        int indexOfCommander = findCommanderIndex(getChar("Enter the letter of the army commander you want to upgrade: ", upgradeCommanderAV, 1), upgradeCommanderAV);
        int commanderUpgradeCosts[5] = { 0 };
        printCostsToUpgradeACommander(commanderUpgradeCosts, indexOfCommander);

        std::cout << endl;
        char failCommanderUpgrade = 'S';

        if (getChar("Proceed with upgrade? ", "YN", 1) == 'Y')
        {
            for (int x = 0; x < 5; x++) /*subtracts cost of upgrade from capital resources. If one of the resources goes into the negative,
    training fails; check to make sure there are enough resources to upgrade the commander*/
            {
                newProvince->subtractResources(x, commanderUpgradeCosts[x]);
                if (newProvince->getResource(x) < 0)
                {
                    failCommanderUpgrade = 'F';
                }
            }
            if (failCommanderUpgrade == 'S')
            {
                commandersList[0][indexOfCommander].addCommanderLevel(1);
                std::cout << "Upgrade successful; Commander " << commanderIdentifiers[0][indexOfCommander] << "is now level " << commandersList[0][indexOfCommander].getCommanderIdentifier() << endl;
            }
            else
            {
                for (int x = 0; x < 5; x++) /*return resource values back to original values*/
                {
                    newProvince->addResources(x, commanderUpgradeCosts[x]);
                }
                std::cout << "Upgrade failed. " << endl;
            }
        }
    }
    else
    {
        std::cout << "No commanders available, can not upgrade" << endl;
    }
    std::cout << "Returning to the Army Deployment menu... " << endl << endl;
}
void ArmyDeploymentMA::viewArmyOverview()
{
    string viewArmyOverviewOptionChar;
    for (char foo : commanderIdentifiers[0])
    {
        viewArmyOverviewOptionChar.push_back(foo);
    }
    viewArmyOverviewOptionChar.push_back('B');

    string VAOString;
    char repeatVAO = 'Y';

    std::cout << "You have " << commandersList[0].size() << " commanders. " << endl;

    if (commandersList[0].size() > 0)
    {
        do
        {
            std::cout << "Here is a list of your commanders: " << endl;
            for (int x = 0; x < commandersList[0].size(); x++)
            {
                std::cout << "Commander " << commanderIdentifiers[0][x] << endl;
            }
            std::cout << endl;

            char VAOChar = getChar("Please enter the letter of the commander you wish to select (Enter 'B' to go back to the Army Deployment menu): ",
                viewArmyOverviewOptionChar, 1);

            if (VAOChar == 'B')
            {
                std::cout << "Returning to Army Deployment Menu... " << endl;
                repeatVAO = 'N';
            }
            else
            {
                int participantIndex = 0; /*Fix this when making AI stuff*/
                int index = findCommanderIndex(VAOChar, viewArmyOverviewOptionChar);
                int xThingy = commandersList[participantIndex][index].getCoordinate('X');
                int yThingy = commandersList[participantIndex][index].getCoordinate('Y');

                std::cout << "Commander " << VAOChar << " selected... " << endl;
                std::cout << "The coordinates of this Commander: (" << translateCoordinate(xThingy, 'x', 'O') << ", " << translateCoordinate(yThingy, 'y', 'O') << ") " << endl;
                std::cout << endl;

                commandersList[0][findCommanderIndex(VAOChar,
                    convertPCIToString(commanderIdentifiers[0]))].printCommanderStats();
            }
        } while (repeatVAO == 'Y');
    }
    else
    {
        std::cout << endl;
        std::cout << "No commanders available... returning to the Army Deployment menu" << endl << endl;
    }
}
void ArmyDeploymentMA::trainCommanders()
{
    Provinces *newProvince;
    newProvince = &provincesList[capitalX][capitalY];
    string yesOrNoString;
    int currentPlayerCommanders = commandersList[0].size();
    std::cout << "You have " << currentPlayerCommanders << " army commanders in total. " << endl;
    if (currentPlayerCommanders == 0)
    {
        std::cout << "Do you want to train a commander? (Y/N) ";
    }
    else
    {
        std::cout << "Do you want to train another commnader? (Y/N) ";
    }
    int trainArmyCommanderCosts[5] = { 0 };
    if (getChar("Replacement", "YN", 2) == 'Y')
    {
        if (currentPlayerCommanders < maxAmountOfCommanders) /*if amount of commanders is less than max (not at max capacity)*/
        {
            printCostsToTrainAnotherCommander(trainArmyCommanderCosts, currentPlayerCommanders);
            char failCommanderTraining = 'S';

            if (getChar("Proceed with upgrade? (Y/N) ", "YN", 1) == 'Y')
            {
                for (int x = 0; x < 5; x++) /*subtracts cost of upgrade from a province's land resources. If one of the resources goes into the negative,
training fails*/
                {
                    newProvince->subtractResources(x, trainArmyCommanderCosts[x]);
                    if (newProvince->getResource(x) < 0)
                    {
                        failCommanderTraining = 'F';
                    }
                }

                if (failCommanderTraining == 'S')
                {
                    currentPlayerCommanders++;
                    std::cout << "Commander training successful " << endl;
                    std::cout << "Current commanders: " << commandersList[0].size() + 1 << endl;
                    int commanderIndex = commandersList[0].size();
                    CommanderProfile newCommander(1, commanderIdentifiersList[0][0], commanderIndex);
                    commandersList[0].push_back(newCommander);

                    updateCommanderIdentifiers(0);
                }
                else /*If training fails, return province land resources to their original values*/
                {
                    std::cout << "Commander training failed (Not enough resources)... " << endl << endl;
                    for (int x = 0; x < 5; x++)
                    {
                        newProvince->addResources(x, trainArmyCommanderCosts[x]);
                    }
                }
            }
        }
        else
        {
            std::cout << "At maximum army commander amount. Training failed, returning to menu " << endl;
        }
    }
    else
    {
        std::cout << "Returning to previous menu... " << endl;
    }
}
void ArmyDeploymentMA::deployCommanderMF()
{
    int commandersInCapital = provincesList[capitalX][capitalY].getCommandersPresent();

    if (commandersInCapital == 0)
    {
        std::cout << "No commanders in capital, cannot deploy..." << endl;
    }
    else
    {
        string listOfCommanders = deployCommanderDisplayInformation(commandersInCapital);

        char returnToMenu = 'N';
        string listOfCommandersTwo = listOfCommanders;
        listOfCommandersTwo.push_back(1);
        string commanderLetterIdentifierString;
        do
        {
            char commanderLetterIdentifierChar = getChar("Enter the letter identifier of the commander you want to deploy (enter '1' to go back to previous menu): ",
                listOfCommandersTwo, 1);
            std::cout << endl;

            if (commanderLetterIdentifierChar != 1)
            {
                int indexToSelect = findCommanderIndex(commanderLetterIdentifierChar, listOfCommanders);

                commandersList[0][indexToSelect].printCommanderStats();

                string confirmDeployCommanderString;
                std::cout << "Deploy commander " << commanderLetterIdentifierChar << "? (Y/N) ";
                char confirmDeployCommanderChar = getChar("Replacement", "YN", 2);

                int participantIndex = 0; /*Fix this when developing AI*/
                int xThingyTwo = commandersList[participantIndex][indexToSelect].getCoordinate('X');
                int yThingyTwo = commandersList[participantIndex][indexToSelect].getCoordinate('Y');
                if (confirmDeployCommanderChar == 'Y')
                {
                    if (commandersList[0][indexToSelect].hasCommanderMoved() == 'N')
                    {
                        moveUnit(xThingyTwo, yThingyTwo, 0, indexToSelect);
                        returnToMenu = 'Y';
                    }
                    else
                    {
                        std::cout << "This unit has already moved... please pick another unit " << endl;
                    }
                }
            }
            else
            {
                returnToMenu = 'Y';
            }
        } while (returnToMenu == 'N');
        std::cout << endl;
    }
    std::cout << "Returning to the Army Deployment action menu" << endl;
    std::cout << endl;
}
string ArmyDeploymentMA::deployCommanderDisplayInformation(int commandersInCapital)
{
    string listOfCommanders;
    int findCommanderLevel;
    char commanderIdentifierThingy;
    std::cout << "The following commanders are in the capital: " << provincesList[capitalX][capitalY].getCommandersPresent() << endl;

    for (int x = 0; x < commandersList[0].size(); x++)
    {
        listOfCommanders.push_back(commandersList[0][x].getCommanderIdentifier());
    }

    for (int a = 0; a < commandersInCapital; a++)
    {
        commanderIdentifierThingy = provincesList[0][a].returnCommanderPresentIdentifier(a);
        findCommanderLevel = findCommanderIndex(commanderIdentifierThingy, listOfCommanders);
        std::cout << "Commander " << provincesList[0][a].returnCommanderPresentIdentifier(a) << "; Level: " <<
            commandersList[0][a].getCommanderLevel() << endl;
    }

    std::cout << endl;
    return listOfCommanders;
}

void ArmyDeploymentMA::printCostsToUpgradeACommander(int commanderUpgradeCosts[5], int indexOfCommander)
{
    std::cout << "The following is the cost to upgrade commander " << commanderIdentifiers[0][indexOfCommander] << endl;
    for (int x = 0; x < 5; x++)/*Cost of upgrade increases after each upgrade, cheaper than training a new one*/
    {
        commanderUpgradeCosts[x] = commandersList[0][indexOfCommander].getCommanderLevel() * 5;
        commanderUpgradeCosts[x] *= initialResources[x];
        std::cout << provinceResourcesNames[x] << ": " << commanderUpgradeCosts[x] << endl;
    }
}