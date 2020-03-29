#include "State.h"

State::State(StateType stateType, const char *lua_source)
{
	State::mStateType = stateType;
	State::mCurrentRenderMode = State::RenderMode::NONE;
	State::LUA_SOURCE = lua_source;
}

const StateType& State::GetStateType()
{
	return mStateType;
}

void State::Build()
{
	State::mCurrentRenderMode = State::RenderMode::Build;
	lua_State* L = LuaManager::GetLuaState();

	if (LuaManager::LuaOkay(L, luaL_loadfile(L, LUA_SOURCE)))
	{
		lua_getglobal(L, "Build");
		if (lua_isfunction(L, -1))
		{
			LuaManager::LuaOkay(L, lua_pcall(L, 0, 0, 0));
		}
	}

	State::mCurrentRenderMode = State::RenderMode::NONE;
}

void State::PreRender(sf::RenderTarget& target)
{
	State::mCurrentRenderMode = State::RenderMode::PreRender;
	lua_State* L = LuaManager::GetLuaState();

	if (LuaManager::LuaOkay(L, luaL_loadfile(L, LUA_SOURCE)))
	{
		lua_getglobal(L, "PreRender");
		if (lua_isfunction(L, -1))
		{
			LuaManager::LuaOkay(L, lua_pcall(L, 0, 0, 0));
		}
	}
	State::mCurrentRenderMode = State::RenderMode::NONE;
}

void State::PostRender(sf::RenderTarget& target)
{
	State::mCurrentRenderMode = State::RenderMode::PostRender;
	lua_State* L = LuaManager::GetLuaState();

	if (LuaManager::LuaOkay(L, luaL_loadfile(L, LUA_SOURCE)))
	{
		lua_getglobal(L, "PostRender");
		if (lua_isfunction(L, -1))
		{
			LuaManager::LuaOkay(L, lua_pcall(L, 0, 0, 0));
		}
	}

	State::mCurrentRenderMode = State::RenderMode::NONE;
}