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
	} 
	else if (redo == true)
	{
		std::cout << std::endl;
    std::cout << "Invalid character entered. Please try again. " << std::endl;
    std::cout << "Please enter a valid character: ";
    std::cout << "\033[31m";
    std::getline(std::cin, input);
    std::cout << "\033[0m";
	}

  if (input.length() == 1 && AV[0] == "letter")
	{
		char letter = toupper(input.at(0));
		input.clear();
		input.push_back(letter);
	}


  // if (AV[0] != "number")
  	for (std::string option: AV)
  		if (input == option)
  			return input;
  // else
  //   for (int number: AVInt)
  //     if (number == inputInt)
  //       return std::to_string(inputInt);
	
  return getInput(text, AV, true);
  
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

std::string OtherFunctions::printCoordinates(std::array<int, 2> coordinates)
{
  std::string x = std::to_string(translateCoordinate(coordinates[0], 'x', 'O'));
  std::string y = std::to_string(translateCoordinate(coordinates[1], 'y', 'O'));
	std::string coordinatesString = "(" + x + ", " + y + ") ";
	return coordinatesString;
}

std::vector<int> modifyVector(std::vector<int> primeVector, std::vector<int> secondaryVector, bool isAdd)
{
	if (isAdd)
		for (int &x: primeVector)
			x += secondaryVector[x];
	else
		for (int &x: primeVector)
			x -= secondaryVector[x];
	return primeVector;
}

std::array<int, 5> OtherFunctions::modifyArray(std::array<int, 5> primeArray, std::array<int, 5> secondaryArray, bool isAdd)
{
	if (isAdd)
		for (int &x: primeArray)
			x += secondaryArray[x];
	else
		for (int &x: primeArray)
			x -= secondaryArray[x];
	return primeArray;
}

void OtherFunctions::printResources(std::array<int, 5> resourcesArray)
{
	for (int x = 0; x < 5; x++)
		std::cout << "- " << CV.RESOURCE_NAMES[x] << ": " << resourcesArray[x] <<  std::endl;
	
	std::cout <<  std::endl;
}

void OtherFunctions::enterAnything()
{
	std::string emptyString = " ";
	std::cout << "Enter anything to return to the previous menu: \033[31m";
	getline(std::cin, emptyString);
	println("\n\033[0m")
}