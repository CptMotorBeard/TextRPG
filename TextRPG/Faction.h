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
public:
	std::map<Faction, FactionAllegiance> mFactionRelationships;
	Leader mLeader;
	Colony mColony;

	Faction();
};