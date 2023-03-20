#include "textFunctions.h"


void synopsis()
{
    std::cout << "- Welcome to Fight For Emperor" << std::endl;
    std::cout << "- In a large continent, filled with various kingdoms, you are a monarch seeking to unit the land; you will defeat the other kingdoms and become emperorer." << std::endl;
    std::cout << "- Develop buildings, train troops, and use logistics and battle strategies to conquer enemy provinces." << std::endl;
    std::cout << "- Although players cannot save their complete data, a portion of the land that they gained in the previous game (as well as the amount of resources available) will be available through a code \n\n";
}



void casualtyReport(std::array<int,5> troopsLost, std::array<int,5> injuredTroops)
{
    std::cout << std::endl;
    std::cout << "Troops casualties: " << std::endl;
    for (int x = 0; x < 5; x++) /*print out deaths*/
    {
        std::cout << CV.TROOP_NAMES[x] << " lost: " << troopsLost[x] << std::endl;
    }
    std::cout << std::endl;
    for (int x = 0; x < 5; x++) /*print out deaths*/
    {
        std::cout << CV.TROOP_NAMES[x] << " injured: " << injuredTroops[x] << std::endl;
    }
    std::cout << std::endl;
}


