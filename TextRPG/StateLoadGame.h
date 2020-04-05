#pragma once
#include "State.h"

class StateLoadGame : public State
{
public:
	StateLoadGame() : State(StateType::StateLoadGame, "StateLoadGame.lua")
	{
		lua_State* L = LuaManager::GetLuaState();
		LuaManager::LuaOkay(L, luaL_dofile(L, LUA_SOURCE));

		// register C++ functions
	};
};