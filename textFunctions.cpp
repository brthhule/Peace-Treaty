#include "textFunctions.h"
#include "otherFunctions.h"
#include <iostream>
#include <string.h>
#include <string>
//#include <windows.h> //WO
#include <stdlib.h>
#include "Provinces.h"

using namespace std;
extern vector <vector <Provinces>> provincesList;
extern string provinceResourcesNames[5];
extern string buildingNames[6];
extern string troopNames[5];
extern int playerTroopsLost[5];
extern int initialResources[5];
extern int continentSize;

void synopsis()
{
    cout << "- Welcome to Fight For Emperor" << endl;
    cout << "- In a large continent, filled with various kingdoms, you are a monarch vying for the status of emporer." << endl;
    cout << "- In a distant land, in a distant world, in a distant reality, there lies a land run by evil. In this solo play adventure, work to defeat those enemies that roam the land and unify the now broken empire. Expand your kingdom and rule the world!" << endl;
    cout << "- Build buildings, develop research, and train troops to conquer foreign lands and become the mightiest Emperor." << endl;
    cout << "- Although players cannot save their complete data, a portion of the land that they gained in the previous game (as well as the amount of resources available) will be available (through a code) " << endl << endl;
}

void playerUnitActionHelp()
{
    std::cout << "\033[;34m"; //NW
    cout << "---------- This is the beginning of the Help message ----------" << endl;
    cout << "- You can select to move one of your army units. Only army units deployed with an army commander can move (these are sent out via your capital). " << endl;
    cout << "- Garrisons cannot move, but they can be absorved into army units that are in the same province as an army. " << endl << endl;
    cout << "- If you move an army unit to an empty province, the army unit takes over that province without resistance. " << endl;
    cout << "- If you move an army unit to an enemy province, the army unit will attack the enemy province. The army with the greater combat power will win, but the amount of losses and the types of troops lost will vary depending on troop composition. " << endl;
    cout << "- If you move an army unit to one of your provinces, you can absorb some of the garrison troops into the army as long as the army capacity is not exceeded. You can also merge troops from two or more different armies so long as they're in the same province, but there cannot be two army commanders in one army. " << endl;
    cout << endl;
    cout << "You can increase the size of an army by increasing the level of the army's commander (this can only be done when the army commander and their army are in the capital-- player action 'player deployment'). " << endl;
    cout << "---------- This is the end of the Help message ----------" << endl;
    cout << endl;
    std::cout << "\033[;0m"; //NW
}

void armyDeploymentHelp(int maxAmountOfCommanders)
{
    std::cout << "\033[;34m"; //NW
    cout << "---------- This is the beginning of the Help message ----------" << endl;
    cout << "Train a commander (T): " << endl;
    cout << "- The price of training a commander increases as the amount of commanders you have increases. You start off with one commander" << endl;
    cout << "- The max limit of commanders you can train: " << maxAmountOfCommanders << endl << endl;

    cout << "Upgrade a commander (U): " << endl;
    cout << "- The price of upgrading a commander increases as the level of the commander increases" << endl;
    cout << "- There is no cap on how much you can upgrade a commander" << endl;
    cout << "- The greater the level of a commander, the more troops they can lead in their army (5 units per level) " << endl << endl;

    cout << "View army overview (V): " << endl;
    cout << "- See all your armies (their coordinates and their stats)" << endl << endl;

    cout << "Deploy a commander (D): " << endl;
    cout << "- Move commanders out of the capital and onto the map" << endl;
    cout << "---------- This is the end of the Help message ----------" << endl;
    cout << endl;
    std::cout << "\033[;0m"; //NW
}

void playerActionHelp()
{
    std::cout << "\033[;34m"; //NW
    cout << "---------- This is the beginning of the Help message ----------" << endl;
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
    cout << "---------- This is the end of the Help message ----------" << endl;
    cout << endl;
    std::cout << "\033[;0m"; //NW
    cout << "Enter 'P' when you've finished reading the help message to proceed back to the Main menu: ";
}

void playerMapHelp()
{
    std::cout << "\033[;34m"; //NW
    cout << endl;
    cout << "---------- This is the beginning of the Help message ----------" << endl;
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
    cout << endl;
    std::cout << "\033[;0m"; //NW
}

void viewAllStatsFunction()
{
    string literallyAnyRandomCharacter;
    std::cout << "\033[;34m";//NW
    std::cout << "Militia lost: " << playerTroopsLost[0] << endl;
    std::cout << "Guards lost: " << playerTroopsLost[1] << endl;
    std::cout << "Cavalry lost: " << playerTroopsLost[2] << endl;
    std::cout << "Knights lost: " << playerTroopsLost[3] << endl;
    std::cout << "Paladins lost: " << playerTroopsLost[4] << endl;
    std::cout << "Total troops lost: " << calculatePlayerValues(2) << endl << endl;
    std::cout << "\033[;0m";//NW

    cout << "Enter any character to go back to the Main menu: ";
    getline(cin, literallyAnyRandomCharacter);
}

