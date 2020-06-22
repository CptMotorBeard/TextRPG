#include "Faction.h"

const char* kRelationships = "faction_rls";
const char* kLeader = "faction_ldr";
const char* kColony = "faction_clny";

json Faction::SerializeData() const
{
	json data;

	data[kLeader] = std::move(mLeader.SerializeData());
	data[kColony] = std::move(mColony.SerializeData());

	// std::map<Faction *, FactionAllegiance> mFactionRelationships;	

	return data;
}

void Faction::DeserializeData(json data)
{
	if (!data.is_object())
	{
		return;
	}

	if (data.contains(kLeader))
	{
		Leader tmpLeader;
		tmpLeader.DeserializeData(data[kLeader]);

		mLeader = std::move(tmpLeader);
	}

	if (data.contains(kColony))
	{
		Colony tmpColony;
		tmpColony.DeserializeData(data[kColony]);

		mColony = std::move(tmpColony);
	}

	// std::map<Faction *, FactionAllegiance> mFactionRelationships;	
}

Faction::Faction()
{

}