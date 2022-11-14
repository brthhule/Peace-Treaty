#include "otherFunctions.h"
#include "textFunctions.h"
#include "Provinces.h"
#include "CommanderProfile.h"
#include "AllUnits.h"
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>  
#include <ctime>
#include <chrono>
#include <thread>

#include <stdlib.h>
#include "AttackMA.h"
#include "Participants.h"

using namespace std;
extern vector<vector <Provinces>> provincesMap;
extern vector < vector <CommanderProfile>> allCommanders;
extern vector <Provinces> provincesCanSelect;
extern int provinceBuildingsProductionNumbers[6];
extern int continentSize;
extern int troopsCP[5];
extern vector <Participants> participantsList;
extern int currentParticipantIndex;



int calculatePlayerValues(int decision)
{
    switch (decision)
    {
    case 1:
    {
        int totalTroopsCP = 0;
        int amountOfTroops[5] = {};
        //findTotalTroopsCPFunction
        for (int x = 0; x < continentSize; x++)//find troops in provinces-- might be better to create a list of provinces per player? Don't
            //have to search through provinces that belong to other participants
        {
            for (int y = 0; y < continentSize; y++)
            {
                if (provincesMap[x][y].getBelongsToParticipant() == currentParticipantIndex)
                {
                    totalTroopsCP += provincesMap[x][y].getTotalCP();
                }
            }
        }
        for (int b = 0; b < participantsList[currentParticipantIndex].howManyCommanders(); b++)
        {

            totalTroopsCP += allCommanders[currentParticipantIndex][b].getTotalCP();
        }
        return totalTroopsCP;
        break;
    }
    case 2:
    {
        int totalTroopsLost = 0;
        for (int x : participantsList[currentParticipantIndex].playerTroopsLost)
        {
            totalTroopsLost += x;
        }
        return totalTroopsLost;
        break;
    }
    case 3:
        break;
    default:
        cout << "Something went wrong... " << endl;
        return -1;
        break;
    }
    cout << "Something went wrong" << endl;
    return -1;
}




void showMap()
{
    cout << "Map: " << endl;
    int thingy = continentSize;
    for (int x = 0; x < continentSize; x++)
    {
        //Y axis stuff
        if (thingy < 10)
        {
            cout << " " << thingy << "| ";
        }
        else
        {
            cout << thingy << "| ";
        }
        thingy--;
        //End y axis stuff

        for (int y = 0; y < continentSize; y++)
        {
            char letter = ' ';//Fix this later
            char identifierThingy = ' ';
            if (provincesMap[x][y].getBelongsToParticipant() == currentParticipantIndex)
            {
                std::cout << "\033[;34m";
                identifierThingy = 'H';
                if (provincesMap[x][y].isProvinceACapitalQuestion() == 'Y')
                {
                    letter = 'P';
                }
                else
                {
                    letter = 'p';
                }
            }
            else if (provincesMap[x][y].getBelongsToParticipant() != -1)
            {
                cout << "\033[;31m";
                identifierThingy = 'V';
                if (provincesMap[x][y].isProvinceACapitalQuestion() == 'Y')
                {
                    letter = 'E';
                }
                else
                {
                    letter = 'e';
                }
            }
            else
            {
                letter = '0';
            }
            if (provincesMap[x][y].commandersPresentIndex.size() == 0)
            {
                cout << letter << "   ";
            }
            else
            {
                if (provincesMap[x][y].commandersPresentIndex.size() <= 9)
                {
                    cout << letter << identifierThingy << provincesMap[x][y].commandersPresentIndex.size() << " ";
                }
                else
                {
                    cout << letter << identifierThingy << "* ";
                }
            }
            cout << "\033[;0m";
        }
        cout << endl;
    }






    //X axis stuff
    cout << "    ";
    for (int a = 0; a < continentSize - 1; a++)
    {
        cout << "----";
    }
    cout << "-";
    cout << endl;
    cout << "    ";
    for (int a = 0; a < continentSize; a++)
    {
        if (a < 8)
        {
            cout << a + 1 << "   ";
        }
        else
            cout << a + 1 << "  ";
    }
    cout << endl;
    cout << endl;
}