char listOfActions(int identifier)
{
    string userInput = " ";
    char userInputChar = ' ';
    string stringToSend = " ";
    /*cout << "- ()" << endl;*/
    /*HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE); //WO
    SetConsoleTextAttribute(console_color, 12);*/
    cout << "\033[;31m";
    cout << "---------- Here is a list of actions you can do: ----------" << endl;
    switch (identifier)
    {
    case 1: /*selectEnemyAction*/
    {
        cout << "- Attack this province (A) " << endl;
        cout << "- Scout this province (S) " << endl;
        cout << "- Go back to the previous menu (M) " << endl;
        break;
    }
    case 2: /*playerUnitAction*/
    {
        cout << "- Move this unit (M)" << endl;
        cout << "- See Help (H)" << endl;
        cout << "- Go back to the View Map action menu (M)" << endl;
        stringToSend = "PHM";
        break;
    }
    case 3: /*introduction*/
    {
        cout << "- Start a new conquest (S)" << endl;
        cout << "- Resume a previous conquest (R)" << endl;
        stringToSend = "SR1";
        break;
    }
    case 4: /*playerAction*/
    {
        std::cout << "- Build Infrastructure (B) " << endl;
        std::cout << "- Train Troops (T) " << endl;
        std::cout << "- View Your Stats (V) " << endl;
        std::cout << "- View the Map (M) " << endl;
        std::cout << "- View Army Deployment (A) " << endl;
        std::cout << "- Go to Next Turn (G)" << endl;
        std::cout << "- Pause game (P) " << endl;
        stringToSend = "BTVMAGPH";
        break;
    }
    case 5: /*armyDeployment*/
    {
        std::cout << "- Train a commander (T) " << endl;
        std::cout << "- Upgrade a commander (U) " << endl;
        std::cout << "- View army overview (V) " << endl;
        std::cout << "- Deploy a commander (D) " << endl;
        std::cout << "- Go back to Main Menu (M) " << endl;
        stringToSend = "TUVDHM";
        break;
    }
    case 6: /*TrainMAFunction*/
    {
        std::cout << "- Proceed with training (P) " << endl;
        std::cout << "- See the amount of resources in this province (S) " << endl;
        std::cout << "- Go back to the Player Train menu (M) " << endl;
        stringToSend = "PSM";
        break;
    }
    case 7: /*playerBuildFunction*/
    {
        std::cout << "- Upgrade a building (U) " << endl;
        std::cout << "- Go back to the previous menu (M) " << endl;
        stringToSend = "UM";
        break;
    }
    case 8: /*viewPlayerMap*/
    {
        std::cout << "- Pick a province (P) " << endl;
        std::cout << "- Go back to the Main menu (M) " << endl;
        stringToSend = "PMH";
        break;
    }
    case 9: /*selectPlayerProvince*/
    {
        std::cout << "- Build infrastructure (B) " << endl;
        std::cout << "- Train Troops (T) " << endl;
        std::cout << "- Go back to the map (M) " << endl;
        stringToSend = "BTM";
        break;
    }
    case 10: /*selectEnemyProvince*/
    {
        std::cout << "- Attack this province (A) " << endl;
        std::cout << "- Scout this province (S) " << endl;
        std::cout << "- View the scout log (V) " << endl;
        std::cout << "- Go back to the menu (M) " << endl;
        stringToSend = "ASVM";
        break;
    }
    case 11: /*scoutLogFunction*/
    {
        std::cout << "- View the garrison report for this province (G) " << endl;
        std::cout << "- View the resource report for this province (R) " << endl;
        std::cout << "- View the building report for this province (B) " << endl;
        std::cout << "- Go back to the Enemy Province Action Selection menu (M) " << endl;
        stringToSend = "GRBM";
        break;
    }
    }
    std::cout << "-------------------- End of list --------------------------" << endl << endl;

    cout << "\033[;0m"; //NW
    //SetConsoleTextAttribute(console_color, 15); //WO
    cout << "Enter the letter of the action you want to complete (enter 'H' to see help to know what to do): ";
    std::getline(cin, userInput);
    userInputChar = checkChar(stringToSend, userInput);
    return userInputChar;

}

void upgradeBuildingsHelp()
{

}//finish this


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

void printCostsToTrainAnotherCommander(int trainArmyCommanderCosts[5], int currentPlayerCommanders
)
{
    std::cout << endl;
    std::cout << "The following is the cost to train another commander: " << endl;
    for (int x = 0; x < 5; x++) /*calculate and print costs to train another commander (more expensive than the last)*/
    {
        trainArmyCommanderCosts[x] = (currentPlayerCommanders + 1) * 10;
        trainArmyCommanderCosts[x] *= initialResources[x];
        std::cout << provinceResourcesNames[x] << ": " << trainArmyCommanderCosts[x] << endl;
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
            switch (provincesList[a][b].getProvinceIdentifier())
            {
            case 'P':
            case 'p':
                x = translateCoordinate(b, 'x', 'O');
                y = translateCoordinate(a, 'y', 'O');
                std::cout << "(" << x << ", " << y << ") " << endl;
                break;
            }
        }
    }
    std::cout << endl;
}

