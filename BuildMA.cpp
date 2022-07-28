#include <iostream>
#include <vector>
#include <string>

#include "BuildMA.h"
#include "otherFunctions.h"
#include "Provinces.h"
#include "textFunctions.h"

using namespace std;

extern vector <vector<Provinces>> provincesMap;
extern string buildingNames[6];
extern string provinceResourcesNames[5];

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
    vector <int> XYCoordinates;
    do
    {
        XYCoordinates.clear();
        std::cout << "Welcome to the Player Build menu" << endl << endl;
        XYCoordinates = getTrainBuildCoordinates();
        provinceXCoordinate = XYCoordinates[0];
        provinceYCoordinate = XYCoordinates[1];
        if (provinceXCoordinate == -1 || provinceYCoordinate == -1)
        {
            repeatThisOne = 'N';
            std::cout << "Returning to Main menu... " << endl;
        }
        else
        {
            switch (provincesMap[provinceXCoordinate][provinceYCoordinate].getProvinceIdentifier())
            {
            case 'P':
            case 'p':
            case 'H':
                playerBuildFunction();
                break;
            default:
                std::cout << "Invalid province elected. Please try again. " << endl;
                break;
            }
            std::cout << endl;
        }
    } while (repeatThisOne == 'Y');
}
void BuildMA::playerBuildFunction()
{
    std::cout << "---------- Start printing province information ----------" << endl;
    provincesMap[provinceXCoordinate][provinceYCoordinate].printResources();
    provincesMap[provinceXCoordinate][provinceYCoordinate].printBuildingStats();
    std::cout << "---------- End printing province information ----------" << endl << endl;

    char upgradeBuilding = ' ';
    char repeatPlayerBuildFunction = 'Y';

    do
    {
        upgradeBuilding = listOfActions(7);
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
            std::cout << buildingNames[buildingNumber] << " selected " << endl;
            std::cout << "The following is the cost of the upgrade: " << endl; //here
            for (int x = 0; x < 5; x++)
            {
                requiredResources[x] = (int)requiredResourcesBuildings[buildingNumber][x] * newProvince->getBuildingLevel(x);
                std::cout << provinceResourcesNames[x] << ": " << requiredResources[x] << endl;
            }
            std::cout << endl;
            char upgradeProceed = getChar("Proceed with upgrade? (Y/N) ", "YN", 1);

            if (upgradeProceed == 'Y')
            {
                char failOrWork = 'W'; /*delete this? not necessary-- will always return 'Y'*/
                for (int x = 0; x < 5; x++)
                {
                    newProvince->subtractResources(x, requiredResources[x]);
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
            upgradeBuildingsHelp();
        }
        upgradeAnotherBuildingChar = getChar("Upgrade another building (Y/N): ", "YN", 1);
    } while (upgradeAnotherBuildingChar == 'Y');
    std::cout << "Returning to Build Infrastructure action menu. " << endl;
}