#include "otherFunctions.h"

void showMap() {
  std::cout << "Map: " << endl;
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
        if (provincesMap[x][y].isProvinceACapitalQuestion() == 'Y') {
          letter = 'P';
        } else {
          letter = 'p';
        }
      } else if (provincesMap[x][y].getParticipantIndex() != -1) {
        std::cout << "\033[;31m";
        identifierThingy = 'V';
        if (provincesMap[x][y].isProvinceACapitalQuestion() == 'Y') {
          letter = 'E';
        } else {
          letter = 'e';
        }
      } else {
        letter = '0';
      }
      if (provincesMap[x][y].commandersPresentIndex.size() == 0) {
        std::cout << letter << "   ";
      } else {
        if (provincesMap[x][y].commandersPresentIndex.size() <= 9) {
          std::cout << letter << identifierThingy
               << provincesMap[x][y].commandersPresentIndex.size() << " ";
        } else {
          std::cout << letter << identifierThingy << "* ";
        }
      }
      std::cout << "\033[;0m";
    }
    std::cout << endl;
  }

  // X axis stuff
  std::cout << "    ";
  for (int a = 0; a < continentSize - 1; a++) {
    std::cout << "----";
  }
  std::cout << "-";
  std::cout << endl;
  std::cout << "    ";
  for (int a = 0; a < continentSize; a++) {
    if (a < 8) {
      std::cout << a + 1 << "   ";
    } else
      std::cout << a + 1 << "  ";
  }
  std::cout << endl;
  std::cout << endl;
}

void updateprovinceResources() {
  for (int x = 0; x < continentSize; x++) {
    for (int y = 0; y < continentSize; y++) {
      for (int z = 0; z < 5; z++) {
        provincesMap[x][y].updateBuildingsProduction();
        provincesMap[x][y].updateProvinceResources();
      }
    }
  }
}

int getInt(std::string textToDisplay, std::vector<int> acceptableValues,
           int caseInstance) {
  std::string userInput;
  if (caseInstance == 1) {
    std::cout << textToDisplay;
  }
  std::cout << "\033[31m";
  std::getline(std::cin, userInput);
  std::cout << "\033[0m";
  return checkInt(acceptableValues, userInput);
}
int checkInt(std::vector<int> &acceptableValuesTwo, std::string input) {
  std::vector<std::string> acceptableValuesOne;
  std::string foo = " ";
  for (int a = 0; a < acceptableValuesTwo.size(); a++) {
    foo = to_std::string(acceptableValuesTwo[a]);
    acceptableValuesOne.push_back(foo);
  }

  char repeat = 'Y';
  do {
    repeat = 'N';
    for (int x = 0; x < acceptableValuesOne.size(); x++) {
      if (input == acceptableValuesOne[x]) {
        repeat = 'N';
        return acceptableValuesTwo[x];
      }
    }
    repeat = 'Y';
    std::cout << endl;
    std::cout << "Invalid character entered. Please try again." << endl;
    std::cout << "Please enter a valid number: ";
    std::cout << "\033[31m";
    std::getline(std::cin, input);
    std::cout << "\033[0m";

  } while (repeat == 'Y');
  return -1;
}
char getChar(std::string textToDisplay, std::string acceptableValues, int caseInstance) {
  std::string userInput;
  if (caseInstance == 1) {
    std::cout << textToDisplay;
  }
  std::cout << "\033[31m";
  std::getline(std::cin, userInput);
  std::cout << "\033[0m";
  return checkChar(acceptableValues, userInput);
}
char checkChar(std::string std::stringAV, std::string input) {
  std::vector<char> acceptableValuesOne; /*Uppercase*/
  char inputTwo = ' ';

  for (int x = 0; x < std::stringAV.length(); x++) {
    acceptableValuesOne.push_back(std::stringAV.at(x));
  }

  char goodToGo = 'G';
  std::string character;
  do {
    goodToGo = 'G';
    if (input.length() == 1) {
      inputTwo = toupper(input.at(0));
      for (int x = 0; x < acceptableValuesOne.size(); x++) {
        if (inputTwo == acceptableValuesOne[x]) {
          goodToGo = 'G';
          return acceptableValuesOne[x];
        }
      }
    }
    goodToGo = 'B';

    std::cout << endl;
    std::cout << "Invalid character entered. Please try again. " << endl;
    std::cout << "Please enter a valid character: ";
    std::cout << "\033[31m";
    std::getline(std::cin, input);
    std::cout << "\033[0m";

  } while (goodToGo == 'B');
  return '1'; /*added this bc the debugger said that not all control paths
                 return a value*/
}

