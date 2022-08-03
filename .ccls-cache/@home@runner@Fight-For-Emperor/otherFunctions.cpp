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
extern vector <Provinces> provincesCanSelect;
extern char mapMoveUnit[15][15];
extern int provinceBuildingsProductionNumbers[6];
extern int continentSize;
extern int playerTroopsLost[5];
extern int scoutLogTurnLevel[15][15][2];
extern int troopsCP[5];
extern vector <Participants> participantsList;
extern int actualParticipantIndex;


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
                switch (provincesMap[x][y].getProvinceIdentifier())
                {
                case 'P':
                case 'p':
                    totalTroopsCP += provincesMap[x][y].getTotalCP();
                    break;
                }
            }
        }
        for (int b = 0; b < participantsList[actualParticipantIndex].howManyCommanders(); b++)
        {
            for (int c = 0; c < 5; c++)
            {
                totalTroopsCP += participantsList[actualParticipantIndex].returnCommander(b)->getTotalCP();
            }
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
int findCommanderIndex(char commanderChar)
{
    for (int x = 0; x < participantsList[actualParticipantIndex].howManyCommanders(); x++) /*find index of chosen commander unit*/
    {
        if (commanderChar == participantsList[actualParticipantIndex].returnCommander(x)->getCommanderIdentifier())
        {
            return x;
        }
    }
    return -1;//if something goes wrong
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
    std::getline(cin, actualXString);
    XYCoordinates[0] = checkInt(actualCoordinatesAVTwo, actualXString);
    if (XYCoordinates[0] != -1)
    {
        std::cout << "Enter the y coordinate " << phrase << " (Enter '-1' to go back to previous menu) : ";
        std::getline(cin, actualYString);
        XYCoordinates[1] = checkInt(actualCoordinatesAVTwo, actualYString);
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
    /*HANDLE console_color; //Windows only
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);*/
    int thingy = continentSize;
    for (int x = 0; x < continentSize; x++)
    {
        if (thingy < 10)
            cout << " " << thingy << "| ";
        else
            cout << thingy << "| ";
        thingy--;
        for (int y = 0; y < continentSize; y++)
        {
            char letter = provincesMap[x][y].getProvinceIdentifier();
            char identifierThingy = ' ';
            switch (letter)
            {
            case 'E':
            case 'e':
                cout << "\033[;31m";
                identifierThingy = 'V';
                break;
            case 'P':
            case 'p':
                std::cout << "\033[;34m";
                identifierThingy = 'H';
                break;
            }
            if (provincesMap[x][y].commandersPresent == 0)
            {
                cout << letter << "   ";
            }
            else
            {
                if (provincesMap[x][y].commandersPresent <= 9)
                {
                    cout << letter << identifierThingy << provincesMap[x][y].commandersPresent << " ";
                }
                else
                {
                    cout << letter << identifierThingy << "* ";
                }
            }
            //SetConsoleTextAttribute(console_color, 15); //WO
            cout << "\033[;0m"; //NW
        }
        cout << endl;
    }
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




void moveUnit(int xCoordinate, int yCoordinate, int participantIndex, int commanderIndex)
{
    if (participantsList[actualParticipantIndex].returnCommander(commanderIndex)->hasCommanderMoved() == 'N')
    {

        std::cout << "The coordinates of this unit are: ";
        std::cout << "(" << translateCoordinate(xCoordinate, 'y', 'O') << ", " << translateCoordinate(yCoordinate, 'x', 'O') << ") " << endl;
        std::cout << endl;
        std::cout << "You can only move this unit to one of the provinces adjacent to the province it is in. " << endl;

        vector<int> XYCoordinates = getCoordinates(2);
        int moveToXTwo = XYCoordinates[0];
        int moveToYTwo = XYCoordinates[1];
        int moveToX = translateCoordinate(moveToXTwo, 'x', 'O');
        int moveToY = translateCoordinate(moveToYTwo, 'y', 'O');
        provincesCanSelect.clear(); /*reset coordinates of provinces player can unit move to*/

        for (int x = -1; x <= 1; x++) /*Identify all the provinces that the player can move a unit to*/
        {
            for (int y = -1; y <= 1; y++)
            {
                if (x >= 0 && x < continentSize)
                    if (y >= 0 && y < continentSize)
                        mapMoveUnit[x + moveToXTwo][y + moveToYTwo] = 'Y';
            }
        }

        string confirmMove;
        char attackScenario = 'P';/*P is for peace, A is for attack*/
        if (mapMoveUnit[moveToXTwo][moveToYTwo] == 'Y')
        {
            switch (provincesMap[moveToX][moveToY].getProvinceIdentifier())
            {
            case 'E':
            case 'e':
            case 'V':
            case '0':
                attackScenario = 'A';
                std::cout << "This province is occupied by the enemy. Moving here will cause your unit to attack any enemy units stationed at this province." << endl;
                break;
            }
            std::cout << "Confirm moving your unit to (" << moveToX << ", " << moveToY << ")? (Y/N) ";

            if (getChar("Replacement thingy", "YN", 2) == 'Y')
            {
                if (attackScenario == 'P')
                {
                    participantsList[actualParticipantIndex].returnCommander(commanderIndex)->changeCommanderCoordinates(moveToXTwo, moveToYTwo);
                    if (provincesMap[xCoordinate][yCoordinate].getProvinceIdentifier() != 'P')
                    {
                        provincesMap[xCoordinate][yCoordinate].setProvinceIdentifier('p');
                    }
                    provincesMap[moveToXTwo][moveToYTwo].setProvinceIdentifier('H');
                }
                else
                {
                    AttackMA newAttackMA(xCoordinate, yCoordinate, moveToXTwo, moveToYTwo, commanderIndex, participantIndex);
                    newAttackMA.playerAttack();
                }
            }
        }
    }
    else
    {
        std::cout << "This unit has already moved this turn. Please pick another unit. " << endl;
    }
    std::cout << "Returning to previous menu... " << endl << endl;
}/* unfinished*/

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
            switch (provincesMap[x][y].getProvinceIdentifier())
            {
            case 'P':
            case 'p':
                for (int a = 0; a < 5; a++)
                {
                    totalPlayerUnits[a] += provincesMap[x][y].getTroopsPresent(a);
                }
            }
        }
    }
    for (int b = 0; b < participantsList[actualParticipantIndex].howManyCommanders(); b++)
    {
        for (int c = 0; c < 5; c++)
        {
            totalPlayerUnits[c] += participantsList[actualParticipantIndex].returnCommander(b)->getTroopsPresent(c);
        }
    }
}