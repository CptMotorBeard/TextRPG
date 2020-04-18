#pragma once
#include "State.h"

class StateFactionCreation : public State
{
public:
	StateFactionCreation() : State(StateType::STATEFACTIONCREATION, "StateFactionCreation.lua") { };
};

class StateFactionCreationFactory : public StateFactory
{
public:
	virtual StateFactionCreation* Create() override
	{
		return new StateFactionCreation();
	};

	virtual std::unique_ptr<StateFactory> Clone() override
	{
		return std::make_unique<StateFactionCreationFactory>(*this);
	};
};