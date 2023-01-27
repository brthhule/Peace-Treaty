#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include "Provinces.h"
#include "textFunctions.h"
#include "otherFunctions.h"
#include "coordinateFunctions.h"


using namespace std;
extern vector <vector <Provinces>> provincesMap;
extern vector <Participants> participantsList;
extern string provinceResourcesNames[5];
extern string buildingNames[6];
extern string troopNames[5];
extern int initialResources[5];
extern int continentSize;
extern int currentParticipantIndex;

void synopsis()
{
    cout << "- Welcome to Fight For Emperor" << endl;
    cout << "- In a large continent, filled with various kingdoms, you are a monarch seeking to unit the land; you will defeat the other kingdoms and become emperorer." << endl;
    cout << "- Develop buildings, train troops, and use logistics and battle strategies to conquer enemy provinces." << endl;
    cout << "- Although players cannot save their complete data, a portion of the land that they gained in the previous game (as well as the amount of resources available) will be available through a code " << endl << endl;
}

void viewAllStatsFunction()
{
    string literallyAnyRandomCharacter;
    std::cout << "\033[;34m";//NW
    for (int x = 0; x < 5; x++)
    {
        std::cout << troopNames[x] << " lost: " << participantsList[currentParticipantIndex].playerTroopsLost[x] << endl;
    }
    std::cout << "Total troops lost: " << calculatePlayerValues(2) << endl << endl;
    std::cout << "\033[;0m";//NW

    cout << "Enter any character to go back to the Main menu: ";
    cout << "\033[31m";
    getline(cin, literallyAnyRandomCharacter);
    cout << "\033[0m";
}

void casualtyReport(int deadTroops[5], int injuredTroops[5])
{
    std::cout << endl;
    std::cout << "Troops casualties: " << endl;
    for (int x = 0; x < 5; x++) /*print out deaths*/
    {
        std::cout << troopNames[x] << " dead: " << deadTroops[x] << endl;
    }
    std::cout << endl;
    for (int x = 0; x < 5; x++) /*print out deaths*/
    {
        std::cout << troopNames[x] << " injured: " << injuredTroops[x] << endl;
    }
    std::cout << endl;
}

void printListOfProvinces()
{
    std::cout << "Here is a list of your provinces: " << endl;
    int x;
    int y;
    for (int a = 0; a < continentSize; a++)
    {
        for (int b = 0; b < continentSize; b++)
        {
            if (provincesMap[a][b].getBelongsToParticipant() == currentParticipantIndex)
            {
                x = translateCoordinate(b, 'x', 'O');
                y = translateCoordinate(a, 'y', 'O');
                std::cout << "(" << x << ", " << y << ") " << endl;
            }
        }
    }
    std::cout << endl;
}


