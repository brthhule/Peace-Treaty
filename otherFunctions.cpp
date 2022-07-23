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
extern vector<vector <Provinces>> provincesList;
extern vector <vector <char>> commanderIdentifiers;
extern vector <vector <char>> commanderIdentifiersList;
extern vector <vector <CommanderProfile>> commandersList;
extern vector <Provinces> provincesCanSelect;
extern char mapMoveUnit[15][15];
extern char generalCommanderIdentifiers[26];



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
        for (int x = 0; x < 5; x++)
        {
            totalTroopsCP += totalTroops[x] * troopsCP[x];
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
        break;
    }
    cout << "Something went wrong" << endl;
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

string convertPCIToString(vector <char> playerCommanderIdentifiers)
{
    string convertedString;
    for (char conversion : playerCommanderIdentifiers)
    {
        convertedString.push_back(conversion);
    }
    return convertedString;
}

int findCommanderIndex(char commanderChar, string listOfCommanders)
{
    for (int x = 0; x < listOfCommanders.size() && x >= 0; x++) /*find index of chosen commander unit*/
    {
        if (commanderChar == listOfCommanders.at(x))
        {
            return x;
        }
    }
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
            char letter = provincesList[x][y].getProvinceIdentifier();
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
            if (provincesList[x][y].commandersPresent == 0)
            {
                cout << letter << "   ";
            }
            else
            {
                if (provincesList[x][y].commandersPresent <= 9)
                {
                    cout << letter << identifierThingy << provincesList[x][y].commandersPresent << " ";
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

void updateCommanderIdentifiers(int participantIndex)
{
    commanderIdentifiersList[participantIndex].erase(commanderIdentifiersList[participantIndex].begin()); /*deletes the assigned letter identifier from the letter identifier list so
                    it isn't repeated*/
    if (commanderIdentifiersList[participantIndex].size() == 0) /*if the lesster identifier list is empty, reset it*/
    {
        for (int x = 0; x < sizeof(generalCommanderIdentifiers); x++)
        {
            commanderIdentifiersList[participantIndex].push_back(generalCommanderIdentifiers[x]);
        }
        for (int x = 0; x < commanderIdentifiersList[participantIndex].size(); x++) /* delete any existing commander identifiers from resetted identifier
            list so it isn't used again*/
        {
            for (int y = 0; y < commanderIdentifiersList[participantIndex].size(); y++)/*This finds the index of the element that needs to be deleted. Potential
"fix this": modify it such that it searches for the element to delete by searching for the char rather than scanning for the index-- if element is
equal to this identifier, this one, or this one, remove it; go through playerCommanderIdentifiersList like this*/
            {
                if (commanderIdentifiersList[participantIndex][y] == commanderIdentifiers[participantIndex][x])
                {
                    commanderIdentifiersList[participantIndex].erase(commanderIdentifiersList[participantIndex].begin() + y);
                    y--;
                }
            }
        }
    }
}




void moveUnit(int xCoordinate, int yCoordinate, int participantIndex, int commanderIndex)
{
    if (commandersList[participantIndex][commanderIndex].hasCommanderMoved() == 'N')
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
            switch (provincesList[moveToX][moveToY].getProvinceIdentifier())
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

            if (getChar(NULL, "YN", 2) == 'Y')
            {
                if (attackScenario == 'P')
                {
                    commandersList[participantIndex][commanderIndex].changeCommanderCoordinates(moveToXTwo, moveToYTwo);
                    if (provincesList[xCoordinate][yCoordinate].getProvinceIdentifier() != 'P')
                    {
                        provincesList[xCoordinate][yCoordinate].setProvinceIdentifier('p');
                    }
                    provincesList[moveToXTwo][moveToYTwo].setProvinceIdentifier('H');
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
