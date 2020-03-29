#include "LUA.h"
lua_State *LuaManager::L = nullptr;

bool LuaManager::LuaOkay(lua_State* L, int r)
{
	if (r != LUA_OK)
	{
		std::string errorMessage = lua_tostring(L, -1);
		std::cout << errorMessage << std::endl;

		return false;
	}

	return true;
}

lua_State* LuaManager::GetLuaState()
{
	if (LuaManager::L == nullptr)
	{
		L = luaL_newstate();
		luaL_openlibs(L);
	}

	return L;
}

void LuaManager::Shutdown()
{
	lua_close(L);
}