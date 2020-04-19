#pragma once

#include "BaseIncludes.h"
#include "ColonyZone.h"
#include "ColonyUpgrades.h"
#include "Resources.h"

class Colony
{
private:
	std::vector<ColonyZone> mZones;
	std::vector<ColonyUpgrades> mUpgrades;
	Resources mColonyResources;

public:
	Colony();
};