#pragma once
#include "State.h"

class StateLoadGame : public State
{
public:
	StateLoadGame() : State(StateType::StateLoadGame, "StateLoadGame.lua") { };
};