#include "State.h"
#include "LocalizationManager.h"
#include "GameManager.h"

#include <fstream>

State::State(StateType stateType, const char *lua_source)
{
	State::mStateType = stateType;
	State::mCurrentRenderMode = State::RenderMode::NONE;
	State::LUA_SOURCE = lua_source;
	State::mHash = 0;
	State::mRebuild = true;

	HashFile();

	lua_State* L = LuaManager::GetLuaState();
	LuaManager::LuaOkay(L, luaL_dofile(L, State::LUA_SOURCE));
}

void State::HashFile()
{
	std::ifstream file;
	file.open(LUA_SOURCE);
	if (file.good())
	{
		std::string luafile = "";
		std::string line;

		while (std::getline(file, line))
		{
			luafile += line;
		}

		mHash = std::hash<std::string>{}(luafile);
	}
	file.close();
}

const StateType& State::GetStateType()
{
	return mStateType;
}

void State::RecalculateHash()
{
	uint64 h = uint64(mHash);
	HashFile();
	mRebuild = h != mHash;

	if (mRebuild)
	{
		lua_State* L = LuaManager::GetLuaState();
		LuaManager::LuaOkay(L, luaL_dofile(L, State::LUA_SOURCE));
	}
}

void State::Build()
{
	State::mCurrentRenderMode = State::RenderMode::Build;

	if (mRebuild)
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

	State::mCurrentRenderMode = State::RenderMode::NONE;
}

void State::Render(sf::RenderTarget& target)
{
	State::mCurrentRenderMode = State::RenderMode::Render;

	if (mRebuild)
	{
		mAllDrawables.clear();
		mAllButtons.clear();

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

	for (auto const& d : mAllDrawables)
	{
		target.draw(*d);
	}

	for (auto const& b : mAllButtons)
	{
		b->Draw(target);
	}

	State::mCurrentRenderMode = State::RenderMode::NONE;
}

void State::ProcessEvents(const sf::Event &sfEvent)
{
	for (auto const& b : mAllButtons)
	{
		b->ProcessEvents(sfEvent);
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

void State::AddButton(std::string text, sf::FloatRect rect, std::string callbackName)
{
	auto localizedText = LocalizationManager::GetInstance()->GetLocByKey(text);

	sf_ext::SFML_Button b(*localizedText, rect,
		[=]() {
		LuaManager::CallbackFunction(callbackName, LUA_SOURCE);
		}
	);

	mAllButtons.push_back(std::make_shared<sf_ext::SFML_Button>(b));
}