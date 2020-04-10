#pragma once
#include "State.h"

class StateSaveGame : public State
{
public:
	StateSaveGame() : State(StateType::StateSaveGame, "StateSaveGame.lua") { };
};