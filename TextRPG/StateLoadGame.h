#pragma once
#include "State.h"

class StateLoadGame : public State
{
public:
	StateLoadGame() : State(StateType::STATELOADGAME, "StateLoadGame.lua") { };
};

class StateLoadGameFactory : public StateFactory
{
public:
	virtual StateLoadGame* Create() override
	{
		return new StateLoadGame();
	};

	virtual std::unique_ptr<StateFactory> Clone() override
	{
		return std::make_unique<StateLoadGameFactory>(*this);
	}
};