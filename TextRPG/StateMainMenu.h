#pragma once
#include "State.h"

class StateMainMenu : public State
{
public:
	StateMainMenu() : State(StateType::STATEMAINMENU, "StateMainMenu.lua") { };
};

class StateMainMenuFactory : public StateFactory
{
public:
	virtual StateMainMenu* Create() override
	{
		return new StateMainMenu();
	};

	virtual std::unique_ptr<StateFactory> Clone() override
	{
		return std::make_unique<StateMainMenuFactory>(*this);
	}
};