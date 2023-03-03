#include "Participants.h"

#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;


//Constructor
Participants::Participants ()
{
	createCapital();
	addCommander();
	initialCapRSS();
  setKingdomName("-1");
}
void Participants::createCapital()
{
	  /*For each participant, generate random x and y values, see if the province associated with these values (coordinates) is empty. If it's empty, change the province identifier and add it to a partipant's list of provinces. If it's not empty, repeatMap is 'Y' and the process repeats*/

	int xCoord = getRandomCoordinate();
	int yCoord = getRandomCoordinate();
	Provinces *newProvince = &provincesMap[xCoord][yCoord];
	if (newProvince->getBelongsToParticipant() == -1)
	{
		newProvince->changeBelongsToParticipant(p);
		addProvince(newProvince);
		setCapital(newProvince);
	}
	else
	{
		createCapital ();
	}
}

//Accessors
Provinces *Participants::getCapital()
{
  return provincesList[capitalIndex];
}
Provinces *Participants::findProvince(int x, int y)
{
  for (int a = 0; a < provincesList.size(); a++)
  {
		Provinces *newProvince = provincesList[a];
    if (x == newProvince->getCoordinate(0) && y == newProvince->getCoordinate(1))
      return newProvince;
  }
}

int Participants::provincesNum()
{
  return provincesList.size();
}
int Participants::commandersNum()
{
  commandersList.size();
}

int Participants::findCommanderIndex(CommanderProfile *commander)
{
  for (int x = 0; x < commandersNum(); x++) /*find index of chosen commander unit*/
  {
		if (&commander == &commandersList[x])
		{
				return x;
		}
	}
}
void Participants::initialCapRSS()
{
	
  //Add resources to enemy participants/players based on difficulty
  Provinces *newProvince = provincesList[capitalIndex]; 
  for (int resourceIndex = 0; resourceIndex < 5; resourceIndex++)
  {
    newProvince->addResources(resourceIndex, initialResources[resourceIndex]);
  }
}
//Mutators
void Participants::setCapital(Provinces *newProvince)
{
	for (int x = 0; x < provincesList.size(); x++)
	{
		if (provincesList[x] == newProvince)
		{
			capitalIndex = x;
			x = provincesList.size();
		}
	}
}

void Participants::addProvince(Provinces *newProvince)
{
  provincesList.push_back(newProvince);
}

void Participants::addCommander()
{
    CommanderProfile newCommander(1, getNewName());
    newCommander.changeCoordinates(getCapitalCoordinate('X'), getCapitalCoordinate('Y'));
    commandersList.push_back(newCommander);
}

void Participants::setKingdomName(std::string newName)
{
	if (newName == "-1")
	{
		newName = generateNewName(); //fix this-- add functionality
	}
  kingdomName = newName;
}

std::string Participants::getKingdomName()
{
    return kingdomName;
}

bool Participants::isAlive()
{
  if (provincesNum() > 0 && commandersNum() > 0)
  {
    return true;
  }
  return false;
}

void Participants::createAsPlayer(bool choice)
{
	playerStatus = choice;
}

void Participants::viewStats()
{
    std::cout << "Kingdom name: " << kingdomName << "\n\n";
    int totalPlayerUnits[5];
    findTotalPlayerUnits(totalPlayerUnits);
    
    for (int x = 0; x < 5; x++){
        std::cout << "Total " << provinceResourcesNames[x] << ": " << totalPlayerResources[x] << std::endl;}
    
    std::cout << std::endl;
    
    for (int x = 0; x < 5; x++){
        std::cout << "Total " << troopNames[x] << " alive: " << totalPlayerUnits[x] << std::endl;}
    
    std::cout << "Your total army combat power: " << calculatePlayerValues(1) << std::endl;
    std::cout << "Your numnber of provinces: " << participantsList[0]->provincesNum() << "\n\n";

    switch (getChar("View all stats? (Y/N) ", "YN", 1)){
    case 'Y':
        viewAllStatsFunction();
    case 'N':
        std::cout << "Returning to menu" << std::endl;
        break;}
}

std::vector<int> Participants::calculatePlayerValues(int decision)
{
    switch (decision)
    {
    case 1:
    {
			return totalUnits;
    }
    case 2:
    {
        return troopsLost;
    }
    }
}

Provinces *Participants::getProvince(int index)
{
	return provincesList[index];
}

