#include "ScoutMA.h"

#define print(x) std::cout << x;
#define println(x) std::cout << x << endl;

extern std::vector <std::vector <Provinces>> provincesMap;
extern std::vector <Participants> participantsList;
extern std::vector <std::vector <CommanderProfile>> allCommanders;
extern int currentParticipantIndex;
extern int continentSize;
extern int turn;

ScoutMA::ScoutMA(Participants *newParticipant, Provinces *newProvince)
{
  participant = newParticipant;
  yourProvince = newProvince; 
}

void ScoutMA::selectTargetToScout() /*So much to fix here... truly so much.... make sure to simplify things later on*/
{
    Participants* enemyParticipant = &participantsList[targetParticipantIndex];

    std::string unitType = " ";
    std::vector <int> acceptableValues;
    std::string unitName = " ";
    println("Coordinates selected to scout: ");

    println("The following units are at these coordinates: ");
	
    std::cout << "1) Province " << targetProvince->getUnitName() << " (Level " << targetProvince->findProvinceLevel() << ") " << endl;
    acceptableValues.push_back(1);

    for (int b = 0; b < targetProvince->commanders.size(); b++)
    {
        CommanderProfile* newCommander = participantsList[targetParticipantIndex].getCommander(enemyProvince->returnCommanderIndex(b));
			
        std::cout << b + 2 << ") Commander " << newCommander.getUnitName() << " (Level " << newCommander.getCommanderLevel() << ") " << endl;
        acceptableValues.push_back(b + 2);
    }
    int numberSelected = getInt("Enter the number of the unit you would like to select (the number to the left of the first ')' symbol): ",
        acceptableValues, 1);
    if (numberSelected == 1)
    {
			//Identify target as a province
        targetInformation[0] = 0;
			Provinces *target
        targetInformation[1] = participantsList[targetParticipantIndex].
            findProvinceIndexWithCoordinates(targetXCoordinate, targetYCoordinate);
        unitType = "Province ";
        unitName = enemyProvince-> getUnitName();
        enemyLevel = enemyProvince->findProvinceLevel();
    }
    else
    {
        targetInformation[0] = 1;//Identify target as a commander
        targetInformation[1] = numberSelected - 2;//Have to check if this is right later
        unitType = "Commander";
        CommanderProfile* newCommander = &allCommanders[targetParticipantIndex][targetInformation[1]];
        unitName = newCommander->getUnitName();
        enemyLevel = newCommander->getCommanderLevel();
    }
    std::cout << unitType << " " << unitName << " selected " << endl;
    std::cout << "You can only scout this unit if one of your provinces or armies is next to it... " << endl;

    //Find if there are any player units that can scout the target
    for (int a = -1; a <= 1; a++) /*Identify the surrounding units that can scout, add them to std::vectors (their coordinates)*/
    {
        for (int b = -1; b <= 1; b++)
        {
            if (/*X coordinates*/targetXCoordinate + a >= 0 && targetXCoordinate + a < continentSize && /*Y coordinates*/targetYCoordinate + b >= 0 && targetYCoordinate + b < continentSize)
            {
                if (provincesMap[targetXCoordinate + a][targetYCoordinate + b].getBelongsToParticipant() == currentParticipantIndex)
                {
                    provincesCanSelectX.push_back(targetXCoordinate + a);
                    provincesCanSelectY.push_back(targetYCoordinate + b);
                    //Finds the index of the province, makes the Participants object return the province, change canSelectThisUnit of the province
                }

                for (int x = 0; x < attackingParticipant->howManyCommanders(); x++)
                {
                    if (allCommanders[currentParticipantIndex][x].getCoordinate('X') == targetXCoordinate + a &&
                        allCommanders[currentParticipantIndex][x].getCoordinate('Y') == targetXCoordinate + b)
                    {
                        commandersCanSelect.push_back(x);
                    }
                }
            }
        }
    }

    //If there are commanders or provinces that can scout the target
    if (provincesCanSelectX.size() > 0 || commandersCanSelect.size() > 0)
    {
        playerScoutStepTwo();
    }
    else
    {
        std::cout << "No player provinces or armies are around the target... " << endl;
    }
    std::cout << "Returning to previous menu" << endl << endl;
} /*fix this-- needs to be reviewed*/

