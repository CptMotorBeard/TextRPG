#pragma once
#include "State.h"

class StateUnitUpgrades : public State
{
public:
	StateUnitUpgrades() : State(StateType::STATEBUILDINGUPGRADES, "Resources/LUA/StateUnitUpgrades.lua") { };
};

class StateUnitUpgradesFactory : public StateFactory
{
public:
	virtual StateUnitUpgrades* Create() override
	{
		return new StateUnitUpgrades();
	};

	virtual std::unique_ptr<StateFactory> Clone() override
	{
		return std::make_unique<StateUnitUpgradesFactory>(*this);
	}
};