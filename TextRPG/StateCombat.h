#pragma once
#include "State.h"

class StateCombat : public State
{
public:
	StateCombat() : State(StateType::STATECOMBAT, "Resources/LUA/StateCombat.lua") { };
};

class StateCombatFactory : public StateFactory
{
public:
	virtual StateCombat* Create() override
	{
		return new StateCombat();
	};

	virtual std::unique_ptr<StateFactory> Clone() override
	{
		return std::make_unique<StateCombatFactory>(*this);
	}
};