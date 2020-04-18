#pragma once
#include "State.h"

class StateFactionOverview : public State
{
public:
	StateFactionOverview() : State(StateType::STATEFACTIONOVERVIEW, "StateFactionOverview.lua") { };
};

class StateFactionOverviewFactory : public StateFactory
{
public:
	virtual StateFactionOverview* Create() override
	{
		return new StateFactionOverview();
	};

	virtual std::unique_ptr<StateFactory> Clone() override
	{
		return std::make_unique<StateFactionOverviewFactory>(*this);
	}
};