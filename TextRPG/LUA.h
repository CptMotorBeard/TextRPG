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
	static void InitializeNativeFunctions();

public:
	static bool LuaOkay(lua_State* L, int r);
	static bool CallbackFunction(const std::string &functionName, const char* sourceFile);
	static lua_State* GetLuaState();
	static void Shutdown();
};