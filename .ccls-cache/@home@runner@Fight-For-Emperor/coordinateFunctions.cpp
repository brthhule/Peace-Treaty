#include "coordinateFunctions.h"


using namespace std;
extern vector<vector <Provinces*>> provincesMap;
extern int provinceBuildingsProductionNumbers[6];
extern int continentSize;
extern int troopsCP[5];
extern vector <Participants> participantsList;

int translateCoordinate(int coordinate, char indicator, char whichWay)
{
    /*replacement = xCoordinate;
    xCoordinate = translateCoordinate(yCoordinate, 'y', 'I');
    yCoordinate = translateCoordinate (replacement, 'x', 'I');*/
    int translation = 0;
    switch (whichWay)
    {
    case 'I':
        switch (indicator)
        {
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
        switch (indicator)
        {
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

Provinces* getCoords(int identifier)/*Add funcitonality to add safety incase innvalid values are entered for the coordinates*/
{
    vector<int> actualCoordinatesAVTwo = {-1};
    for (int x = 1; x <= continentSize; x++)
    {
        actualCoordinatesAVTwo.push_back(x);
    }
    showMap();
    string phrase;
    switch (identifier)
    {
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
    std::cout << "Enter the x coordinate " << phrase << " (Enter '-1' to go back to previous menu) : ";
    int xCoordinate = getInt("Replacement", actualCoordinatesAVTwo, 2);
    cout << "X: " << xCoordinate << endl;
    if (xCoordinate != -1)
    {
        std::cout << "Enter the y coordinate " << phrase << " (Enter '-1' to go back to previous menu) : ";
        int yCoordinate = getInt("Replacement", actualCoordinatesAVTwo, 2);
        std::cout << endl;
        cout << "Y: " << yCoordinate << endl;
 
        if (yCoordinate != -1)
        {
            int replacement = xCoordinate;
            xCoordinate = translateCoordinate(yCoordinate, 'y', 'I');
            yCoordinate = translateCoordinate(replacement, 'x', 'I');
          return provincesMap[xCoordinate][yCoordinate];
        }
    }
    exit(0);//May need to use an alternative method by using a fake Provinces object that gets delted later
}//Can make this an array

int getRandomCoordinate()
{
    return rand() % continentSize;
}
