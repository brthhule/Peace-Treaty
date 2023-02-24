#include "coordinateFunctions.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << endl;

using namespace std;
extern std::vector<std::vector<Provinces>> provincesMap;
extern int provinceBuildingsProductionNumbers[6];
extern int continentSize;
extern int troopsCP[5];
extern std::vector<Participants> participantsList;

int translateCoordinate(int coordinate, char indicator, char whichWay) {
  /*replacement = xCoordinate;
  xCoordinate = translateCoordinate(yCoordinate, 'y', 'I');
  yCoordinate = translateCoordinate (replacement, 'x', 'I');*/
  int translation = 0;
  switch (whichWay) {
  case 'I':
    switch (indicator) {
    case 'x':
      translation = coordinate - 1;
      break;

    case 'y':
      translation = coordinate - continentSize;
      translation = abs(translation);
      break;
    }
    break;
  case 'O':
    switch (indicator) {
    case 'x':
      translation = coordinate + 1;
      break;
    case 'y':
      translation = continentSize - coordinate;
      translation = abs(translation);
      break;
    }
    break;
  }
  return translation;
}

std::vector<int> getCoords(int identifier) {
	int yCoordinate = -1;
  std::vector<int> actualCoordinatesAVTwo = {-1};
  for (int x = 1; x <= continentSize; x++) {
    actualCoordinatesAVTwo.push_back(x);
  }
  showMap();
  std::string phrase;
  switch (identifier) {
  case 1:
    printListOfProvinces();
    phrase = "of the province you want to select";
    break;
  case 2:
    printListOfProvinces();
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
    std::cout << endl;
    if (yCoordinate != -1 && yCoordinate < continentSize && yCoordinate >= 0) {
      int replacement = xCoordinate;
      xCoordinate = translateCoordinate(yCoordinate, 'y', 'I');
      yCoordinate = translateCoordinate(replacement, 'x', 'I');
      return {xCoordinate, yCoordinate};
    }
  }
	if (xCoordinate == -1 || yCoordinate == -1)
	{
		return {-1,-1};
	}
  getCoords(identifier);
           // object that gets delted later
} // Can make this an array

int getRandomCoordinate() { return rand() % continentSize; }
