#include "Lists.h"

Lists::Lists(int num) { identifier = num; }
char Lists::listOfActions() // print out what actions a player can do
{
  std::string std::stringToSend = " ";
  /*cout << "- ()" << std::endl;*/
  /*HANDLE console_color;
  console_color = GetStdHandle(STD_OUTPUT_HANDLE); //WO
  SetConsoleTextAttribute(console_color, 12);*/
  std::cout << "\033[;31m---------- List of Operations: ----------" << std::endl;
  switch (identifier) {
  case 1: /*selectEnemyAction*/
  {
    std::cout << "- Attack this province (A) " << std::endl;
    std::cout << "- Scout this province (S) " << std::endl;
    break;
  }
  case 2: /*playerUnitAction*/
  {
    std::cout << "- Move this unit (P)" << std::endl;
    std::stringToSend = "P";
    break;
  }
  case 3: /*introduction*/
  {
    std::cout << "- Start a new conquest (S)" << std::endl;
    std::cout << "- Resume a previous conquest (R)" << std::endl;
    std::stringToSend = "SR";
    break;
  }
  case 4: /*playerAction*/
  {
    std::cout << "- Buildings (B) " << std::endl;
    std::cout << "- Training (T) " << std::endl;
    std::cout << "- Stats (S) " << std::endl;
    std::cout << "- Select Unit (U) " << std::endl;
    std::cout << "- Deployment (D) " << std::endl;
    std::cout << "- Next Turn (N)" << std::endl;
    std::cout << "- Pause (P) " << std::endl;
    std::stringToSend = "BTSUDNP";
    break;
  }
  case 5: /*armyDeployment*/
  {
    std::cout << "- Train a commander (T) " << std::endl;
    std::cout << "- Upgrade a commander (U) " << std::endl;
    std::cout << "- View army overview (V) " << std::endl;
    std::cout << "- Deploy a commander (D) " << std::endl;
    std::stringToSend = "TUVDHM";
    break;
  }
  case 6: /*TrainMAFunction*/
  {
    std::cout << "- Proceed with training (P) " << std::endl;
    std::cout << "- See the amount of resources in this province (S) " << std::endl;
    std::stringToSend = "PSM";
    break;
  }
  case 7: /*playerBuildFunction*/
  {
    std::cout << "- Upgrade a building (U) " << std::endl;
    std::stringToSend = "UM";
    break;
  }
  case 8: /*viewPlayerMap*/
  {
    std::cout << "- Pick a province (P) " << std::endl;
    std::stringToSend = "PM";
    break;
  }
  case 9: /*selectPlayerProvince*/
  {
    std::cout << "- Build infrastructure (B) " << std::endl;
    std::cout << "- Train Troops (T) " << std::endl;
    std::stringToSend = "BTM";
    break;
  }
  case 10: /*selectEnemyProvince*/
  {
    std::cout << "- Attack this province (A) " << std::endl;
    std::cout << "- Scout this province (S) " << std::endl;
    std::cout << "- View the scout log (V) " << std::endl;
    std::stringToSend = "ASVM";
    break;
  }
  case 11: /*scoutLogFunction*/
  {
    std::string SLFReports[3] = {"garrison", "resource", "building"};
    for (int x = 0; x < 3; x++) {
      std::cout << "- View the " << SLFReports << " report for this province ("
                << toupper(SLFReports[x].at(0)) << ") " << std::endl;
    }
    std::stringToSend = "GRBM";
    break;
  }
  }
  std::cout << "-------------- End List: ---------------- \033[;0m" << std::endl
            << std::endl;

  std::cout << "- Return to the previous menu (M) " << std::endl;
  // SetConsoleTextAttribute(console_color, 15); //WO
  if (identifier != 3 && identifier != 4) {
    std::stringToSend += "MH";
  }
  return getChar("Enter the letter of the action you want to complete (enter "
                 "'H' to see help to know what to do): ",
                 std::stringToSend, 1);
}

