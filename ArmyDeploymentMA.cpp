#include <iostream>
#include <vector>

#include "ArmyDeploymentMA.h"

#include "textFunctions.h"
#include "otherFunctions.h"

#include "CommanderProfile.h"
#include "Participants.h"
#include "coordinateFunctions.h"


using namespace std;
extern int maxAmountOfCommanders;

extern vector <vector <Provinces>> provincesMap;
extern vector < vector <CommanderProfile>> allCommanders;
extern vector <Participants> participantsList;

extern string provinceResourcesNames[5];
extern int initialResources[5];
extern int currentParticipantIndex;


ArmyDeploymentMA::ArmyDeploymentMA()
{
    capitalX = participantsList[currentParticipantIndex].getCapitalCoordinate('X'); 
    capitalY = participantsList[currentParticipantIndex].getCapitalCoordinate('Y');
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
    Provinces* newProvince = &provincesMap[capitalX][capitalY];
    Participants* newParticipant = &participantsList[currentParticipantIndex];
    vector <int> indexOfCommanders;
    for (int x = 1; x <= newParticipant->howManyCommanders(); x++)
    {
        indexOfCommanders.push_back(x);
    }

    std::cout << "You have " << newParticipant->howManyCommanders() << " army commanders." << endl;

    if (participantsList[currentParticipantIndex].howManyCommanders() > 0)
    {
        std::cout << "Here is list of your commanders: " << endl;

        for (int x = 0; x < newParticipant->howManyCommanders(); x++)
        {
            std::cout << x + 1 << ") Commander " << allCommanders[currentParticipantIndex][x].getUnitName() << "; Level: " << allCommanders[currentParticipantIndex][x].getCommanderLevel() << endl;
        }
        std::cout << endl;
        //gets the char of the commander the participant wants to select, compares that against the list of commanders
        int indexOfCommander = getInt("Enter the number of the army commander you want to upgrade: ", indexOfCommanders, 1);
        indexOfCommander--;

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
                CommanderProfile* newCommander = &allCommanders[currentParticipantIndex][indexOfCommander];
                newCommander->addCommanderLevel(1);
                std::cout << "Upgrade successful; Commander " << newCommander->getUnitName() << "is now level " <<
                    newCommander->getCommanderLevel() << endl;
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
    Participants* newParticipant = &participantsList[currentParticipantIndex];
    vector <int> listOfOptions = {-1};
    for (int x = 0; x < newParticipant->howManyCommanders(); x++)
    {
        listOfOptions.push_back(x + 1);
    }

    char repeatVAO = 'Y';

    std::cout << "You have " << newParticipant->howManyCommanders() << " commanders. " << endl;

    if (newParticipant->howManyCommanders() > 0)
    {
        do
        {
            std::cout << "Here is a list of your commanders: " << endl;
            for (int x = 0; x < newParticipant->howManyCommanders(); x++)
            {
                std::cout << x + 1 << ") Commander " << allCommanders[currentParticipantIndex][x].getUnitName() << endl;
            }
            std::cout << endl;

            int VAO = getInt("Please enter the number of the commander you wish to select: ",
                listOfOptions, 1);
            int index = VAO - 1;
            cout << "Confirm selection of commander " << allCommanders[currentParticipantIndex][index].getUnitName() << "? (Y/N): ";
            char confirmSelection = getChar("0", "YN", 2);

            switch (confirmSelection)
            {
            case 'Y':
            {
                CommanderProfile* newCommander2 = &allCommanders[currentParticipantIndex][index];

                std::cout << "Commander " << newCommander2->getUnitName() << " selected... " << endl;
                std::cout << "The coordinates of this Commander: (" << translateCoordinate(newCommander2->getCoordinate('X'), 'x', 'O') << ", " <<
                    translateCoordinate(newCommander2->getCoordinate('Y'), 'y', 'O') << ") " << endl;
                std::cout << endl;

                allCommanders[currentParticipantIndex][index].printCommanderStats();
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

    Participants* newParticipant = &participantsList[currentParticipantIndex];
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
            printCostsToTrainAnotherCommander(trainArmyCommanderCosts);
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

                if (failCommanderTraining == 'S') //create new commander
                {
                    std::cout << "Commander training successful " << endl;
                    std::cout << "Current commanders: " << newParticipant->howManyCommanders() + 1 << endl;
                    Participants* newParticipant = &participantsList[currentParticipantIndex];

                    CommanderProfile newCommander(1, getNewName(), newParticipant->howManyCommanders());
                    newCommander.changeCoordinates(newParticipant->getCapitalCoordinate('X'), newParticipant->getCapitalCoordinate('Y'));
                    allCommanders[currentParticipantIndex].push_back(newCommander);
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
    Participants* newParticipant = &participantsList[currentParticipantIndex];
    int commandersInCapital = (int)provincesMap[capitalX][capitalY].commandersPresentIndex.size();

    if (commandersInCapital == 0)
    {
        std::cout << "No commanders in capital, cannot deploy..." << endl;
    }
    else
    {
        deployCommanderDisplayInformation(commandersInCapital);

        char returnToMenu = 'N';
        vector <int> listOfCommandersIndex;
        vector <int> amountOfCommanders = { -1 };
        for (int x = 0; x < provincesMap[newParticipant->listOfProvincesX[0]][newParticipant->listOfProvincesY[0]].commandersPresentIndex.size(); x++)
        {
            int xCoordinate = newParticipant->listOfProvincesX[x];
            int yCoordinate = newParticipant->listOfProvincesY[x];
            listOfCommandersIndex.push_back(provincesMap[xCoordinate][yCoordinate].returnCommanderIndex(x));
            amountOfCommanders.push_back(x + 1);
        }
        do
        {
            int commanderLetterIdentifier = getInt("Enter the number identifier of the commander you want to deploy (enter '1' to go back to previous menu): ",
                amountOfCommanders, 1);
            std::cout << endl;

            if (commanderLetterIdentifier != 1)
            {
                int indexToSelect = commanderLetterIdentifier - 1;
                CommanderProfile*  newCommander3 = &allCommanders[currentParticipantIndex][indexToSelect];

                newCommander3->printCommanderStats();

                string confirmDeployCommanderString;
                int commanderIndex = provincesMap[capitalX][capitalY].returnCommanderIndex(indexToSelect);
                std::cout << "Deploy commander " << allCommanders[currentParticipantIndex][commanderIndex].getUnitName() << "? (Y/N) ";
                char confirmDeployCommanderChar = getChar("Replacement", "YN", 2);

                int participantIndex = 0; /*Fix this when developing AI*/
                int xThingyTwo = newCommander3->getCoordinate('X');
                int yThingyTwo = newCommander3->getCoordinate('Y');
                if (confirmDeployCommanderChar == 'Y')
                {
                    if (newCommander3->hasCommanderMoved() == 'N')
                    {
                        newCommander3->moveUnit();
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
    string commanderName = " ";

    Participants* newParticipant = &participantsList[currentParticipantIndex];

    std::cout << "The following commanders are in the capital: " << provincesMap[capitalX][capitalY].commandersPresentIndex.size() << endl;

    for (int a = 0; a < commandersInCapital; a++)
    {
        int commanderIndex = provincesMap[newParticipant->getCapitalCoordinate('X')][newParticipant->getCapitalCoordinate('Y')].commandersPresentIndex[a];
        commanderName = allCommanders[currentParticipantIndex][commanderIndex].getUnitName();
        //int commanderIndex = participantsList[currentParticipantIndex].findCommanderIndex(commanderName);
        std::cout << "Commander " << allCommanders[currentParticipantIndex][commanderIndex].getUnitName() << "; Level: " <<
            allCommanders[currentParticipantIndex][commanderIndex].getCommanderLevel() << endl;
    }
}

void ArmyDeploymentMA::printCostsToUpgradeACommander(int commanderUpgradeCosts[5], int indexOfCommander)
{
    Participants* newParticipant = &participantsList[currentParticipantIndex];
    std::cout << "The following is the cost to upgrade commander " << allCommanders[currentParticipantIndex][indexOfCommander].getUnitName() << endl;
    for (int x = 0; x < 5; x++)/*Cost of upgrade increases after each upgrade, cheaper than training a new one*/
    {
        commanderUpgradeCosts[x] = allCommanders[currentParticipantIndex][indexOfCommander].getCommanderLevel() * 5;
        commanderUpgradeCosts[x] *= initialResources[x];
        std::cout << provinceResourcesNames[x] << ": " << commanderUpgradeCosts[x] << endl;
    }
}

void ArmyDeploymentMA::printCostsToTrainAnotherCommander(int trainArmyCommanderCosts[5])
{
    std::cout << endl;
    std::cout << "The following is the cost to train another commander: " << endl;
    for (int x = 0; x < 5; x++) /*calculate and print costs to train another commander (more expensive than the last)*/
    {
        trainArmyCommanderCosts[x] = (int) allCommanders[currentParticipantIndex].size() * 10;
        trainArmyCommanderCosts[x] *= initialResources[x];
        std::cout << provinceResourcesNames[x] << ": " << trainArmyCommanderCosts[x] << endl;
    }
    std::cout << endl;

    cout << "The following are the resources currently in your capital: << endl;" << endl;
    provincesMap[participantsList[currentParticipantIndex].getCapitalCoordinate('X')]
        [participantsList[currentParticipantIndex].getCapitalCoordinate('Y')].printResources();
}