#include "otherFunctions.h"
#include "textFunctions.h"
#include "Provinces.h"
#include "CommanderProfile.h"
#include "AllUnits.h"
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
//#include <windows.h> //WO
#include <stdlib.h>
#include "AttackMA.h"
#include "Participants.h"

/*How to use colors: */
/*On Linux, you can change the current foreground and background color by writing special character sequences into the output. Write the ESC escape character (octal "\033", hex \x1b), followed by an opening square bracket [. The color definition will follow next, termniated by a lowercase m.

The color definition is a series of numbers, separated by semicolons. In order to make the text color red (number 31),
you can write "\033[31m" which will make any following output red. If you want yellow text (33) on blue background (44),
you write "\033[31;44m". To reset everything back to the default colors, you write "\033[0m".


         foreground background
black        30         40
red          31         41
green        32         42
yellow       33         43
blue         34         44
magenta      35         45
cyan         36         46
white        37         47
Additionally, you can use these:

reset             0  (everything back to normal)
bold/bright       1  (often a brighter shade of the same colour)
underline         4
inverse           7  (swap foreground and background colours)
bold/bright off  21
underline off    24
inverse off      27*/

using namespace std;
extern vector<vector <Provinces>> provincesMap;
extern vector < vector <CommanderProfile>> allCommanders;
extern vector <Provinces> provincesCanSelect;
extern char mapMoveUnit[15][15];
extern int provinceBuildingsProductionNumbers[6];
extern int continentSize;
extern int playerTroopsLost[5];
extern int scoutLogTurnLevel[15][15][2];
extern int troopsCP[5];
extern vector <Participants> participantsList;
extern int currentParticipantIndex;


int translateCoordinate(int coordinate, char indicator, char whichWay)
{
    /*replacement = xCoordinate;
    xCoordinate = translateCoordinate(yCoordinate, 'y', 'I');
    yCoordinate = translateCoordinate (replacement, 'x', 'I');*/
    int translation = 0;
    switch (whichWay)
    {
    case 'I':
        switch (indicator)
        {
        case 'x':
            translation = coordinate - 1;
            break;

        case 'y':
            translation = continentSize - coordinate;
            break;
        }
        break;
    case 'O':
        switch (indicator)
        {
        case 'x':
            translation = coordinate + 1;
            break;
        case 'y':
            translation = continentSize - coordinate;
            translation = abs(translation);
            break;
        }
        break;
    }
    return translation;
}
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
        for (int x : playerTroopsLost)
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
string convertPCIToString(vector <char> playerCommanderIdentifiers)
{
    string convertedString;
    for (char conversion : playerCommanderIdentifiers)
    {
        convertedString.push_back(conversion);
    }
    return convertedString;
}
vector<int> getCoordinates(int identifier)/*Might have have to fix this (check if the coordinate stuff is right)*/
{
    vector <int> XYCoordinates;/*[0] = x coordinate, [1] = y coordinate*/
    string actualXString;
    string actualYString;

    vector<int> actualCoordinatesAVTwo;

    for (int x = 1; x <= continentSize; x++)
    {
        actualCoordinatesAVTwo.push_back(x);
    }
    actualCoordinatesAVTwo.push_back(-1);
    string phrase;

    switch (identifier)
    {
    case 1:
        phrase = "of the province you want to select";
        break;
    case 2:
        phrase = "of the province you want to move to";
        break;
    case 3:
        phrase = "of the army you want to use to attack the target with";
    }

    std::cout << "Enter the x coordinate " << phrase << " (Enter '-1' to go back to previous menu) : ";
    XYCoordinates[0] = getInt("Replacement", actualCoordinatesAVTwo, 2);
    if (XYCoordinates[0] != -1)
    {
        std::cout << "Enter the y coordinate " << phrase << " (Enter '-1' to go back to previous menu) : ";
        XYCoordinates[1] = getInt("Replacement", actualCoordinatesAVTwo, 2);
        std::cout << endl;

        if (XYCoordinates[1] != 1)
        {
            int replacement = XYCoordinates[0];
            XYCoordinates[0] = translateCoordinate(XYCoordinates[1], 'y', 'I');
            XYCoordinates[1] = translateCoordinate(replacement, 'x', 'I');
        }
    }
    return XYCoordinates;
}//Can make this an array
vector<int> getTrainBuildCoordinates()
{
    showMap();
    printListOfProvinces();

    return getCoordinates(1);
}

void showMap()
{

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
    std::getline(cin, userInput);
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
        std::getline(cin, input);

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
    std::getline(cin, userInput);
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
        std::getline(cin, input);

    } while (goodToGo == 'B');
    return '1'; /*added this bc the debugger said that not all control paths return a value*/
}

void findTotalPlayerUnits(int totalPlayerUnits[5])
{
    for (int x = 0; x < sizeof(totalPlayerUnits) / sizeof(int); x++)
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
    Participants* newParticipant = &participantsList[currentParticipantIndex];
    string newName = " ";  
    char repeatGetName = 'N';

    //Check to make sure that the name isn't used by any other units the participant has
    do
    {
        repeatGetName = 'N';
        newName = createRandomName();
        for (int x = 0; x < newParticipant->howManyProvinces(); x++)
        {
            Provinces* newProvince = &provincesMap[newParticipant->listOfProvincesX[x]][newParticipant->listOfProvincesY[x]];
            if (newName == newProvince -> getUnitName())
            {
                repeatGetName = 'Y';
            }
        }

        for (int x = 0; x < newParticipant->howManyCommanders(); x++)
        {
            CommanderProfile* newCommander = &allCommanders[currentParticipantIndex][x];
            if (newName == newCommander->getUnitName())
            {
                repeatGetName = 'N';
            }
        }
    } while (repeatGetName == 'Y');

    return newName;
}
string createRandomName()
{
    string name = "";
    int randomNumber = 0;
    char characterThingy = ' ';
    srand(time(0));
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