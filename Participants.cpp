#include "Participants.h"


using namespace std;
extern int currentParticipantIndex;
extern int initialResources [5];
extern std::vector <std::vector <Provinces>> provincesMap;

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
        std::cout << "Total " << provinceResourcesNames[x] << ": " << totalPlayerResources[x] << endl;}
    
    std::cout << endl;
    
    for (int x = 0; x < 5; x++){
        std::cout << "Total " << troopNames[x] << " alive: " << totalPlayerUnits[x] << endl;}
    
    std::cout << "Your total army combat power: " << calculatePlayerValues(1) << endl;
    std::cout << "Your numnber of provinces: " << participantsList[0]->provincesNum() << "\n\n";

    switch (getChar("View all stats? (Y/N) ", "YN", 1)){
    case 'Y':
        viewAllStatsFunction();
    case 'N':
        std::cout << "Returning to menu" << endl;
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
	//cout << "Check provinces" << endl;
	for (int x = 0; x < participant->provincesNum(); x++) //If any provinces of the participant have the name
	{
		Provinces* newProvince = participant->getProvince(x);
		if (newName == newProvince -> getProvinceName())
		{
			getNewName();
		}
	}
	//cout << "Check commanders" << endl;
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
        std::cout << troopNames[x] << " lost: " << participantsList[currentParticipantIndex].playerTroopsLost[x] << endl;
    }
    std::cout << "Total troops lost: " << calculatePlayerValues(2) << endl << endl;
    std::cout << "\033[;0m";//NW

    std::cout << "Enter any character to go back to the Main menu: ";
    std::cout << "\033[31m";
    getline(cin, literallyAnyRandomCharacter);
    std::cout << "\033[0m";
}

void Participants::printListOfProvinces()
{
    std::cout << "Here is a list of your provinces: " << endl;
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
                std::cout << "(" << x << ", " << y << ") " << endl;
            }
        }
    }
    std::cout << endl;
}