char listOfActions(int identifier) //print out what actions a player can do
{
    string stringToSend = " ";
    /*cout << "- ()" << endl;*/
    /*HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE); //WO
    SetConsoleTextAttribute(console_color, 12);*/
    cout << "\033[;31m---------- List of Operations: ----------" << endl;
    switch (identifier)
    {
    case 1: /*selectEnemyAction*/
    {
        cout << "- Attack this province (A) " << endl;
        cout << "- Scout this province (S) " << endl;
        break;
    }
    case 2: /*playerUnitAction*/
    {
        cout << "- Move this unit (P)" << endl;
        stringToSend = "P";
        break;
    }
    case 3: /*introduction*/
    {
        cout << "- Start a new conquest (S)" << endl;
        cout << "- Resume a previous conquest (R)" << endl;
        stringToSend = "SR";
        break;
    }
    case 4: /*playerAction*/
    {
        std::cout << "- Buildings (B) " << endl;
        std::cout << "- Training (T) " << endl;
        std::cout << "- Stats (S) " << endl;
        std::cout << "- Select Unit (U) " << endl;
        std::cout << "- Deployment (D) " << endl;
        std::cout << "- Next Turn (N)" << endl;
        std::cout << "- Pause (P) " << endl;
        stringToSend = "BTSUDNP";
        break;
    }
    case 5: /*armyDeployment*/
    {
        std::cout << "- Train a commander (T) " << endl;
        std::cout << "- Upgrade a commander (U) " << endl;
        std::cout << "- View army overview (V) " << endl;
        std::cout << "- Deploy a commander (D) " << endl;
        stringToSend = "TUVDHM";
        break;
    }
    case 6: /*TrainMAFunction*/
    {
        std::cout << "- Proceed with training (P) " << endl;
        std::cout << "- See the amount of resources in this province (S) " << endl;
        stringToSend = "PSM";
        break;
    }
    case 7: /*playerBuildFunction*/
    {
        std::cout << "- Upgrade a building (U) " << endl;
        stringToSend = "UM";
        break;
    }
    case 8: /*viewPlayerMap*/
    {
        std::cout << "- Pick a province (P) " << endl;
        stringToSend = "PM";
        break;
    }
    case 9: /*selectPlayerProvince*/
    {
        std::cout << "- Build infrastructure (B) " << endl;
        std::cout << "- Train Troops (T) " << endl;
        stringToSend = "BTM";
        break;
    }
    case 10: /*selectEnemyProvince*/
    {
        std::cout << "- Attack this province (A) " << endl;
        std::cout << "- Scout this province (S) " << endl;
        std::cout << "- View the scout log (V) " << endl;
        stringToSend = "ASVM";
        break;
    }
    case 11: /*scoutLogFunction*/
    {
        string SLFReports [3] = {"garrison", "resource", "building"};
        for (int x = 0; x < 3; x++){std::cout << "- View the " << SLFReports << " report for this province (" << toupper(SLFReports[x].at(0)) << ") " << endl;}
        stringToSend = "GRBM";
        break;
    }
    }
    std::cout << "-------------- End List: ---------------- \033[;0m" << endl << endl;
    
    std::cout << "- Return to the previous menu (M) " << endl;
    //SetConsoleTextAttribute(console_color, 15); //WO
    if (identifier != 3 && identifier != 4)
    {
        stringToSend += "MH";
    }
    return getChar("Enter the letter of the action you want to complete (enter 'H' to see help to know what to do): ", stringToSend, 1);
}

