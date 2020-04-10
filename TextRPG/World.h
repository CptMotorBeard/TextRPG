#pragma once
#include "BaseIncludes.h"
#include "Faction.h"

class World
{
public:
	Faction PlayerFaction;
	std::vector<Faction> WorldFactions;
};