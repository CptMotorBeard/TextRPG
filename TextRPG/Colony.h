#pragma once

#include "BaseIncludes.h"
#include "ColonyZone.h"
#include "ColonyUpgrades.h"

class Colony
{
private:
	std::vector<ColonyZone> mZones;
	std::vector<ColonyUpgrades> mUpgrades;

public:
	Colony()
	{
		mZones = std::vector<ColonyZone>();
		mUpgrades = std::vector<ColonyUpgrades>();
	};
};