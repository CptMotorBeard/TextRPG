#pragma once
#include "BaseIncludes.h"
#include "State.h"

class StateMainMenu : public State
{
public:
	StateMainMenu() : State(StateType::StateMainMenu, "StateMainMenu.lua")
	{
		lua_State* L = LuaManager::GetLuaState();
		LuaManager::LuaOkay(L, luaL_dofile(L, LUA_SOURCE));

		// register C++ functions
	};

	void ProcessEvents(const sf::Event &sfEvent) override;
};