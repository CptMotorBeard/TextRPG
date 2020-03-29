#pragma once
#include <iostream>

extern "C"
{
#include "Lua535/include/lua.h"
#include "Lua535/include/lauxlib.h"
#include "Lua535/include/lualib.h"
}

class LuaManager
{
private:
	static lua_State* L;

public:
	static bool LuaOkay(lua_State* L, int r);

	static lua_State* GetLuaState();
	static void Shutdown();
};