#pragma once

#include "BaseIncludes.h"

#include "ColonyUpgrades.h"
#include "ColonyZone.h"
#include "Resources.h"

class Colony
{
private:
	std::vector<ColonyZone> mZones;
	std::vector<ColonyUpgrades> mUpgrades;
	Resources mColonyResources;

public:
	Colony();

	json SerializeData() const;
	void DeserializeData(json data);
};