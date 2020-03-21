#include "Faction.h"

Faction::Faction()
{
	Faction::mColony = Colony();
	Faction::mLeader = Leader();

	Faction::mFactionRelationships = std::map<Faction, FactionAllegiance>();
}