#pragma once
#include "BaseIncludes.h"

#include "Unit.h"

class ColonyBuilding
{
private:
	std::vector<Unit> mUnits;

public:
	ColonyBuilding();
};

class ColonyHome : ColonyBuilding {};
class ColonyBusiness : ColonyBuilding {};
class ColonyPowerBuilding : ColonyBuilding {};
class ColonyConstructionBuilding : ColonyBuilding {};