#pragma once
#include "State.h"

class StateSaveGame : public State
{
public:
	StateSaveGame() : State(StateType::StateSaveGame, "StateSaveGame.lua")
	{
		lua_State* L = LuaManager::GetLuaState();
		LuaManager::LuaOkay(L, luaL_dofile(L, LUA_SOURCE));

		// register C++ functions
	};
};