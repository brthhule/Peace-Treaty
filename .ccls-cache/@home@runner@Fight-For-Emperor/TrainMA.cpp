#include "TrainMA.h"

TrainMA::TrainMA(Provinces *newP)
{
   province = newP;
}

void TrainMA::TrainMAFunction()
{
    Provinces* newProvinceList;
    newProvinceList = &provincesMap[provinceXCoordinate][provinceYCoordinate];
    int troopCost[5] = { 5, 4, 3, 2, 1 };

    int barracksLevel = newProvinceList->getBuildingLevel(5);
    std::cout << "Start printing province barracks information: \033[34m" << std::endl;
    std::cout << "Province of kingdom " << participantsList[provincesMap[provinceXCoordinate][provinceYCoordinate].getBelongsToParticipant()].getKingdomName() << " selected" << std::endl;
    std::cout << "Coordinates: (" << translateCoordinate(provinceYCoordinate, 'x', 'O') << ", " << translateCoordinate(provinceXCoordinate, 'y', 'O') << ") " << std::endl << std::endl;
    std::cout << "The barracks level of this province: " << barracksLevel << std::endl;
    int troopTier = barracksLevel / 5;
    troopTier += 1;

    if (troopTier > 5)
    {
        troopTier = 5;
    }
    std::cout << "The max tier troop you can train: " << troopTier << ", " << troopNames[troopTier - 1] << std::endl;
    std::cout << "The max amount of troops you can train at this barracks during this turn (training capacity): \033[0m" << std::endl;
    std::cout << std::endl;
    int trainTroop;
    std::string trainTroops std::string;
    std::vector <std::string> trainTroopsAVOne;
    std::vector <int> trainTroopsAVTwo;
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
        std::string amountOfTroopsstd::string = " ";
        std::vector <int> amountOfTroopsAV = {};
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
                std::cout << "The required amount of resources are as follows: " << std::endl; //here
                for (int x = 0; x < 5; x++)
                {
                    std::cout << provinceResourcesNames[x] << ": " << requiredResources[x] << std::endl;
                }
                std::cout << std::endl;
                char repeatProceedWithTraining = 'Y';
                std::string proceedWithTrainingstdString;
                std::vector <char> proceedWithTrainingThree = { 'P', 'S', 'M' };
        
                do
                {
                    Lists newList (6);
                    char proceedWithTraining = newList.listOfActions();
                    std::cout << std::endl;
        
                    switch (proceedWithTraining)
                    {
                    case 'P':
                    {
                        char trainingFail = 'S';
                        for (int a = 0; a < 5; a++)
                        {
                            newProvinceList->addRSS(a, requiredResources[a] * -1);
                            if (newProvinceList->getResource(a) < 0)
                            {
                                trainingFail = 'F';
                            }
                        }
        
                        if (trainingFail == 'F')
                        {
                            std::cout << "Training failed" << std::endl;
                            for (int a = 0; a < 5; a++)
                            {
                                newProvinceList->addResources(a, requiredResources[a]);
                            }
                        }
                        else
                        {
                            std::cout << "Training successful" << std::endl;
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
                        std::cout << "Returning to menu... " << std::endl;
                    }
                    }
                } while (repeatProceedWithTraining == 'Y');
            }
            else
            {
                repeatOuterDoLoop = 'Y';
                std::cout << "Amount of troops selected exceeds the training capacity of the barracks... please try again" << std::endl;
            }
        } while (repeatOuterDoLoop == 'Y');
    }

}

std::vector <Provinces*> TrainMA::getTrainProvince()
{
  std::cout << "Welcome to the Player Train menu" << std::endl << std::endl;
  getTrainBuildCoordinates(provinceXCoordinate, provinceYCoordinate);

  if (provinceXCoordinate == -1 || provinceYCoordinate == -1)
  {
      repeatThisOne = 'N';
      std::cout << "Returning to Main menu... " << std::endl;
  }
  else
  {
      if (provincesMap[provinceXCoordinate][provinceYCoordinate].getBelongsToParticipant() == currentParticipantIndex)
      {
          TrainMAFunction();
      }
      else
      {
          std::cout << "Invalid province elected. Please try again. " << std::endl;
      }
      std::cout << std::endl;
  }
}