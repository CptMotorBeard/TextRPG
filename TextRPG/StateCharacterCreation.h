#pragma once
#include "State.h"

class StateCharacterCreation : public State
{
public:
	StateCharacterCreation() : State(StateType::StateCharacterCreation, "StateCharacterCreation.lua") { };
};