#pragma once
#include "State.h"

class StateCharacterOverview : public State
{
public:
	StateCharacterOverview() : State(StateType::StateCharacterOverview, "StateCharacterOverview.lua") { };
};