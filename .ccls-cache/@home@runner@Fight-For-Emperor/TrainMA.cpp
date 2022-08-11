#include "TrainMA.h"
#include "textFunctions.h"
#include "AllUnits.h"
#include "Provinces.h"
#include "coordinateFunctions.h"

using namespace std;

extern vector <vector <Provinces>> provincesMap;
extern vector <Participants> participantsList;
extern string troopNames[5];
extern string provinceResourcesNames[5];
extern int currentParticipantIndex;

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
    cout << "Start printing province barracks information: \033[34m" << endl;
    cout << "Province of kingdom " << participantsList[provincesMap[provinceXCoordinate][provinceYCoordinate].getBelongsToParticipant()].getKingdomName() << " selected" << endl;
    cout << "Coordinates: (" << translateCoordinate(provinceYCoordinate, 'x', 'O') << ", " << translateCoordinate(provinceXCoordinate, 'y', 'O') << ") " << endl << endl;
    cout << "The barracks level of this province: " << barracksLevel << endl;
    int troopTier = barracksLevel / 5;
    troopTier += 1;

    if (troopTier > 5)
    {
        troopTier = 5;
    }
    std::cout << "The max tier troop you can train: " << troopTier << ", " << troopNames[troopTier - 1] << endl;
    std::cout << "The max amount of troops you can train at this barracks during this turn (training capacity): \033[0m" << endl;
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

    trainTroop = getInt("What tier troop do you want to train? (1/2/3/4/5) ", trainTroopsAVTwo, 1);
    char repeatOuterDoLoop = 'N';
    if (trainTroop <= troopTier)
    {
        int amountOfTroops = 0;
        string amountOfTroopsString = " ";
        vector <int> amountOfTroopsAV = {};
        for (int x = 0; x <= maxAmountOfTroopsBarracksCanTrain - newProvinceList->getTroopsTrainedThisTurn(); x++) /*fix this*/
        {
            amountOfTroopsAV.push_back(x);
        }
        do
        {
            repeatOuterDoLoop = 'N';
            std::cout << "How many tier " << troopTier << " troops do you want to train (troops trained in this barracks: " << newProvinceList->getTroopsTrainedThisTurn() << "/" << maxAmountOfTroopsBarracksCanTrain << ")? ";
            amountOfTroops = getInt("Replacement", amountOfTroopsAV, 2);
    
            if (amountOfTroops <= maxAmountOfTroopsBarracksCanTrain - newProvinceList->getTroopsTrainedThisTurn())
            {
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
                        provincesMap[provinceXCoordinate][provinceYCoordinate].addTroopsTrainedThisTurn(amountOfTroops);
                        cout << "Returning to menu... " << endl;
                    }
                    }
                } while (repeatProceedWithTraining == 'Y');
            }
            else
            {
                repeatOuterDoLoop = 'Y';
                cout << "Amount of troops selected exceeds the training capacity of the barracks... please try again" << endl;
            }
        } while (outerDoLoop == 'Y')
    }

}

void TrainMA::findProvinceCoordinates()
{
    char repeatThisOne = 'Y';
    do
    {
        cout << "Welcome to the Player Train menu" << endl << endl;
        getTrainBuildCoordinates(provinceXCoordinate, provinceYCoordinate);

        if (provinceXCoordinate == -1 || provinceYCoordinate == -1)
        {
            repeatThisOne = 'N';
            cout << "Returning to Main menu... " << endl;
        }
        else
        {
            if (provincesMap[provinceXCoordinate][provinceYCoordinate].getBelongsToParticipant() == currentParticipantIndex)
            {
                TrainMAFunction();
            }
            else
            {
                std::cout << "Invalid province elected. Please try again. " << endl;
            }
            std::cout << endl;
        }
    } while (repeatThisOne == 'Y');
}