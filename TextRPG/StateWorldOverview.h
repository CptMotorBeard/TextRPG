#pragma once
#include "State.h"

class StateWorldOverview : public State
{
public:
	StateWorldOverview() : State(StateType::STATEWORLDOVERVIEW, "StateWorldOverview.lua") { };
};

class StateWorldOverviewFactory : public StateFactory
{
public:
	virtual StateWorldOverview* Create() override
	{
		return new StateWorldOverview();
	};

	virtual std::unique_ptr<StateFactory> Clone() override
	{
		return std::make_unique<StateWorldOverviewFactory>(*this);
	}
};