std::string Participants::getNewName()
{
	std::string newName = createRandomName();
	//cout << "Check provinces" << std::endl;
	for (int x = 0; x < participant->provincesNum(); x++) //If any provinces of the participant have the name
	{
		Provinces* newProvince = participant->getProvince(x);
		if (newName == newProvince -> getProvinceName())
		{
			getNewName();
		}
	}
	//cout << "Check commanders" << std::endl;
	for (int x = 0; x < participant->commandersNum(); x++)
	{
		CommanderProfile* newCommander = &allCommanders[currentParticipantIndex][x];
		if (newName == newCommander->getUnitName())
		{
			getNewName();
		}
	}
	return newName;

}

CommanderProfile *Participants::getCommander(int index)
{
	return commandersList[index];
}

std::vector <int> Participants::getTrainCosts ()
{
	return trainCosts;
}

int Participants::getMaxCommanders()
{
	return maxCommanders;
}

void Participants::setParticipantIndex(int num)
{
	participantIndex = num;
}

int Participants::getParticipantIndex()
{
	return participantIndex;
}

void Participants::viewAllStatsFunction()
{
    std::string literallyAnyRandomCharacter;
    std::cout << "\033[;34m";//NW
    for (int x = 0; x < 5; x++)
    {
        std::cout << troopNames[x] << " lost: " << participantsList[currentParticipantIndex].playerTroopsLost[x] << std::endl;
    }
    std::cout << "Total troops lost: " << calculatePlayerValues(2) << std::endl << std::endl;
    std::cout << "\033[;0m";//NW

    std::cout << "Enter any character to go back to the Main menu: ";
    std::cout << "\033[31m";
    getline(cin, literallyAnyRandomCharacter);
    std::cout << "\033[0m";
}

void Participants::printListOfProvinces()
{
    std::cout << "Here is a list of your provinces: " << std::endl;
    int x;
    int y;
    for (int a = 0; a < continentSize; a++)
    {
        for (int b = 0; b < continentSize; b++)
        {
            if (provincesMap[a][b].getBelongsToParticipant() == currentParticipantIndex)
            {
                x = translateCoordinate(b, 'x', 'O');
                y = translateCoordinate(a, 'y', 'O');
                std::cout << "(" << x << ", " << y << ") " << std::endl;
            }
        }
    }
    std::cout << std::endl;
}
Provinces *Participants::getYourCoords(int identifier)
{
	Provinces* newProvince = getCoords(identifier);
	if (newProvince->getParticipantIndex = participantIndex)
	{
		return newProvince;
	}
	std::cout<< "This province does not belong to you. Please try again \n";
	getYourCoords(identifier);
}
Provinces* Participants::getCoords(int identifier) {
	OtherFunctions OF;
	int yCoordinate = -1;
  std::vector<int> actualCoordinatesAVTwo = {-1};
  for (int x = 1; x <= continentSize; x++) {
    actualCoordinatesAVTwo.push_back(x);
  }
  OF.showMap();
  std::string phrase;
  switch (identifier) {
  case 1:
    OF.printListOfProvinces();
    phrase = "of the province you want to select";
    break;
  case 2:
    OF.printListOfProvinces();
    phrase = "of the province you want to move to";
    break;
  case 3:
    phrase = "of the army you want to use to attack the target with";
  }
  int xCoordinate = getInt("Enter the x coordinate " + phrase + "(Enter '-1' to go back to previous menu) : ", actualCoordinatesAVTwo, 2);
  // Critical: check to make sure the coordinate checkings are correct
  if (xCoordinate != -1 && xCoordinate < continentSize && xCoordinate >= 0) {
    yCoordinate =
        getInt("Enter the y coordinate " + phrase + " (Enter '-1' to go back to previous menu) : ", actualCoordinatesAVTwo, 2);
    std::cout << std::endl;
    if (yCoordinate != -1 && yCoordinate < continentSize && yCoordinate >= 0) {
      int replacement = xCoordinate;
      xCoordinate = translateCoordinate(yCoordinate, 'y', 'I');
      yCoordinate = translateCoordinate(replacement, 'x', 'I');
			Provinces *newProvince = &provincesMap[xCoordinate][yCoordinate];
      return newProvince;
    }
  }
	if (xCoordinate == -1 || yCoordinate == -1)
	{
		Provinces* newProvince = &provincesMap[xCoordinate][yCoordinate];
		newProvince->setDeleteProvince();
		return newProvince;
	}
  getCoords(identifier);
           // object that gets delted later
} // Can make this an array

int Participants::getRandomCoordinate() { return rand() % continentSize; }


bool Participants::hasCommander(std::string name)
{
	for (int x = 0; x < commandersList.size(); x++)
	{
		if (name == commandersList[x]->getName())
		{
			return true;
		}
	}
	return false;
}

CommanderProfile* Participants::getCommanderName(std::string name)
{
	for (int x = 0; x < commandersList.size(); x++)
	{
		if (name == commandersList[x]->getName())
		{
			return commandersList[x];
		}
	}
}