#pragma once
#include "State.h"

class StateFactionCreation : public State
{
public:
	StateFactionCreation() : State(StateType::StateFactionCreation, "StateFactionCreation.lua") { };
};