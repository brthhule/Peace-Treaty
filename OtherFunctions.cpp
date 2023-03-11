#include "OtherFunctions.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

OtherFunctions::OtherFunctions() {}

std::string OtherFunctions::getInput(std::string text, std::vector<std::string> AV, bool redo) {
	std::string input;
	if (redo == false)
	{
		std::cout << text;
		std::cout << "\033[31m";
	  std::getline(std::cin, input);
	  std::cout << "\033[0m";
	} else
	{
		std::cout << std::endl;
    std::cout << "Invalid character entered. Please try again. " << std::endl;
    std::cout << "Please enter a valid character: ";
    std::cout << "\033[31m";
    std::getline(std::cin, input);
    std::cout << "\033[0m";
	}

	for (int x = 0; x < AV.size(); x++)
	{
		if (input == AV[x])
			return input;
	}
	getInput(text, AV, true);
}

std::string OtherFunctions::createRandomName() {
  std::string name = "";
	std::string consonants = "bcdfghjklmnpqrstvwxyz";
	std::string vowels = "aeiou";
	
  char newCharacter = ' ';
  for (int x = 0; x < 4; x++) {
    if (x % 2 == 0) // if even
    {
      newCharacter = consonants.at(rand() % 21);
    } else if (x % 2 == 1) // if odd
    {
      newCharacter = vowels.at(rand() % 5);
    }
    if (x == 0) {
      newCharacter = toupper(newCharacter);
    }
    name += newCharacter;
  }
  return name;
}



void OtherFunctions::clearScreen() {
  std::cout << "\033[32m";
  std::cout << "Clearing screen. " << std::endl;
  std::cout << "\033[0m";
  std::chrono::seconds dura(1);
  std::this_thread::sleep_for(dura);
  system("clear"); /*Non-Windows*/
}



int OtherFunctions::translateCoordinate(int coordinate, char indicator, char whichWay) {
  /*replacement = xCoordinate;
  xCoordinate = translateCoordinate(yCoordinate, 'y', 'I');
  yCoordinate = translateCoordinate (replacement, 'x', 'I');*/
  int translation = 0;
  switch (whichWay) {
  case 'I':
    return translateCoordinateInput(coordinate, indicator);
    break;
  case 'O':
    return translateCoordinateOutput(coordinate, indicator);
    break;
  }
}

int OtherFunctions::translateCoordinateInput(int coordinate, char indicator) {
  switch (indicator) {
  case 'x':
    return coordinate - 1;
    break;
  case 'y':
    return abs(coordinate - continentSize);
    break;
  }
}

int OtherFunctions::translateCoordinateOutput(int coordinate, char indicator) {
  switch (indicator) {
  case 'x':
    return coordinate + 1;
    break;
  case 'y':
    return abs(continentSize - coordinate);
    break;
  }
}

void OtherFunctions::printCoordinates(int xCoordinate, int yCoordinate)
{
	OtherFunctions OF;
  std::cout << "(" << OF.translateCoordinate(xCoordinate, 'x', 'O') << ", " << OF.translateCoordinate(yCoordinate, 'y', 'O') << ") ";
}

std::vector<int> OtherFunctions::addVectors(std::vector<int> primeVector, std::vector<int> secondaryVector)
{
	for (int x = 0; x < primeVector.size(); x++)
		primeVector[x] += secondaryVector[x];
	return primeVector;
}
std::vector<int> OtherFunctions::subtractVectors(std::vector<int> primeVector, std::vector<int> secondaryVector)
{
	for (int x = 0; x < primeVector.size(); x++)
		primeVector[x] -= secondaryVector[x];
	return primeVector;
}