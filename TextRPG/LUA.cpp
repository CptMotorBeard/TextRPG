#include "LUA.h"
#include "StateManager.h"

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
		InitializeNativeFunctions();
	}

	return L;
}

#pragma region Native Functions
int lua_AddText(lua_State* L)
{
	// AddText(string text, int fontSize, float locX, float locY);

	if (lua_gettop(L) >= 4)
	{
		std::string text = lua_tostring(L, 1);
		int fontSize = (int)lua_tonumber(L, 2);
		float locx = (float)lua_tonumber(L, 3);
		float locy = (float)lua_tonumber(L, 4);

		StateManager::GetInstance()->GetCurrentState()->AddText(text, fontSize, locx, locy);
	}

	return 0;
}
#pragma endregion

void LuaManager::InitializeNativeFunctions()
{
	lua_register(L, "AddText", lua_AddText);
}

void LuaManager::Shutdown()
{
	lua_close(L);
}