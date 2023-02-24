#include "textFunctions.h"

using namespace std;
extern std::vector <std::vector <Provinces>> provincesMap;
extern std::vector <Participants> participantsList;
extern std::string provinceResourcesNames[5];
extern std::string buildingNames[6];
extern std::string troopNames[5];
extern int initialResources[5];
extern int continentSize;
extern int currentParticipantIndex;

void synopsis()
{
    std::cout << "- Welcome to Fight For Emperor" << endl;
    std::cout << "- In a large continent, filled with various kingdoms, you are a monarch seeking to unit the land; you will defeat the other kingdoms and become emperorer." << endl;
    std::cout << "- Develop buildings, train troops, and use logistics and battle strategies to conquer enemy provinces." << endl;
    std::cout << "- Although players cannot save their complete data, a portion of the land that they gained in the previous game (as well as the amount of resources available) will be available through a code " << endl << endl;
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


