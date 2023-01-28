#include <iostream>
#include <vector>
#include "Participants.h"
#include "otherFunctions.h"
#include "coordinateFunctions.h"

using namespace std;
extern int currentParticipantIndex;
extern int initialResources [5];
extern vector <vector <Provinces*>> provincesMap;

//Constructors
Participants::Participants()
{
  createCapital();
	addCommander();
	initialCapRSS();
  setKingdomName();
}
void Participants::createCapital()
{
	  /*For each participant, generate random x and y values, see if the province associated with these values (coordinates) is empty. If it's empty, change the province identifier and add it to a partipant's list of provinces. If it's not empty, repeatMap is 'Y' and the process repeats*/

	int xCoord = getRandomCoordinate();
	int yCoord = getRandomCoordinate();
	Provinces *newProvince = provincesMap[xCoord][yCoord];
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

int Participants::findCommanderIndex(string commanderName)
{
  for (int x = 0; x < commandersNum(); x++) /*find index of chosen commander unit*/
  {
		if (commanderName == commandersList[x]->getUnitName())
		{
				return x;
		}
	}
	return -1;//if something goes wrong
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

void Participants::setKingdomName(string newName)
{
	if (kingdomName == " ")
    kingdomName = newName;
}

string Participants::getKingdomName()
{
    return kingdomName;
}