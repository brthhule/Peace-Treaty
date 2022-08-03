#include "ArmyDeploymentMA.h"
#include "textFunctions.h"
#include <iostream>
#include <vector>
#include "textFunctions.h"
#include "otherFunctions.h"
#include "CommanderProfile.h"
#include "Participants.h"

using namespace std;
extern int maxAmountOfCommanders;

extern vector <vector <Provinces>> provincesMap;
extern int initialResources[5];
extern string provinceResourcesNames[5];
extern int actualParticipantIndex;
extern vector <Participants> participantsList;


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
    newProvince = &provincesMap[capitalX][capitalY];
    string upgradeCommanderAV = convertPCIToString(participantsList[actualParticipantIndex].commanderIdentifiersList);

    Participants* newParticipant = &participantsList[actualParticipantIndex];
    std::cout << "You have " << newParticipant->howManyCommanders() << " army commanders." << endl;

    if (participantsList[actualParticipantIndex].howManyCommanders() > 0)
    {
        std::cout << "Here is list of your commanders: " << endl;

        for (int x = 0; x < newParticipant->howManyCommanders(); x++)
        {
            std::cout << "Army commander " << newParticipant->returnCommander(x)->getCommanderIdentifier() << "; Level: " << newParticipant->returnCommander(x)->getCommanderLevel() << endl;
        }
        std::cout << endl;
        //gets the char of the commander the participant wants to select, compares that against the list of commanders
        int indexOfCommander = findCommanderIndex(getChar("Enter the letter of the army commander you want to upgrade: ", upgradeCommanderAV, 1));
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
                newParticipant->returnCommander(indexOfCommander)->addCommanderLevel(1);
                std::cout << "Upgrade successful; Commander " << newParticipant->returnCommander(indexOfCommander)->getCommanderIdentifier() << "is now level " << 
                    newParticipant->returnCommander(indexOfCommander)->getCommanderIdentifier() << endl;
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
    Participants* newParticipant = &participantsList[actualParticipantIndex];
    string viewArmyOverviewOptionChar;
    for (int x = 0; x < newParticipant->howManyCommanders(); x++)
    {
        viewArmyOverviewOptionChar.push_back(newParticipant->returnCommander(x)->getCommanderIdentifier());
    }
    viewArmyOverviewOptionChar.push_back('B');

    string VAOString;
    char repeatVAO = 'Y';

    std::cout << "You have " << newParticipant->howManyCommanders() << " commanders. " << endl;

    if (newParticipant->howManyCommanders() > 0)
    {
        do
        {
            std::cout << "Here is a list of your commanders: " << endl;
            for (int x = 0; x < newParticipant->howManyCommanders(); x++)
            {
                std::cout << "Commander " << newParticipant->returnCommander(x)->getCommanderIdentifier() << endl;
            }
            std::cout << endl;

            char VAOChar = getChar("Please enter the letter of the commander you wish to select: ",
                viewArmyOverviewOptionChar, 1);
            cout << "Confirm selection of commander " << VAOChar << "? (Y/N): ";
            char confirmSelection = getChar("0", "YN", 2);

            switch (confirmSelection)
            {
            case 'Y':
            {
                int index = findCommanderIndex(VAOChar);

                std::cout << "Commander " << VAOChar << " selected... " << endl;
                std::cout << "The coordinates of this Commander: (" << translateCoordinate(newParticipant->returnCommander(index)->getCoordinate('X'), 'x', 'O') << ", " <<
                    translateCoordinate(newParticipant->returnCommander(index)->getCoordinate('Y'), 'y', 'O') << ") " << endl;
                std::cout << endl;

                newParticipant->returnCommander(index)->printCommanderStats();
                break;
            }
            case 'N':
                std::cout << "Returning to Army Deployment Menu... " << endl;
                repeatVAO = 'N';
                break;
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
    Provinces* newProvince;
    newProvince = &provincesMap[capitalX][capitalY];

    Participants* newParticipant = &participantsList[actualParticipantIndex];
    string yesOrNoString;
    int currentPlayerCommanders = newParticipant->howManyCommanders();
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
                    std::cout << "Current commanders: " << newParticipant->howManyCommanders() + 1 << endl;
                    int commanderIndex = newParticipant->howManyCommanders();
                    CommanderProfile newCommander(1, newParticipant->getCommanderIdentifier(0), commanderIndex);
                    newParticipant->addCommander(newCommander);

                    participantsList[actualParticipantIndex].updateCommanderIdentifiers();
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
    Participants* newParticipant = &participantsList[actualParticipantIndex];
    int commandersInCapital = provincesMap[capitalX][capitalY].getCommandersPresent();

    if (commandersInCapital == 0)
    {
        std::cout << "No commanders in capital, cannot deploy..." << endl;
    }
    else
    {
        deployCommanderDisplayInformation(commandersInCapital);

        char returnToMenu = 'N';
        string listOfCommanders;
        for (int x = 0; x < newParticipant->returnProvince(0).getCommandersPresent(); x++)
        {
            listOfCommanders.push_back(newParticipant->returnProvince(0).returnCommanderPresentIdentifier(x));
        }
        listOfCommanders.push_back(1);
        do
        {
            char commanderLetterIdentifierChar = getChar("Enter the letter identifier of the commander you want to deploy (enter '1' to go back to previous menu): ",
                listOfCommanders, 1);
            std::cout << endl;

            if (commanderLetterIdentifierChar != 1)
            {
                int indexToSelect = findCommanderIndex(commanderLetterIdentifierChar);

                newParticipant->returnCommander(indexToSelect)->printCommanderStats();

                string confirmDeployCommanderString;
                std::cout << "Deploy commander " << commanderLetterIdentifierChar << "? (Y/N) ";
                char confirmDeployCommanderChar = getChar("Replacement", "YN", 2);

                int participantIndex = 0; /*Fix this when developing AI*/
                int xThingyTwo = newParticipant->returnCommander(indexToSelect)->getCoordinate('X');
                int yThingyTwo = newParticipant->returnCommander(indexToSelect)->getCoordinate('Y');
                if (confirmDeployCommanderChar == 'Y')
                {
                    if (newParticipant->returnCommander(indexToSelect)->hasCommanderMoved() == 'N')
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
void ArmyDeploymentMA::deployCommanderDisplayInformation(int commandersInCapital)
{
    int findCommanderLevel = 0;
    char commanderIdentifierThingy = ' ';

    Participants* newParticipant = &participantsList[actualParticipantIndex];

    std::cout << "The following commanders are in the capital: " << provincesMap[capitalX][capitalY].getCommandersPresent() << endl;


    for (int a = 0; a < commandersInCapital; a++)
    {
        commanderIdentifierThingy = provincesMap[newParticipant->getCapitalCoordinate('X')][newParticipant->getCapitalCoordinate('Y')] .returnCommanderPresentIdentifier(a);
        int commanderIndex = findCommanderIndex(commanderIdentifierThingy);
        std::cout << "Commander " << newParticipant->returnCommander(commanderIndex)->getCommanderIdentifier() << "; Level: " <<
            newParticipant->returnCommander(commanderIndex)->getCommanderLevel() << endl;
    }
}

void ArmyDeploymentMA::printCostsToUpgradeACommander(int commanderUpgradeCosts[5], int indexOfCommander)
{
    std::cout << "The following is the cost to upgrade commander " << participantsList[actualParticipantIndex].returnCommander(indexOfCommander)->getCommanderIdentifier() << endl;
    for (int x = 0; x < 5; x++)/*Cost of upgrade increases after each upgrade, cheaper than training a new one*/
    {
        commanderUpgradeCosts[x] = participantsList[actualParticipantIndex].returnCommander(indexOfCommander)->getCommanderLevel() * 5;
        commanderUpgradeCosts[x] *= initialResources[x];
        std::cout << provinceResourcesNames[x] << ": " << commanderUpgradeCosts[x] << endl;
    }
}