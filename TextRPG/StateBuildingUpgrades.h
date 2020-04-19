#pragma once
#include "State.h"

class StateBuildingUpgrades : public State
{
public:
	StateBuildingUpgrades() : State(StateType::STATEBUILDINGUPGRADES, "Resources/LUA/StateBuildingUpgradesFactory.lua") { };
};

class StateBuildingUpgradesFactory : public StateFactory
{
public:
	virtual StateBuildingUpgrades* Create() override
	{
		return new StateBuildingUpgrades();
	};

	virtual std::unique_ptr<StateFactory> Clone() override
	{
		return std::make_unique<StateBuildingUpgradesFactory>(*this);
	}
};