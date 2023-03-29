#include "Lists.h"

Lists::Lists(int num) { identifier = num; }
char Lists::listOfActions() // print out what actions a player can do
{
  std::vector<std::string> vectorToSend;
  /*cout << "- ()\n";*/
  /*HANDLE console_color;
  console_color = GetStdHandle(STD_OUTPUT_HANDLE); //WO
  SetConsoleTextAttribute(console_color, 12);*/
  std::cout << "\033[;31m---------- List of Operations: ----------\n";
  switch (identifier) {
  case 1: /*selectEnemyAction*/
  {
    std::cout << "- Attack this province (A) \n";
    std::cout << "- Scout this province (S) \n";
		vectorToSend = {"A", "S"};
    break;
  }
  case 2: /*playerUnitAction*/
  {
    std::cout << "- Move this unit (P)\n";
    vectorToSend = {"P"};
    break;
  }
  case 3: /*introduction*/
  {
    std::cout << "- Start a new game (S)\n";
    std::cout << "- Resume a previous game (R)\n";
    vectorToSend = {"S","R"};
    break;
  }
  case 4: /*playerAction*/
  {
    std::cout << "- Buildings (B)\n";
    std::cout << "- Training (T)\n";
    std::cout << "- Stats (S)\n";
    std::cout << "- Select Unit (U)\n";
    std::cout << "- Deployment (D)\n";
    std::cout << "- Next Turn (N)\n";
    std::cout << "- Pause (P)\n";
    vectorToSend = {"B", "T", "S", "U", "D", "N", "P"};
    break;
  }
  case 5: /*armyDeployment*/
  {
    std::cout << "- Train a commander (T)\n";
    std::cout << "- Upgrade a commander (U)\n";
    std::cout << "- View army overview (V)\n";
    std::cout << "- Deploy a commander (D)\n";
    vectorToSend = {"T", "U", "V", "D"};
    break;
  }
  case 6: /*TrainMAFunction*/
  {
    std::cout << "- Proceed with training (P)\n";
    std::cout << "- See the amount of resources in this province (S)\n";
    vectorToSend = {"P", "S"};
    break;
  }
  case 7: /*playerBuildFunction*/
  {
    std::cout << "- Upgrade a building (U)\n";
    vectorToSend = { "U"};
    break;
  }
  case 8: /*viewPlayerMap*/
  {
    std::cout << "- Pick a province (P)\n";
    vectorToSend = {"P"};
    break;
  }
  case 9: /*selectPlayerProvince*/
  {
    std::cout << "- Build infrastructure (B)\n";
    std::cout << "- Train Troops (T)\n";
    vectorToSend = {"B", "T"};
    break;
  }
  case 10: /*selectEnemyProvince*/
  {
    std::cout << "- Attack this province (A)\n";
    std::cout << "- Scout this province (S)\n";
    std::cout << "- View the scout log (V)\n";
    vectorToSend = {"A", "S", "V"};
    break;
  }
  case 11: /*scoutLogFunction*/
  {
    std::string SLFReports[3] = {"garrison", "resource", "building"};
    for (int x = 0; x < 3; x++) {
      std::cout << "- View the " << SLFReports << " report for this province (" << toupper(SLFReports[x].at(0)) << ")\n";
    }
    vectorToSend = {"G", "R", "B"};
    break;
  }
  }

  std::cout << "- Return to the previous menu (M)\n";
  std::cout << "-------------- End List: ---------------- \033[;0m\n\n";
  // SetConsoleTextAttribute(console_color, 15); //WO
  if (identifier != 3 && identifier != 4) {
    vectorToSend.push_back("M");
  }

	vectorToSend.push_back("H");

  std::vector <std::string> newVector;
  newVector.push_back("letter");
  for (std::string option: vectorToSend)
    newVector.push_back(option);
	
	return OF.getInput("Enter the letter of the action you want to complete (enter 'H' to see help to know what to do): ", newVector , false).at(0);
}