void updateprovinceResources()
{
    for (int x = 0; x < continentSize; x++)
    {
        for (int y = 0; y < continentSize; y++)
        {
            for (int z = 0; z < 5; z++)
            {
                provincesMap[x][y].updateBuildingsProduction();
                provincesMap[x][y].updateProvinceResources();
            }

        }
    }
}

int getInt(string textToDisplay, vector <int> acceptableValues, int caseInstance)
{
    string userInput;
    if (caseInstance == 1)
    {
        std::cout << textToDisplay;
    }
    cout << "\033[31m";
    std::getline(cin, userInput);
    cout << "\033[0m";
    return checkInt(acceptableValues, userInput);
}
int checkInt(vector<int>& acceptableValuesTwo, string input)
{
    vector <string> acceptableValuesOne;
    string foo = " ";
    for (int a = 0; a < acceptableValuesTwo.size(); a++)
    {
        foo = to_string(acceptableValuesTwo[a]);
        acceptableValuesOne.push_back(foo);
    }

    char repeat = 'Y';
    do
    {
        repeat = 'N';
        for (int x = 0; x < acceptableValuesOne.size(); x++)
        {
            if (input == acceptableValuesOne[x])
            {
                repeat = 'N';
                return acceptableValuesTwo[x];
            }
        }
        repeat = 'Y';
        std::cout << endl;
        std::cout << "Invalid character entered. Please try again." << endl;
        std::cout << "Please enter a valid number: ";
        cout << "\033[31m";
        std::getline(cin, input);
        cout << "\033[0m";

    } while (repeat == 'Y');
    return -1;
}
char getChar(string textToDisplay, string acceptableValues, int caseInstance)
{
    string userInput;
    if (caseInstance == 1)
    {
        std::cout << textToDisplay;
    }
    cout << "\033[31m";
    std::getline(cin, userInput);
    cout << "\033[0m";
    return checkChar(acceptableValues, userInput);
}
char checkChar(string stringAV, string input)
{
    vector<char> acceptableValuesOne; /*Uppercase*/
    char inputTwo = ' ';

    for (int x = 0; x < stringAV.length(); x++)
    {
        acceptableValuesOne.push_back(stringAV.at(x));
    }

    char goodToGo = 'G';
    string character;
    do
    {
        goodToGo = 'G';
        if (input.length() == 1)
        {
            inputTwo = toupper(input.at(0));
            for (int x = 0; x < acceptableValuesOne.size(); x++)
            {
                if (inputTwo == acceptableValuesOne[x])
                {
                    goodToGo = 'G';
                    return acceptableValuesOne[x];
                }
            }
        }
        goodToGo = 'B';

        std::cout << endl;
        std::cout << "Invalid character entered. Please try again. " << endl;
        std::cout << "Please enter a valid character: ";
        cout << "\033[31m";
        std::getline(cin, input);
        cout << "\033[0m";

    } while (goodToGo == 'B');
    return '1'; /*added this bc the debugger said that not all control paths return a value*/
}

void findTotalPlayerUnits(int totalPlayerUnits[5])
{
    for (int x = 0; x < 5; x++)
    {
        totalPlayerUnits[x] = 0;
    }
    for (int x = 0; x < continentSize; x++)
    {
        for (int y = 0; y < continentSize; y++)
        {
            if (provincesMap[x][y].getBelongsToParticipant() == currentParticipantIndex)
            {
                for (int a = 0; a < 5; a++)
                {
                    totalPlayerUnits[a] += provincesMap[x][y].getTroopsPresent(a);
                }
            }
        }
    }
    for (int b = 0; b < participantsList[currentParticipantIndex].howManyCommanders(); b++)
    {
        for (int c = 0; c < 5; c++)
        {
            totalPlayerUnits[c] += allCommanders[currentParticipantIndex][b].getTroopsPresent(c);
        }
    }
}