void Lists::listOfHelp() {
  std::cout << "\033[;34m ---------- Begin Help ----------" << std::endl;
  switch (identifier) {
  case 2: {
    std::cout << "- You can select to move one of your army units. Only army units "
            "deployed with an army commander can move (these are sent out via "
            "your capital). "
         << std::endl;
    std::cout << "- Garrisons cannot move, but they can be absorved into army units "
            "that are in the same province as an army. "
         << std::endl
         << std::endl;
    std::cout << "- If you move an army unit to an empty province, the army unit "
            "takes over that province without resistance. "
         << std::endl;
    std::cout << "- If you move an army unit to an enemy province, the army unit "
            "will attack the enemy province. The army with the greater combat "
            "power will win, but the amount of losses and the types of troops "
            "lost will vary depending on troop composition. "
         << std::endl;
    std::cout << "- If you move an army unit to one of your provinces, you can "
            "absorb some of the garrison troops into the army as long as the "
            "army capacity is not exceeded. You can also merge troops from two "
            "or more different armies so long as they're in the same province, "
            "but there cannot be two army commanders in one army. "
         << std::endl;
    std::cout << std::endl;
    std::cout << "You can increase the size of an army by increasing the level of "
            "the army's commander (this can only be done when the army "
            "commander and their army are in the capital-- player action "
            "'player deployment'). "
         << std::endl;
    break;
  }
  case 3: {
    std::cout << "Start a new conquest (S): " << std::endl;
    std::cout << "- Start a new game" << std::endl;
    std::cout << "Resume a previous conquest (R): " << std::endl;
    std::cout << "- Enter a code/text file to import a game/generate a game with "
            "information from a previous play through"
         << std::endl;
    break;
  }
  case 4: // playerActionHelp
  {
    std::cout << "Build infrastructure (B): " << std::endl;
    std::cout << "- Select one of your provincesand build or upgrade one or several "
            "of the buildings in the province (Farm, Lumber Mill, Quarry, "
            "Mine, Church, and Barracks) "
         << std::endl
         << std::endl;

    std::cout << "Train troops (T): " << std::endl;
    std::cout << "- Select one of your provinces and train troops " << std::endl;
    std::cout << "- The tier troop you can train depends on the level of the "
            "barracks in this province"
         << std::endl;
    std::cout << "- Your capital province automatically starts with a barracks "
            "level of 1. You can upgrade a province's barracks through the "
            "build infrastructure action. "
         << std::endl
         << std::endl;

    std::cout << "View your stats (V): " << std::endl;
    std::cout << "- See your overall stats, including the total amount of "
            "resourcesand troops across all your provinces "
         << std::endl;
    std::cout << "- You can see the specific stats of each of your provinces "
            "through the view map action. "
         << std::endl
         << std::endl;

    std::cout << "View the map (M): " << std::endl;
    std::cout << "- See a map of the continent. Help for the map is available in "
            "the map section. "
         << std::endl;
    std::cout << "- Through the map, you can see the specific stats of each of your "
            "province(such as resources and troops available in the province). "
         << std::endl;
    std::cout << "- You can also scoutand attack enemy provinces through this "
            "action. "
         << std::endl
         << std::endl;

    std::cout << "View army deployment (A): " << std::endl;
    std::cout << "- Train army commanders here. The amount of army commanders you "
            "can have corresponds to the size of the continent. "
         << std::endl;
    std::cout << "- Through this action, you can also see the coordinates of each "
            "of your armiesand their specific stats. "
         << std::endl;
    std::cout << "- If an army is totally defeated, its army commander will dieand "
            "a new one will have to be trained "
         << std::endl
         << std::endl;

    std::cout << "Go to the next turn (G): " << std::endl;
    std::cout << "- This a turn - based game.You can scout enemy provinces, train "
            "troops, view your stats, and build infrastructure as much as "
            "you'd like. "
         << std::endl;
    std::cout << "- However, you can only get new resources by going to the next "
            "turn, and each of your armies can only move once per turn. "
         << std::endl
         << std::endl;

    std::cout << "Pause game (P): " << std::endl;
    std::cout << "- End the game and get a code to play again at another time. "
         << std::endl;
    break;
  }
  case 5: {
    std::cout << "Train a commander (T): " << std::endl;
    std::cout << "- The price of training a commander increases as the amount of "
            "commanders you have increases. You start off with one commander"
         << std::endl;
    // std::cout << "- The max limit of commanders you can train: " <<
    // maxAmountOfCommanders << std::endl << std::endl;

    std::cout << "Upgrade a commander (U): " << std::endl;
    std::cout << "- The price of upgrading a commander increases as the level of "
            "the commander increases"
         << std::endl;
    std::cout << "- There is no cap on how much you can upgrade a commander" << std::endl;
    std::cout << "- The greater the level of a commander, the more troops they can "
            "lead in their army (5 units per level) "
         << std::endl
         << std::endl;

    std::cout << "View army overview (V): " << std::endl;
    std::cout << "- See all your armies (their coordinates and their stats)" << std::endl
         << std::endl;

    std::cout << "Deploy a commander (D): " << std::endl;
    std::cout << "- Move commanders out of the capital and onto the map" << std::endl;
    break;
  }
  case 8: {
    std::cout << "On the map, each coordinate is a province that containes a type "
            "of unit (identified by a symbol). Here is a list of what each "
            "symbol on the map: "
         << std::endl
         << std::endl;
    std::cout << "P) Your capital province " << std::endl;
    std::cout << "p) One of your provinces " << std::endl;
    std::cout << "E) Your enemy's capital province " << std::endl;
    std::cout << "e) One of your eneny's provinces " << std::endl;
    std::cout << "H) One of your army units " << std::endl;
    std::cout << "V) One of your enemy's army units " << std::endl;
    std::cout << std::endl;
    std::cout << "If there are two letters in one province, that means that there "
            "are two units there-- if a province has PH, that means the player "
            "capital province and a commander unit are there. The number next "
            "to the letter indicates how many commander units are in the "
            "province"
         << std::endl
         << std::endl;
    std::cout << "Enter the x and y coordinates of the province you want to select. "
            "Depending on the type of province, you can build infrastructure, "
            "train troops, move armies, or attack armies. "
         << std::endl;
    std::cout << "------------ This is the end of the Help message ------------"
         << std::endl;
    break;
  }
  case 12: // upgradeBuildingsHelp
  {
    // finish this
    break;
  }
  }
  std::cout << "-------------- End Help ---------------- \033[;0m" << std::endl
            << std::endl;
  std::cout << "Enter 'R' to return to the menu: ";
  std::cout << ""; // NW
}