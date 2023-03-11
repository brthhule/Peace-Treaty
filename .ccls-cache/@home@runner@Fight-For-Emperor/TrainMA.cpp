#include "TrainMA.h"

TrainMA::TrainMA()
{
	
}
TrainMA::TrainMA(Provinces *newP) { province = newP; }

void TrainMA::TrainMAFunction() {
  int troopCost[5] = {5, 4, 3, 2, 1};

  int barracksLevel = province->getBuildingLevel(5);
  std::cout << "Start printing province barracks information: \033[34m\n";
  std::cout
      << "Province of kingdom "
      << participantsList[province->getParticipantIndex()].getKingdomName()
      << " selected" << std::endl;
  std::cout << "Coordinates: ("
            << province->translateX(false)
            << province->translateY(false)<< ") "
            << std::endl
            << std::endl;
  std::cout << "The barracks level of this province: " << barracksLevel
            << std::endl;
  int troopTier = barracksLevel / 5;
  troopTier += 1;

  if (troopTier > 5) {
    troopTier = 5;
  }
  std::cout << "The max tier troop you can train: " << troopTier << ", "
            << troopNames[troopTier - 1] << std::endl;
  std::cout << "The max amount of troops you can train at this barracks during "
               "this turn (training capacity): \033[0m"
            << std::endl;
  std::cout << std::endl;
  int trainTroop;
  std::string trainTroops;
  std::vector<std::string> trainTroopsAVOne;
  std::vector<std::string> trainTroopsAVTwo;
  char repeat = 'N';
  for (int x = 1; x <= troopTier; x++) {
    trainTroopsAVTwo.push_back(std::to_string(x));
  }
  int maxAmountOfTroopsBarracksCanTrain =
      province->getBuildingLevel(5) * 2;

  trainTroop = stoi(OF.getInput("What tier troop do you want to train? (1/2/3/4/5) ",
                      trainTroopsAVTwo, 1));
  char repeatOuterDoLoop = 'N';
  if (trainTroop <= troopTier) {
    int amountOfTroops = 0;
    std::string amountOfTrops = " ";
    std::vector<std::string> amountOfTroopsAV = {};
    for (int x = 0; x <= maxAmountOfTroopsBarracksCanTrain -
                             province->getTroopsTrainedThisTurn();
         x++) /*fix this*/
    {
      amountOfTroopsAV.push_back(std::to_string(x));
    }
    do {
      repeatOuterDoLoop = 'N';
      std::cout
          << "How many tier " << troopTier
          << " troops do you want to train (troops trained in this barracks: "
          << province->getTroopsTrainedThisTurn() << "/"
          << maxAmountOfTroopsBarracksCanTrain << ")? ";
      amountOfTroops = stoi(OF.getInput("Replacement", amountOfTroopsAV, 2));

      if (amountOfTroops <= maxAmountOfTroopsBarracksCanTrain -
                                province->getTroopsTrainedThisTurn()) {
        std::vector<int> requiredResources = {0, 0, 0, 0, 0};
        for (int x = 0; x < 5; x++) {
          requiredResources[0] = troopCost[0] * troopTier;
          requiredResources[0] *= amountOfTroops;
        }
        std::cout << "The required amount of resources are as follows: "
                  << std::endl; // here
        for (int x = 0; x < 5; x++) {
          std::cout << provinceResourcesNames[x] << ": " << requiredResources[x]
                    << std::endl;
        }
        std::cout << std::endl;
        char repeatProceedWithTraining = 'Y';
        std::string proceedWithTrainingstdString;
        std::vector<char> proceedWithTrainingThree = {'P', 'S', 'M'};

        do {
          Lists newList(6);
          char proceedWithTraining = newList.listOfActions();
          std::cout << std::endl;

          switch (proceedWithTraining) {
          case 'P': {
            bool trainingIsSuccess = province -> subtractCheckResources(requiredResources);

            if (trainingIsSuccess == false) {
              std::cout << "Training failed" << std::endl;
              for (int a = 0; a < 5; a++) {
                province->addResources(requiredResources);
              }
            } else {
              std::cout << "Training successful" << std::endl;
              province->addSpecificTroop(troopTier - 1, amountOfTroops);
            }
            break;
          }
          case 'S': {
            province->printResources();
            break;
          }
          case 'M': {
            repeatProceedWithTraining = 'N';
            province->addTroopsTrainedThisTurn(amountOfTroops);
            std::cout << "Returning to menu... " << std::endl;
          }
          }
        } while (repeatProceedWithTraining == 'Y');
      } else {
        repeatOuterDoLoop = 'Y';
        std::cout << "Amount of troops selected exceeds the training capacity "
                     "of the barracks... please try again"
                  << std::endl;
      }
    } while (repeatOuterDoLoop == 'Y');
  }
}

