#include "ScoutMA.h"
#include "Provinces.h"
#include "Participants.h"

extern vector <vector <Provinces>> provincesMap;
extern vector <Participants> participantsList;
extern int actualParticipantIndex;
extern int continentSize;
extern int turn;

ScoutMA::ScoutMA (int targetXCoordinateV, int targetYCoordinateV)
{
    targetXCoordinate = targetXCoordinateV;
    targetYCoordinate = targetYCoordinateV;
}

void ScoutMA::playerScout() /*So much to fix here... truly so much*/
{
    Provinces *enemyProvince = &provincesMap[targetXCoordinate][targetYCoordinate];
    int enemyProvinceLevel = enemyProvince->findProvinceLevel();
    std::cout << "Province selected to scout: (" << translateCoordinate(targetXCoordinate, 'x', 'O') << ", " << translateCoordinate(targetYCoordinate, 'y', 'O') << ") ";
    std::cout << " Level of this province: " << enemyProvinceLevel << endl << endl;
    string playerScoutString;
    participantsList[actualParticipantIndex].clearCanSelectThisUnit();
    std::cout << "You can only scout this unit if one of your provinces or armies is next to it... " << endl;
    for (int a = -1; a <= 1; a++) /*Identify the surrounding units that can scout, add them to vectors (their coordinates)*/
    {
        for (int b = -1; b <= 1; b++)
        {
            if (/*X coordinates*/targetXCoordinate + a >= 0 && targetXCoordinate + a < continentSize && /*Y coordinates*/targetYCoordinate + b >= 0 && targetYCoordinate + b < continentSize)
            {
                if (provincesMap[targetXCoordinate + a][targetYCoordinate + b].getBelongsToParticipant() == actualParticipantIndex)
                {
                    //Finds the index of the province, makes the Participants object return the province, change canSelectThisUnit of the province
                    participantsList[actualParticipantIndex].returnProvince(provincesMap[targetXCoordinate + a][targetYCoordinate + b].returnIndexInList()).changeCanSelectThisUnit();
                }
            }
        }
    }

    if (provincesCanSelect.size() > 0)
    {
        if (provincesMap[xCoordinate][yCoordinate].getCommandersPresent() == 1)
        {
            string proceedWithScout;
            std::cout << "You have " << provincesCanSelect.size() << " provinces or armies next to the target. Below is a list of units that can scout the target.";
            std::cout << " Please note that the higher the level of the scouting unit, the more accurate the results of the scout report are (The level of the target unit is " << enemyProvinceLevel << "). " << endl << endl;

            vector <int> unitLevels = showUnitsCanScout(provincesCanSelect);
            int cutOffThingy = unitLevels[0];
            unitLevels.erase(unitLevels.begin());
            std::cout << endl;
            std::cout << "Please enter the number of the unit you would like to select: ";
            getline(cin, playerScoutString);
            int scoutWithThis = checkInt(unitLevels, playerScoutString);
            scoutWithThis--;
            int xCoordinateThingy = 0;
            int yCoordinateThingy = 0;
            int unitAccuracyLevel = 0;
            std::cout << "Proceed scout action with unit at (" << translateCoordinate(xCoordinateThingy, 'x', 'O') << ", " << translateCoordinate(yCoordinateThingy, 'y', 'O') << ")? (Y/N) ";
            char proceedWithScoutChar = getChar(" ", "YN", 2);
            if (proceedWithScoutChar == 'Y')
            {
                int accuracy = 50;
                if (unitLevels[scoutWithThis] > enemyProvinceLevel)
                {
                    for (int x = unitLevels[scoutWithThis]; x >= enemyProvinceLevel; x--)
                    {
                        accuracy += 5;
                    }
                }
                if (unitLevels[scoutWithThis] < enemyProvinceLevel)
                {
                    for (int x = unitLevels[scoutWithThis]; x <= enemyProvinceLevel; x++)
                    {
                        accuracy -= 5;
                    }
                }

                if (accuracy > 100)
                {
                    accuracy = 100;
                }
                if (accuracy < 0)
                {
                    accuracy = 0;
                }
                
                if (scoutWithThis < cutOffThingy)
                {
                    participantsList[actualParticipantIndex].returnProvince(scoutWithThis)->completeProvinceScoutReport(accuracy);
                }
                else
                {
                    participantsList[actualParticipantIndex].returnCommander(scoutWithThis)->completeCommanderScoutReport(accuracy);
                }

            }
        }
        else
        {
            std::cout << "There are multiple enemy units at this location... please pick the enemy unit you would like to scout:" << endl;//fix this--identify which enemy to scout if there are multiple enemies at a province
            //...*code to find the unit, find which enemy pariticipant it belongs to and which army commander if applicable
            int accuracy = 0;
            int commanderIndex = 0;//FIX THISSSSSSSSSSSS
            string target;
            if (target == "Commander")
            {
                completeCommanderScoutReport(commanderIndex, accuracy);
            }
            else
            {
                scoutLogCalculationsProvince(accuracy);
            }
        }
    }
    else
    {
        std::cout << "No player provinces or armies are around the target... " << endl;
    }
    std::cout << "Returning to previous menu" << endl << endl;
} /*fix this-- needs to be reviewed*/
vector<int> showUnitsCanScout()
{
    Participants* participant = &participantsList[actualParticipantIndex];

    vector <int> unitLevels = { 0 };
    std::cout << "\033[;34m";
    vector <CommanderProfile*> commandersCanSelect;
    char commanderThingy = ' ';
    int provinceIndex = 0;
    int commanderIndex = 0;
    //For all the provinces in the vector
    for (int x = 0; x < participant->howManyProvinces(); x++)
    {
        
    }
    for (int x = 0; x < provincesCanSelect.size(); x++)
    {
        //For all the commanders in each province in the vector
        for (int a = 0; a < provincesCanSelect[x].getCommandersPresent(); a++)
        {
            //Finds a province, returns that province
            provinceIndex = findProvinceIndex(provincesCanSelect[x].getCoordinate('X'), provincesCanSelect[x].getCoordinate('Y'));//Find the index of the current province
            commanderIndex = participant->returnProvince(provinceIndex).returnCommanderIndex(a);
            commandersCanSelect.push_back(participant->returnCommander(commanderIndex));
        }
    }
    std::cout << "Provinces that can scout: " << endl;
    for (int a = 0; a < provincesCanSelect.size(); a++)
    {
        unitLevels.push_back(provincesCanSelect[a].findProvinceLevel());
        std::cout << a + 1 << ": (" << translateCoordinate(provincesCanSelect[a].getCoordinate('X'), 'x', 'O') << ", " << 
            translateCoordinate(provincesCanSelect[a].getCoordinate('Y'), 'y', 'O') << "); ";
        std::cout << "Unit level: " << unitLevels.back();
    }
    int cutOffProvinceCommanderThingy = (int)unitLevels.size() - 1;
    unitLevels[0] = cutOffProvinceCommanderThingy;

    std::cout << "Commanders that can scout: " << endl;
    for (int a = 0; a < provincesCanSelect.size(); a++)
    {
        unitLevels.push_back(commandersCanSelect[a]->getCommanderLevel());
        std::cout << a + a << ": (" << translateCoordinate(commandersCanSelect[a]->getCoordinate('X'), 'x', 'O') << ", " << translateCoordinate(commandersCanSelect[a]->getCoordinate('Y'), 'y', 'O') << "); ";
        std::cout << "Unit level: " << unitLevels.back();
    }
    std::cout << endl;
    std::cout << "\033[;0m";
    return unitLevels;
}

