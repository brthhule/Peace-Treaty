#include "showText.h"

/*
1 - selectEnemyAction
2 - playerUnitAction
3 - introduction
4 - playerAction
5 - armyDeployment
6 - TrainMAFunction
7 - playerBuildFunction
8 - viewPlayerMap
9 - selectPlayerProvince
10 - selectEnemyProvince
11 - scoutLogFunction
12 - upgradeBuildings
*/

std::vector<std::string> showOptions(int caseNum)
{
	std::string caseNumString = std::to_string(caseNum);
  std::fstream newfile;
  newfile.open("Options.txt", std::ios::in); // open a file to perform read operation using file object
	std::vector<std::string> acceptableValues = {"H"};
	
  if (newfile.is_open()) 
	{
		std::string line;
		bool pause = false;
    while (getline(newfile, line)) 
		{
			bool wait = false;

			if (line.substr(0,3) == "case")
				pause = true;
			if (line == "case " + caseNumString)
			{
				pause = false;
				wait = true;
			}
			if (line == "End")
			{
				wait = true;
				pause = false;
			}

			if (pause == false && wait == false)
				std::cout << line;
		}
    newfile.close(); // close the file object.
  }
	return acceptableValues;
}

void printOptions (std::string tp, int &type, bool &skip, std::vector<std::string> &acceptableValues)
{
	if (tp == "List of Options:")
		type = 1;
	else if (tp == "Options:")
	{
		type = 2;
		skip = true;
	}
	else if (tp == "End Options")
	{
		skip = true;
		type = 3;
	}

	switch (type)
	{
	case 1:
		std::cout << tp << std::endl;
		break;
	case 2:
		if (skip == true)
		{
			//Do nothing
			skip = false;
		}
		else
			acceptableValues.push_back(tp);
		break;
	case 3:
		if (skip == true)
			skip = false;
		else
			std::cout << tp << " ";
		break;
	}	
}

void showHelp (int caseNum)
{
	std::string caseNumString = std::to_string(caseNum);
  std::fstream newfile;
  newfile.open("Help.txt", std::ios::in);
  if (newfile.is_open()) 
	{
		std::string line;
		bool pause = false;
    while (getline(newfile, line)) 
		{
			bool wait = false;

			if (line.substr(0,3) == "case")
				pause = true;
			if (line == "case " + caseNumString)
			{
				pause = false;
				wait = true;
			}
			if (line == "End")
			{
				wait = true;
				pause = false;
			}

			if (pause == false && wait == false)
				std::cout << line;
		}
    newfile.close(); // close the file object.
  }
}

void printFile (std::string fileName)
{
	std::cout << "I am here" << std::endl;
	std::cout << "File name: " << fileName << std::endl;
	std::fstream newfile;
	newfile.open("Synopsis.txt", std::ios::in);
	std::cout << "Is open: " << newfile.is_open();
	if (newfile.is_open())
	{
		std::string line;
		while (getline(newfile, line))
		{
			std::cout << line;
		}
		newfile.close();
	}
	
}

char getOption (int caseNum)
{
	std::string caseNumString = std::to_string(caseNum);
	OtherFunctions OF;
	return OF.getInput ("showOptions, " + caseNumString, {}, false).at(0);
}

// void scoutLogFunction ()
// {
// //case ll
// 	std::string SLFReports[3] = Options:garrisonresourcebuilding
//     for (int x = 0; x < 3; x++) {
//   - View the  << SLFReports <<  report for this province ( << toupper(SLFReports[x].at(0)) << )\n;
  
// Options:GRB
// }