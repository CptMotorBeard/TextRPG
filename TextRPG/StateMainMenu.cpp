#include "StateMainMenu.h"

void StateMainMenu::ProcessEvents(const sf::Event& sfEvent)
{

}

void StateMainMenu::Build()
{
	lua_State* L = LuaManager::GetLuaState();

	if (LuaManager::LuaOkay(L, luaL_loadfile(L, LUA_SOURCE)))
	{
		lua_getglobal(L, "Build");
		if (lua_isfunction(L, -1))
		{
			LuaManager::LuaOkay(L, lua_pcall(L, 0, 0, 0));
		}
	}
}

void StateMainMenu::PreRender(sf::RenderTarget& target)
{
	lua_State* L = LuaManager::GetLuaState();

	if (LuaManager::LuaOkay(L, luaL_loadfile(L, LUA_SOURCE)))
	{
		lua_getglobal(L, "PreRender");
		if (lua_isfunction(L, -1))
		{
			LuaManager::LuaOkay(L, lua_pcall(L, 0, 0, 0));
		}
	}
}

void StateMainMenu::PostRender(sf::RenderTarget& target)
{
	lua_State* L = LuaManager::GetLuaState();

	if (LuaManager::LuaOkay(L, luaL_loadfile(L, LUA_SOURCE)))
	{
		lua_getglobal(L, "PostRender");
		if (lua_isfunction(L, -1))
		{
			LuaManager::LuaOkay(L, lua_pcall(L, 0, 0, 0));
		}
	}
}