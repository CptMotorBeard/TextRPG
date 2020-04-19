#pragma once
#include "State.h"

class StateDiplomacy : public State
{
public:
	StateDiplomacy() : State(StateType::STATEDIPLOMACY, "Resources/LUA/StateDiplomacy.lua") { };
};

class StateDiplomacyFactory : public StateFactory
{
public:
	virtual StateDiplomacy* Create() override
	{
		return new StateDiplomacy();
	};

	virtual std::unique_ptr<StateFactory> Clone() override
	{
		return std::make_unique<StateDiplomacyFactory>(*this);
	}
};