void Lists::listOfHelp() {
  std::cout << "\033[;34m ---------- Begin Help ----------\n";
  switch (identifier) {
  case 2: {
    std::cout << "- You can select to move one of your army units. Only army units deployed with an army commander can move (these are sent out via your capital). \n";
    std::cout << "- Garrisons cannot move, but they can be absorved into army units that are in the same province as an army. \n\n";
    std::cout << "- If you move an army unit to an empty province, the army unit takes over that province without resistance. \n";
    std::cout << "- If you move an army unit to an enemy province, the army unit will attack the enemy province. The army with the greater combat power will win, but the amount of losses and the types of troops lost will vary depending on troop composition. \n";
    std::cout << "- If you move an army unit to one of your provinces, you can absorb some of the garrison troops into the army as long as the army capacity is not exceeded. You can also merge troops from two or more different armies so long as they're in the same province, but there cannot be two army commanders in one army. \n\n";
    std::cout << "You can increase the size of an army by increasing the level of the army's commander (this can only be done when the army commander and their army are in the capital-- player action \"player deployment\"). \n";
    break;
  }
  case 3: {
    std::cout << "Start a new conquest (S):\n";
    std::cout << "- Start a new game\n";
    std::cout << "Resume a previous conquest (R):\n";
    std::cout << "- Enter a code/text file to import a game/generate a game with information from a previous play through\n";
    break;
  }
  case 4: // playerActionHelp
  {
    std::cout << "Build infrastructure (B):\n";
    std::cout << "- Select one of your provinces and build or upgrade one or several of the buildings in the province (Farm, Lumber Mill, Quarry, Mine, Church, and Barracks) \n\n";

    std::cout << "Train troops (T):\n";
    std::cout << "- Select one of your provinces and train troops\n";
    std::cout << "- The tier troop you can train depends on the level of the barracks in this province\n";
    std::cout << "- Your capital province automatically starts with a barracks level of 1. You can upgrade a province's barracks through the build infrastructure action. \n\n";

    std::cout << "View your stats (V):\n";
    std::cout << "- See your overall stats, including the total amount of resourcesand troops across all your provinces \n";
    std::cout << "- You can see the specific stats of each of your provinces through the view map action. \n\n";

    std::cout << "View the map (M):\n";
    std::cout << "- See a map of the continent. Help for the map is available in the map section. \n";
    std::cout << "- Through the map, you can see the specific stats of each of your province(such as resources and troops available in the province). \n";
    std::cout << "- You can also scoutand attack enemy provinces through this action. \n\n";

    std::cout << "View army deployment (A):\n";
    std::cout << "- Train army commanders here. The amount of army commanders you can have corresponds to the size of the continent. \n";
    std::cout << "- Through this action, you can also see the coordinates of each of your armiesand their specific stats. \n";
    std::cout << "- If an army is totally defeated, its army commander will dieand a new one will have to be trained \n\n";

    std::cout << "Go to the next turn (G):\n";
    std::cout << "- This a turn - based game.You can scout enemy provinces, train troops, view your stats, and build infrastructure as much as you'd like. \n";
    std::cout << "- However, you can only get new resources by going to the next turn, and each of your armies can only move once per turn. \n\n";

    std::cout << "Pause game (P):\n";
    std::cout << "- End the game and get a code to play again at another time. \n";
    break;
  }
  case 5: {
    std::cout << "Train a commander (T):\n";
    std::cout << "- The price of training a commander increases as the amount of commanders you have increases. You start off with one commander\n";
    // std::cout << "- The max limit of commanders you can train: " <<
    // maxAmountOfCommanders << std::endl << std::endl;

    std::cout << "Upgrade a commander (U):\n";
    std::cout << "- The price of upgrading a commander increases as the level of the commander increases\n";
    std::cout << "- There is no cap on how much you can upgrade a commander\n";
    std::cout << "- The greater the level of a commander, the more troops they can lead in their army (5 units per level) \n\n";

    std::cout << "View army overview (V):\n";
    std::cout << "- See all your armies (their coordinates and their stats)\n\n";

    std::cout << "Deploy a commander (D):\n";
    std::cout << "- Move commanders out of the capital and onto the map\n";
    break;
  }
  case 8: {
    std::cout << "On the map, each coordinate is a province that containes a type of unit (identified by a symbol). Here is a list of what each symbol on the map: \n\n";
    std::cout << "P) Your capital province\n";
    std::cout << "p) One of your provinces\n";
    std::cout << "E) Your enemy's capital province\n";
    std::cout << "e) One of your eneny's provinces\n";
    std::cout << "H) One of your army units\n";
    std::cout << "V) One of your enemy's army units\n\n";
		
    std::cout << "If there are two letters in one province, that means that there are two units there-- if a province has PH, that means the player capital province and a commander unit are there. The number next to the letter indicates how many commander units are in the province\n\n";
    std::cout << "Enter the x and y coordinates of the province you want to select. Depending on the type of province, you can build infrastructure, train troops, move armies, or attack armies. \n";
    std::cout << "------------ This is the end of the Help message ------------\n";
    break;
  }
  case 12: // upgradeBuildingsHelp
  {
    // finish this
    break;
  }
  }
  std::cout << "-------------- End Help ---------------- \033[;0m\n\n";
  OtherFunctions OF;
	OF.enterAnything();
}