#pragma once
#include "State.h"

class StateCityUpgrades : public State
{
public:
	StateCityUpgrades() : State(StateType::STATECITYUPGRADES, "StateCityUpgrades.lua") { };
};

class StateCityUpgradesFactory : public StateFactory
{
public:
	virtual StateCityUpgrades* Create() override
	{
		return new StateCityUpgrades();
	};

	virtual std::unique_ptr<StateFactory> Clone() override
	{
		return std::make_unique<StateCityUpgradesFactory>(*this);
	}
};