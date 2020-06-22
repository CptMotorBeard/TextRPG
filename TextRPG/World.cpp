#include "World.h"

const char* kPlayerFaction = "world_plfc";
const char* kWorldFactions = "world_wlfc";

json World::SerializeData() const
{
	json data;

	data[kPlayerFaction] = std::move(PlayerFaction.SerializeData());
	data[kWorldFactions] = json::array();

	for (const auto& faction : WorldFactions)
	{
		data[kWorldFactions].emplace_back(std::move(faction.SerializeData()));
	}

	return data;
}

void World::DeserializeData(json data)
{
	if (!data.is_object())
	{
		return;
	}

	if (data.contains(kPlayerFaction))
	{
		Faction tmpFaction;
		tmpFaction.DeserializeData(data[kPlayerFaction]);

		PlayerFaction = std::move(tmpFaction);
	}

	if (data.contains(kWorldFactions) && data[kWorldFactions].is_array())
	{
		WorldFactions.clear();
		for (const auto& faction : data[kWorldFactions])
		{
			Faction tmpFaction;
			tmpFaction.DeserializeData(faction);

			WorldFactions.emplace_back(std::move(tmpFaction));
		}
	}
}