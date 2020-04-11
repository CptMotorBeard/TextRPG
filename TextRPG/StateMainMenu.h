#pragma once
#include "State.h"

class StateMainMenu : public State
{
public:
	StateMainMenu() : State(StateType::StateMainMenu, "StateMainMenu.lua") { };
};