void ScoutMA::playerScoutStepTwo()//Finish this later
{
    int accuracy = 0;
    std::vector <int> unitsCanScoutWith;

    std::cout << "You have " << provincesCanSelectX.size() + commandersCanSelect.size() << " provinces and armies next to the target. Below is a list of units that can scout the target.";
    std::cout << " Please note that the higher the level of the scouting unit, the more accurate the results of the scout report are (The level of the target unit is " << enemyLevel << "). " << endl << endl;

    std::vector <int> unitLevels = showUnitsCanScout();
    int cutOffThingy = unitLevels[0];
    unitLevels.erase(unitLevels.begin());

    for (int x = 1; x <= unitLevels.size(); x++)
    {
        unitsCanScoutWith.push_back(x);
    }
    std::cout << endl;

    int scoutWithThis = getInt("Please enter the number of the unit you would like to select: ", unitsCanScoutWith, 1);
    scoutWithThis--;

    int xCoordinateThingy = 0;
    int yCoordinateThingy = 0;
    int unitAccuracyLevel = 0;

    std::cout << "Proceed scout action with unit at (" << translateCoordinate(xCoordinateThingy, 'x', 'O') << ", " << translateCoordinate(yCoordinateThingy, 'y', 'O') << ")? (Y/N) ";
    char proceedWithScoutChar = getChar(" ", "YN", 2);

    if (proceedWithScoutChar == 'Y')
    {
        int accuracy = 50;
        if (unitLevels[scoutWithThis] > enemyLevel)
        {
            for (int x = unitLevels[scoutWithThis]; x >= enemyLevel; x--)
            {
                accuracy += 5;
            }
        }
        if (unitLevels[scoutWithThis] < enemyLevel)
        {
            for (int x = unitLevels[scoutWithThis]; x <= enemyLevel; x++)
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
            Participants* newParticipant = &participantsList[currentParticipantIndex];
            provincesMap[newParticipant->listOfProvincesX[scoutWithThis]][newParticipant->listOfProvincesY[scoutWithThis]].completeProvinceScoutReport(accuracy);
        }
        else
        {
            Participants* newParticipant = &participantsList[currentParticipantIndex];
            allCommanders[currentParticipantIndex][scoutWithThis].completeCommanderScoutReport(accuracy);
        }

    }
}
std::vector<int>  ScoutMA::showUnitsCanScout()
{
    Participants* attackingParticipant = &participantsList[currentParticipantIndex];

    std::vector <int> unitLevels = { 0 };
    std::cout << "\033[;34m";
    std::vector <CommanderProfile*> commandersCanSelect;
    char commanderThingy = ' ';
    int provinceIndex = 0;
    int commanderIndex = 0;
    //For all the provinces in the std::vector

    std::cout << "Provinces that can scout: " << endl;
    for (int a = 0; a < provincesCanSelectX.size(); a++)
    {
        unitLevels.push_back(provincesMap[provincesCanSelectX[a]][provincesCanSelectY[a]].findProvinceLevel());
        std::cout << a + 1 << ": (" << translateCoordinate(provincesCanSelectX[a], 'x', 'O') << ", " <<
            translateCoordinate(provincesCanSelectY[a], 'y', 'O') << "); ";
        std::cout << "Unit level: " << unitLevels.back();
    }
    int cutOffProvinceCommanderThingy = (int)unitLevels.size() - 1;
    unitLevels[0] = cutOffProvinceCommanderThingy;

    std::cout << "Commanders that can scout: " << endl;
    for (int a = 0; a < commandersCanSelect.size(); a++)
    {
        unitLevels.push_back(commandersCanSelect[a]->getCommanderLevel());
        std::cout << a + a << ": (" << translateCoordinate(commandersCanSelect[a]->getCoordinate('X'), 'x', 'O') << ", " << translateCoordinate(commandersCanSelect[a]->getCoordinate('Y'), 'y', 'O') << "); ";
        std::cout << "Unit level: " << unitLevels.back();
    }
    std::cout << endl;
    std::cout << "\033[;0m";
    return unitLevels;
}

