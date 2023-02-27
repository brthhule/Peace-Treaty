#include "OtherFunctions.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

OtherFunctions::OtherFunctions() {}

void OtherFunctions::showMap() {
  std::cout << "Map: " << std::endl;
  int thingy = continentSize;
  for (int x = 0; x < continentSize; x++) {
    // Y axis stuff
    if (thingy < 10) {
      std::cout << " " << thingy << "| ";
    } else {
      std::cout << thingy << "| ";
    }
    thingy--;
    // End y axis stuff

    for (int y = 0; y < continentSize; y++) {
      char letter = ' '; // Fix this later
      char identifierThingy = ' ';
      if (provincesMap[x][y].getParticipantIndex() == currentParticipantIndex) {
        std::cout << "\033[;34m";
        identifierThingy = 'H';
        if (provincesMap[x][y].isCapital() == true) {
          letter = 'P';
        } else {
          letter = 'p';
        }
      } else if (provincesMap[x][y].getParticipantIndex() != -1) {
        std::cout << "\033[;31m";
        identifierThingy = 'V';
        if (provincesMap[x][y].isCapital() == true) {
          letter = 'E';
        } else {
          letter = 'e';
        }
      } else {
        letter = '0';
      }
      if (provincesMap[x][y].commandersNum() == 0) {
        std::cout << letter << "   ";
      } else {
        if (provincesMap[x][y].commandersNum() <= 9) {
          std::cout << letter << identifierThingy
                    << provincesMap[x][y].commandersNum() << " ";
        } else {
          std::cout << letter << identifierThingy << "* ";
        }
      }
      std::cout << "\033[;0m";
    }
    std::cout << std::endl;
  }

  // X axis stuff
  std::cout << "    ";
  for (int a = 0; a < continentSize - 1; a++) {
    std::cout << "----";
  }
  std::cout << "-";
  std::cout << std::endl;
  std::cout << "    ";
  for (int a = 0; a < continentSize; a++) {
    if (a < 8) {
      std::cout << a + 1 << "   ";
    } else
      std::cout << a + 1 << "  ";
  }
  std::cout << "\n\n";
}

void OtherFunctions::updateprovinceResources() {
  for (int x = 0; x < continentSize; x++) {
    for (int y = 0; y < continentSize; y++) {
      provincesMap[x][y].updateBuildingsProduction();
      provincesMap[x][y].updateProvinceResources();
    }
  }
}

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
	getInput(text, AV, isChar, true);
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

void OtherFunctions::createMap() {
  /*Basically create the map-- make each province an object of Provinces*/
  for (int x = 0; x < continentSize; x++) {
    std::vector<Provinces> vectorThingy;
    provincesMap.push_back(vectorThingy);
    for (int y = 0; y < continentSize; y++) {
      Provinces newProvince(x, y, -1);
      provincesMap[x].push_back(newProvince);
    }
  }
}

void OtherFunctions::clearScreen() {
  std::cout << "\033[32m";
  std::cout << "Clearing screen. " << std::endl;
  std::cout << "\033[0m";
  std::chrono::seconds dura(1);
  std::this_thread::sleep_for(dura);
  system("clear"); /*Non-Windows*/
}

void OtherFunctions::pauseGame() {
  std::string gameCode;
  gameCode += continentSize;

  for (int x = 0; x < continentSize; x++) {
    for (int y = 0; y < continentSize; y++) {
      gameCode += provincesMap[x][y].getParticipantIndex();
    }
  }
  std::cout << "Game ended... \nHere is your game code (Copy this code and "
               "paste it when using the 'Resume Game' functionality): "
            << gameCode << "\n\n";
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