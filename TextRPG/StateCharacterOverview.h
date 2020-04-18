#pragma once
#include "State.h"

class StateCharacterOverview : public State
{
public:
	StateCharacterOverview() : State(StateType::STATECHARACTEROVERVIEW, "StateCharacterOverview.lua") { };
};

class StateCharacterOverviewFactory : public StateFactory
{
public:
	virtual StateCharacterOverview* Create() override
	{
		return new StateCharacterOverview();
	}

	virtual std::unique_ptr<StateFactory> Clone() override
	{
		return std::make_unique<StateCharacterOverviewFactory>(*this);
	}
};