string getNewName()
{
    //cout << "getNewName" << endl;
    Participants* newParticipant = &participantsList[currentParticipantIndex];
    string newName = " ";
    char repeatGetName = 'N';

    //Check to make sure that the name isn't used by any other units the participant has
    do
    {
        repeatGetName = 'N';
        newName = createRandomName();
        //cout << "Check provinces" << endl;
        for (int x = 0; x < newParticipant->howManyProvinces(); x++) //If any provinces of the participant have the name
        {
            Provinces* newProvince = &provincesMap[newParticipant->listOfProvincesX[x]][newParticipant->listOfProvincesY[x]];
            if (newName == newProvince->getUnitName())
            {
                repeatGetName = 'Y';
            }
        }
        //cout << "Check commanders" << endl;
        for (int x = 0; x < newParticipant->howManyCommanders(); x++)//If any commanders have the name
        {
            CommanderProfile* newCommander = &allCommanders[currentParticipantIndex][x];
            if (newName == newCommander->getUnitName())
            {
                repeatGetName = 'Y';
            }
        }
        //cout << "Compare to participant kingdom name" << endl;
        //cout << "Kingdom name: " << newParticipant -> getKingdomName () << endl;
        if (newParticipant->getKingdomName() == newName)
        {
            repeatGetName = 'Y';
        }
    } while (repeatGetName == 'Y');

    return newName;
}
string createRandomName()
{
    //cout << "Create random name" << endl;
    string name = "";
    int randomNumber = 0;
    char characterThingy = ' ';
    for (int x = 0; x < 4; x++)
    {
        if (x % 2 == 0)//if even
        {
            randomNumber = rand() % 21;
            characterThingy = findConsonant(randomNumber);
        }
        else if (x % 2 == 1)//if odd
        {
            randomNumber = rand() % 5;
            characterThingy = findVowel(randomNumber);
        }
        if (x == 0)
        {
            characterThingy = toupper(characterThingy);
        }
        name += characterThingy;
    }
    return name;
}
char findConsonant(int randomNumber)
{
    char characterThingy = ' ';
    switch (randomNumber)
    {
    case 1:
        characterThingy = 'b';
        break;
    case 2:
        characterThingy = 'c';
        break;
    case 3:
        characterThingy = 'd';
        break;
    case 4:
        characterThingy = 'f';
        break;
    case 5:
        characterThingy = 'g';
        break;
    case 6:
        characterThingy = 'h';
        break;
    case 7:
        characterThingy = 'j';
        break;
    case 8:
        characterThingy = 'k';
        break;
    case 9:
        characterThingy = 'l';
        break;
    case 10:
        characterThingy = 'm';
        break;
    case 11:
        characterThingy = 'n';
        break;
    case 12:
        characterThingy = 'p';
        break;
    case 13:
        characterThingy = 'q';
        break;
    case 14:
        characterThingy = 'r';
        break;
    case 15:
        characterThingy = 's';
        break;
    case 16:
        characterThingy = 't';
        break;
    case 17:
        characterThingy = 'v';
        break;
    case 18:
        characterThingy = 'w';
        break;
    case 19:
        characterThingy = 'x';
        break;
    case 20:
        characterThingy = 'y';
        break;
    case 21:
        characterThingy = 'z';
        break;
    }

    return characterThingy;
}
char findVowel(int randomNumber)
{
    char characterThingy = ' ';
    switch (randomNumber)
    {
    case 1:
        characterThingy = 'a';
        break;
    case 2:
        characterThingy = 'e';
        break;
    case 3:
        characterThingy = 'i';
        break;
    case 4:
        characterThingy = 'o';
        break;
    case 5:
        characterThingy = 'u';
        break;
    }
    return characterThingy;
}

void createMap()
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
}


int findAmountOfEnemyProvinces()
{
    int amountOfProvinces = 0;
    for (int x = 1; x < participantsList.size(); x++)
    {
        amountOfProvinces += participantsList[x].howManyProvinces();
    }
    return amountOfProvinces;
}

void clearScreen()
{
    cout << "\033[32m";
    std::cout << "Clearing screen. " << endl;
    cout << "\033[0m";
    chrono::seconds dura(1);
    this_thread::sleep_for(dura);
    system("cls"); /*Windows only*/
    //system("clear"); /*Non-Windows*/
}