void listOfHelp (int identifier)
{
    cout << "\033[;34m ---------- Begin Help ----------" << endl;
    switch (identifier)
    {
        case 2:
        {
            cout << "- You can select to move one of your army units. Only army units deployed with an army commander can move (these are sent out via your capital). " << endl;
            cout << "- Garrisons cannot move, but they can be absorved into army units that are in the same province as an army. " << endl << endl;
            cout << "- If you move an army unit to an empty province, the army unit takes over that province without resistance. " << endl;
            cout << "- If you move an army unit to an enemy province, the army unit will attack the enemy province. The army with the greater combat power will win, but the amount of losses and the types of troops lost will vary depending on troop composition. " << endl;
            cout << "- If you move an army unit to one of your provinces, you can absorb some of the garrison troops into the army as long as the army capacity is not exceeded. You can also merge troops from two or more different armies so long as they're in the same province, but there cannot be two army commanders in one army. " << endl;
            cout << endl;
            cout << "You can increase the size of an army by increasing the level of the army's commander (this can only be done when the army commander and their army are in the capital-- player action 'player deployment'). " << endl;
            break;
        }
        case 3:
        {
            cout << "Start a new conquest (S): " << endl;
            cout << "- Start a new game" << endl;
            cout << "Resume a previous conquest (R): " << endl;
            cout << "- Enter a code/text file to import a game/generate a game with information from a previous play through" << endl;
            break;
        }
        case 4: //playerActionHelp
        {
            cout << "Build infrastructure (B): " << endl;
            cout << "- Select one of your provincesand build or upgrade one or several of the buildings in the province (Farm, Lumber Mill, Quarry, Mine, Church, and Barracks) " << endl << endl;
        
            cout << "Train troops (T): " << endl;
            cout << "- Select one of your provinces and train troops " << endl;
            cout << "- The tier troop you can train depends on the level of the barracks in this province" << endl;
            cout << "- Your capital province automatically starts with a barracks level of 1. You can upgrade a province's barracks through the build infrastructure action. " << endl << endl;
        
            cout << "View your stats (V): " << endl;
            cout << "- See your overall stats, including the total amount of resourcesand troops across all your provinces " << endl;
            cout << "- You can see the specific stats of each of your provinces through the view map action. " << endl << endl;
        
            cout << "View the map (M): " << endl;
            cout << "- See a map of the continent. Help for the map is available in the map section. " << endl;
            cout << "- Through the map, you can see the specific stats of each of your province(such as resources and troops available in the province). " << endl;
            cout << "- You can also scoutand attack enemy provinces through this action. " << endl << endl;
        
            cout << "View army deployment (A): " << endl;
            cout << "- Train army commanders here. The amount of army commanders you can have corresponds to the size of the continent. " << endl;
            cout << "- Through this action, you can also see the coordinates of each of your armiesand their specific stats. " << endl;
            cout << "- If an army is totally defeated, its army commander will dieand a new one will have to be trained " << endl << endl;
        
            cout << "Go to the next turn (G): " << endl;
            cout << "- This a turn - based game.You can scout enemy provinces, train troops, view your stats, and build infrastructure as much as you'd like. " << endl;
            cout << "- However, you can only get new resources by going to the next turn, and each of your armies can only move once per turn. " << endl << endl;
        
            cout << "Pause game (P): " << endl;
            cout << "- End the game and get a code to play again at another time. " << endl;
            break;
        }
        case 5:
        {
            cout << "Train a commander (T): " << endl;
            cout << "- The price of training a commander increases as the amount of commanders you have increases. You start off with one commander" << endl;
            //cout << "- The max limit of commanders you can train: " << maxAmountOfCommanders << endl << endl;
        
            cout << "Upgrade a commander (U): " << endl;
            cout << "- The price of upgrading a commander increases as the level of the commander increases" << endl;
            cout << "- There is no cap on how much you can upgrade a commander" << endl;
            cout << "- The greater the level of a commander, the more troops they can lead in their army (5 units per level) " << endl << endl;
        
            cout << "View army overview (V): " << endl;
            cout << "- See all your armies (their coordinates and their stats)" << endl << endl;
        
            cout << "Deploy a commander (D): " << endl;
            cout << "- Move commanders out of the capital and onto the map" << endl;
            break;
        }
        case 8:
        {
            cout << "On the map, each coordinate is a province that containes a type of unit (identified by a symbol). Here is a list of what each symbol on the map: " << endl << endl;
            cout << "P) Your capital province " << endl;
            cout << "p) One of your provinces " << endl;
            cout << "E) Your enemy's capital province " << endl;
            cout << "e) One of your eneny's provinces " << endl;
            cout << "H) One of your army units " << endl;
            cout << "V) One of your enemy's army units " << endl;
            cout << endl;
            cout << "If there are two letters in one province, that means that there are two units there-- if a province has PH, that means the player capital province and a commander unit are there. The number next to the letter indicates how many commander units are in the province" << endl << endl;
            cout << "Enter the x and y coordinates of the province you want to select. Depending on the type of province, you can build infrastructure, train troops, move armies, or attack armies. " << endl;
            cout << "------------ This is the end of the Help message ------------" << endl;
            break;
        }
        case 12: //upgradeBuildingsHelp
        {
            //finish this
            break;
        }
    }
    std::cout << "-------------- End Help ---------------- \033[;0m" << endl << endl;
    cout << "Enter 'R' to return to the menu: ";
    cout << ""; //NW
}