#pragma once
#include "State.h"

class StateSaveGame : public State
{
public:
	StateSaveGame() : State(StateType::STATESAVEGAME, "StateSaveGame.lua") { };
};

class StateSaveGameFactory : public StateFactory
{
public:
	virtual StateSaveGame* Create() override
	{
		return new StateSaveGame();
	};

	virtual std::unique_ptr<StateFactory> Clone() override
	{
		return std::make_unique<StateSaveGameFactory>(*this);
	}
};