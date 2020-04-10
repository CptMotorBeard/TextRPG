#pragma once
#include "State.h"

class StateFactionOverview : public State
{
public:
	StateFactionOverview() : State(StateType::StateFactionOverview, "StateFactionOverview.lua") { };
};