#pragma once
#include "BaseIncludes.h"
#include "State.h"

class StateMainMenu : public State
{
public:
	StateMainMenu() : State(StateType::StateMainMenu) {};

	void Build() override;
};