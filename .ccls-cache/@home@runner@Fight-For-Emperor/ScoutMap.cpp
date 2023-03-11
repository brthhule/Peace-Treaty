#include "ScoutMap.h"

ScoutMap::ScoutMap()
{
	
}

ScoutMap::ScoutMap(int continentSize)
{
	for (int x = 0; x < continentSize; x++)
	{
		std::vector<Provinces> provincesList;
		for (int y = 0; y < continentSize; y++)
		{
			Provinces newProvince;
			provincesList.push_back(newProvince);
		}
		newScoutMap.push_back(provincesList);
	}
}

