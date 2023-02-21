#include "BuildMA.h"


extern vector <Participants> participantsList;
extern int continentSize;

using namespace std;

extern vector <vector<Provinces>> provincesMap;
extern string buildingNames[6];
extern string provinceResourcesNames[5];
extern int currentParticipantIndex;

BuildMA::BuildMA()
{
    provinceXCoordinate = 0;
    provinceYCoordinate = 0;
}
BuildMA::BuildMA(int xCoordinate, int yCoordinate)
{
    provinceXCoordinate = xCoordinate;
    provinceYCoordinate = yCoordinate;

}

void BuildMA::findProvinceCoordinates()
{
    char repeatThisOne = 'Y';

    do
    {
        provinceXCoordinate = 0;
        provinceYCoordinate = 0;

        std::cout << "Welcome to the Player Build menu" << endl << endl;
        getTrainBuildCoordinates(provinceXCoordinate, provinceYCoordinate);
    
        if (provinceXCoordinate == continentSize && provinceYCoordinate == 1)
        {
            //weird exception in translating units-- everything else units, except for the bottom left province
            //cout << "Continent size: " << continentSize << endl;
            provinceXCoordinate = continentSize - 1;
            provinceYCoordinate = continentSize - 1;
        }

        if (provinceXCoordinate == -1 || provinceYCoordinate == -1)
        {
            repeatThisOne = 'N';
            std::cout << "Returning to Main menu... " << endl;
        }
        else
        {
            if (provincesMap[provinceXCoordinate][provinceYCoordinate].getParticipantIndex() == currentParticipantIndex)
            {
                playerBuildFunction();
            }
            else
            {
                string anyInput = " ";
                std::cout << "Invalid province elected. Please try again. " << endl;
                cout << "Enter anything to proceed back to the Player Build menu (Screen will clear) ";
                std::getline (cin, anyInput);
                clearScreen();
            }
            std::cout << endl;
        }
    } while (repeatThisOne == 'Y');
}
void BuildMA::playerBuildFunction()
{
    clearScreen();
    std::cout << "---------- Start printing province information ----------" << endl;
    cout << "\033[34m";
    cout << "Province of kingdom " << participantsList[provincesMap[provinceXCoordinate][provinceYCoordinate].getParticipantIndex()].getKingdomName() << endl;
    cout << "Coordinates: (" << translateCoordinate(provinceYCoordinate, 'x', 'O') << ", " << translateCoordinate(provinceXCoordinate, 'y', 'O') << ") " << endl << endl;
    cout << "\033[0m";
    provincesMap[provinceXCoordinate][provinceYCoordinate].printResources();
    provincesMap[provinceXCoordinate][provinceYCoordinate].printBuildingStats();
    std::cout << "---------- End printing province information ----------" << endl << endl;

    char upgradeBuilding = ' ';
    char repeatPlayerBuildFunction = 'Y';

    do
    {
        Lists newList (7);
        upgradeBuilding = newList.listOfActions();
        if (upgradeBuilding == 'U')
        {
            upgradeBuildings();
        }
        else
        {
            repeatPlayerBuildFunction = 'N';
        }
        std::cout << endl;
    } while (repeatPlayerBuildFunction == 'Y');
    std::cout << "Returning to previous menu... " << endl;
    clearScreen();
}
void BuildMA::upgradeBuildings()
{
    Provinces* newProvince;
    newProvince = &provincesMap[provinceXCoordinate][provinceYCoordinate];
    string upgradeAnotherBuildingString;
    char upgradeAnotherBuildingChar = 'Y';
    int requiredResources[5] = { 0 };
    int buildingNumber = 0;
    string buildingLetterString;
    string buildingLetterList = "FLQMCBH";

    do
    {
        char buildingLetter = getChar("Enter the first letter of the building you want to upgrade (enter 'H' for help): ", buildingLetterList, 1);
        if (buildingLetter != 'H')
        {
            for (int x = 0; x < 6; x++)
            {
                if (buildingLetter == buildingLetterList.at(x))
                {
                    buildingNumber = x;
                    x = 6;
                }
            }
            cout << "---------- Start printing information----------" << endl;
            cout << endl << "\033[34m";
            std::cout << buildingNames[buildingNumber] << " selected " << endl << endl;
            std::cout << "The following is the cost of the upgrade: " << endl; //here
            for (int x = 0; x < 5; x++)
            {
                requiredResources[x] = (int)requiredResourcesBuildings[buildingNumber][x] * newProvince->getBuildingLevel(x);
                std::cout << provinceResourcesNames[x] << ": " << requiredResources[x] << endl;
            }
            cout << endl;
            cout << "The following are how many resources are in this province: " << endl;
            newProvince->printResources();
            cout << "----------End printing informatio----------" << endl;
            char upgradeProceed = getChar("Proceed with upgrade? (Y/N) ", "YN", 1);

            if (upgradeProceed == 'Y')
            {
                char failOrWork = 'W'; /*delete this? not necessary-- will always return 'Y'*/
                for (int x = 0; x < 5; x++)
                {
                    newProvince->addRSS(x, requiredResources[x] * -1);
                    if (newProvince->getResource(x) < 0)
                    {
                        failOrWork = 'F';
                    }
                }

                if (failOrWork == 'F')
                {
                    for (int x = 0; x < 5; x++)
                    {
                        newProvince->addResources(x, requiredResources[x]);
                    }
                    std::cout << "Upgrade failed. Not enough resources. " << endl;
                }
                else
                {
                    std::cout << "Upgrade successful." << endl << endl;
                    newProvince->increaseBuildingLevel(buildingNumber, 1);
                }
            }
        }
        else
        {
            Lists newList (12);
            newList.listOfHelp();
        }
        upgradeAnotherBuildingChar = getChar("Upgrade another building (Y/N): ", "YN", 1);
    } while (upgradeAnotherBuildingChar == 'Y');
    std::cout << "Returning to Build Infrastructure action menu. " << endl;
}