std::string createRandomName() {
  // std::cout << "Create random name" << endl;
  std::string name = "";
  int randomNumber = 0;
  char characterThingy = ' ';
  for (int x = 0; x < 4; x++) {
    if (x % 2 == 0) // if even
    {
      randomNumber = rand() % 21;
      characterThingy = findConsonant(randomNumber);
    } else if (x % 2 == 1) // if odd
    {
      randomNumber = rand() % 5;
      characterThingy = findVowel(randomNumber);
    }
    if (x == 0) {
      characterThingy = toupper(characterThingy);
    }
    name += characterThingy;
  }
  return name;
}
char findConsonant(int randomNumber) {
  char characterThingy = ' ';
  switch (randomNumber) {
  case 1:
    characterThingy = 'b';
    break;
  case 2:
    characterThingy = 'c';
    break;
  case 3:
    characterThingy = 'd';
    break;
  case 4:
    characterThingy = 'f';
    break;
  case 5:
    characterThingy = 'g';
    break;
  case 6:
    characterThingy = 'h';
    break;
  case 7:
    characterThingy = 'j';
    break;
  case 8:
    characterThingy = 'k';
    break;
  case 9:
    characterThingy = 'l';
    break;
  case 10:
    characterThingy = 'm';
    break;
  case 11:
    characterThingy = 'n';
    break;
  case 12:
    characterThingy = 'p';
    break;
  case 13:
    characterThingy = 'q';
    break;
  case 14:
    characterThingy = 'r';
    break;
  case 15:
    characterThingy = 's';
    break;
  case 16:
    characterThingy = 't';
    break;
  case 17:
    characterThingy = 'v';
    break;
  case 18:
    characterThingy = 'w';
    break;
  case 19:
    characterThingy = 'x';
    break;
  case 20:
    characterThingy = 'y';
    break;
  case 21:
    characterThingy = 'z';
    break;
  }

  return characterThingy;
}
char findVowel(int randomNumber) {
  char characterThingy = ' ';
  switch (randomNumber) {
  case 1:
    characterThingy = 'a';
    break;
  case 2:
    characterThingy = 'e';
    break;
  case 3:
    characterThingy = 'i';
    break;
  case 4:
    characterThingy = 'o';
    break;
  case 5:
    characterThingy = 'u';
    break;
  }
  return characterThingy;
}

void createMap() {
  /*Basically create the map-- make each province an object of Provinces*/
  for (int x = 0; x < continentSize; x++) {
    std::vector<Provinces> std::vectorThingy;
    provincesMap.push_back(std::vectorThingy);
    for (int y = 0; y < continentSize; y++) {
      Provinces newProvince(x, y, -1);
      provincesMap[x].push_back(newProvince);
    }
  }
}

void clearScreen() {
  std::cout << "\033[32m";
  std::cout << "Clearing screen. " << endl;
  std::cout << "\033[0m";
  chrono::seconds dura(1);
  this_thread::sleep_for(dura);
  // system("cls"); /*Windows only*/
  system("clear"); /*Non-Windows*/
}

void pauseGame() {
  std::string gameCode;
  gameCode += continentSize;

  for (int x = 0; x < continentSize; x++) {
    for (int y = 0; y < continentSize; y++) {
      gameCode += provincesMap[x][y].getParticipantIndex();
    }
  }
  std::cout << "Game ended... \nHere is your game code (Copy this code and "
               "paste it when using the 'Resume Game' functionality): "
            << gameCode << endl
            << endl;
}