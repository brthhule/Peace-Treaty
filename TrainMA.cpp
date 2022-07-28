#include "TrainMA.h"
#include "textFunctions.h"
#include "AllUnits.h"
#include "Provinces.h"

using namespace std;

extern vector <vector <Provinces>> provincesMap;
extern string troopNames[5];
extern string provinceResourcesNames[5];

TrainMA::TrainMA()
{
    provinceXCoordinate = 0;
    provinceYCoordinate = 0;
}
TrainMA::TrainMA(int xCoordinate, int yCoordinate)
{
    provinceXCoordinate = xCoordinate;
    provinceYCoordinate = yCoordinate;
}

void TrainMA::TrainMAFunction()
{
    Provinces* newProvinceList;
    newProvinceList = &provincesMap[provinceXCoordinate][provinceYCoordinate];
    int troopCost[5] = { 5, 4, 3, 2, 1 };

    int barracksLevel = newProvinceList->getBuildingLevel(5);

    cout << "The barracks level of this province: " << barracksLevel << endl;
    int troopTier = barracksLevel / 5;
    troopTier += 1;

    if (troopTier > 5)
    {
        troopTier = 5;
    }
    std::cout << "The max tier troop you can train: " << troopTier << ", " << troopNames[troopTier - 1] << endl;
    std::cout << endl;
    int trainTroop;
    string trainTroopsString;
    vector <string> trainTroopsAVOne;
    vector <int> trainTroopsAVTwo;
    char repeat = 'N';
    for (int x = 1; x <= troopTier; x++)
    {
        trainTroopsAVTwo.push_back(x);
    }
    int maxAmountOfTroopsBarracksCanTrain = newProvinceList->getBuildingLevel(5) * 2;

    std::cout << "What tier troop do you want to train? (1/2/3/4/5) ";
    std::getline(cin, trainTroopsString);
    trainTroop = checkInt(trainTroopsAVTwo, trainTroopsString);

    if (trainTroop <= troopTier)
    {
        int amountOfTroops;
        string amountOfTroopsString = " ";
        vector <int> amountOfTroopsAV = {};
        for (int x = 0; x <= maxAmountOfTroopsBarracksCanTrain - newProvinceList->getTroopsTrainedThisTurn(); x++) /*fix this*/
        {
            amountOfTroopsAV.push_back(x);
        }

        std::cout << "How many tier " << troopTier << " troops do you want to train (troops trained in this barracks: " << newProvinceList->getTroopsTrainedThisTurn() << "/" << maxAmountOfTroopsBarracksCanTrain << ")? ";
        std::getline(cin, amountOfTroopsString);
        cout << endl;

        amountOfTroops = checkInt(amountOfTroopsAV, amountOfTroopsString);
        int requiredResources[5] = { 0 };
        for (int x = 0; x < 5; x++)
        {
            requiredResources[0] = troopCost[0] * troopTier;
            requiredResources[0] *= amountOfTroops;
        }
        std::cout << "The required amount of resources are as follows: " << endl; //here
        for (int x = 0; x < 5; x++)
        {
            std::cout << provinceResourcesNames[x] << ": " << requiredResources[x] << endl;
        }
        std::cout << endl;
        char repeatProceedWithTraining = 'Y';
        string proceedWithTrainingString;
        vector <char> proceedWithTrainingThree = { 'P', 'S', 'M' };

        do
        {
            char proceedWithTraining = listOfActions(6);
            std::cout << endl;

            switch (proceedWithTraining)
            {
            case 'P':
            {
                char trainingFail = 'S';
                for (int a = 0; a < 5; a++)
                {
                    newProvinceList->subtractResources(a, requiredResources[a]);
                    if (newProvinceList->getResource(a) < 0)
                    {
                        trainingFail = 'F';
                    }
                }

                if (trainingFail == 'F')
                {
                    std::cout << "Training failed" << endl;
                    for (int a = 0; a < 5; a++)
                    {
                        newProvinceList->addResources(a, requiredResources[a]);
                    }
                }
                else
                {
                    std::cout << "Training successful" << endl;
                    newProvinceList->addSpecificTroop(troopTier - 1, amountOfTroops);
                }
                break;
            }
            case 'S':
            {
                newProvinceList->printResources();
                break;
            }
            case 'M':
            {
                repeatProceedWithTraining = 'N';
                cout << "Returning to menu... " << endl;
            }
            }
        } while (repeatProceedWithTraining == 'Y');
    }

}

void TrainMA::findProvinceCoordinates()
{
    char repeatThisOne = 'Y';
    vector <int> XYCoordinates;
    do
    {
        XYCoordinates.clear();
        cout << "Welcome to the Player Train menu" << endl << endl;
        XYCoordinates = getTrainBuildCoordinates();
        provinceXCoordinate = XYCoordinates[0];
        provinceYCoordinate = XYCoordinates[1];

        if (provinceXCoordinate == -1 || provinceYCoordinate == -1)
        {
            repeatThisOne = 'N';
            cout << "Returning to Main menu... " << endl;
        }
        else
        {
            switch (provincesMap[provinceXCoordinate][provinceYCoordinate].getProvinceIdentifier())
            {
            case 'P':
            case 'p':
            case 'H':
                TrainMAFunction();
                break;
            default:
                std::cout << "Invalid province elected. Please try again. " << endl;
                break;
            }
            std::cout << endl;
        }
    } while (repeatThisOne == 'Y');
}