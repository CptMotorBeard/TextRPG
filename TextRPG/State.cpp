#include "State.h"
#include "LocalizationManager.h"
#include "GameManager.h"

State::State(StateType stateType, const char *lua_source)
{
	State::mStateType = stateType;
	State::mCurrentRenderMode = State::RenderMode::NONE;
	State::LUA_SOURCE = lua_source;

	mAllDrawables = std::vector<std::shared_ptr<sf::Drawable>>();

	lua_State* L = LuaManager::GetLuaState();
	LuaManager::LuaOkay(L, luaL_dofile(L, State::LUA_SOURCE));
}

const StateType& State::GetStateType()
{
	return mStateType;
}

void State::Build()
{
	State::mCurrentRenderMode = State::RenderMode::Build;
	lua_State* L = LuaManager::GetLuaState();

	if (LuaManager::LuaOkay(L, luaL_dofile(L, LUA_SOURCE)))
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

	mAllDrawables.clear();
	
	lua_State* L = LuaManager::GetLuaState();

	if (LuaManager::LuaOkay(L, luaL_dofile(L, LUA_SOURCE)))
	{
		lua_getglobal(L, "PreRender");
		if (lua_isfunction(L, -1))
		{
			LuaManager::LuaOkay(L, lua_pcall(L, 0, 0, 0));
		}
	}
	State::mCurrentRenderMode = State::RenderMode::NONE;
	
	for (auto const& d : mAllDrawables)
	{
		target.draw(*d);
	}
}

void State::PostRender(sf::RenderTarget& target)
{
	State::mCurrentRenderMode = State::RenderMode::PostRender;

	mAllDrawables.clear();

	lua_State* L = LuaManager::GetLuaState();

	if (LuaManager::LuaOkay(L, luaL_dofile(L, LUA_SOURCE)))
	{
		lua_getglobal(L, "PostRender");
		if (lua_isfunction(L, -1))
		{
			LuaManager::LuaOkay(L, lua_pcall(L, 0, 0, 0));
		}
	}

	State::mCurrentRenderMode = State::RenderMode::NONE;

	for (auto const& d : mAllDrawables)
	{
		target.draw(*d);
	}
}

void State::AddText(std::string text, int fontSize, float locx, float locy)
{
	sf::Text t;

	auto localizedText = LocalizationManager::GetInstance()->GetLocByKey(text);
	t.setString(*localizedText);
	t.setFont(*GameManager::GetInstance()->GetGlobalFont());
	t.setFillColor(sf::Color::Red);
	t.setCharacterSize(fontSize);
	t.setPosition(locx, locy);

	mAllDrawables.push_back(std::make_shared<sf::Text>(t));
}