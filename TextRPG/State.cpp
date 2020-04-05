#include "State.h"

State::State(StateType stateType, const char *lua_source)
{
	State::mStateType = stateType;
	State::mCurrentRenderMode = State::RenderMode::NONE;
	State::LUA_SOURCE = lua_source;

	mAllDrawables = std::vector<std::unique_ptr<sf::Drawable>>();
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

void State::PreRender(sf::RenderTarget& target, sf::Font *font)
{
	State::mCurrentRenderMode = State::RenderMode::PreRender;
	mCurrentFont = font;

	for (auto& d : mAllDrawables)
	{
		d.release();
	}

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

void State::PostRender(sf::RenderTarget& target, sf::Font* font)
{
	State::mCurrentRenderMode = State::RenderMode::PostRender;
	mCurrentFont = font;

	for (auto& d : mAllDrawables)
	{
		d.release();
	}

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
	std::unique_ptr<sf::Text> t = std::make_unique<sf::Text>();

	t->setString(text);
	t->setFont(*mCurrentFont);
	t->setFillColor(sf::Color::Red);
	t->setCharacterSize(fontSize);
	t->setPosition(locx, locy);

	mAllDrawables.push_back(std::move(t));
}