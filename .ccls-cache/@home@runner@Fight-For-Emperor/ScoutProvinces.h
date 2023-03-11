#ifndef SCOUTPROVINCES_H
#define SCOUTPROVINCES_H

#include <iostream>
#include <vector>

class ScoutProvinces
{
public:
	ScoutProvinces();
private:
	std::vector<int> resourcesPresent;
	garrisonedTroops;
	int maxResources;
	int *provinceStats[27]; /*

[5] max resources province can hold
[6] garrisoned militia
[7] garrisoned guards
[8] garrisoned cavalry
[9] garrisoned knights
[10] garrisoned paladins
[11] max garrison
[12] injured malitia
[13] injured guards
[14] injured cavalry
[15] injured knights
[16] injured paladins
[17] max infirmary capacity
[18] farm level
[19] lumber mill level
[20] quarry level
[21] mine level
[22] church level
[23] barracks level
[24] infirmary level
[25] total CP
[26] food consumption*/
	
};

#endif