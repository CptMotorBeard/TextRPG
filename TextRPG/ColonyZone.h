#pragma once
#include "BaseIncludes.h"
#include "ColonyBuildings.h"

class ColonyZone
{
private:
	std::vector<ColonyBuilding> mColonyBuildings;

public:
	ColonyZone()
	{
		mColonyBuildings = std::vector<ColonyBuilding>();
	};
};