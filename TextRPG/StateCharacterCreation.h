#pragma once
#include "State.h"

class StateCharacterCreation : public State
{
public:
	StateCharacterCreation() : State(StateType::STATECHARACTERCREATION, "StateCharacterCreation.lua") { };
};

class StateCharacterCreationFactory : public StateFactory
{
public:
	virtual StateCharacterCreation* Create() override
	{
		return new StateCharacterCreation();
	};

	virtual std::unique_ptr<StateFactory> Clone() override
	{
		return std::make_unique<StateCharacterCreationFactory>(*this);
	}
};