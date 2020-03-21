#pragma once
#include "BaseIncludes.h"
#include "Unit.h"
#include "Colony.h"

enum class FactionAllegiance
{
	LENGTH
};

class Faction
{
	std::map<Faction, FactionAllegiance> mFactionRelationships;
	Unit mLeader;
	Colony mColony;
};