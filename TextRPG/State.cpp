#include "State.h"
#include "LocalizationManager.h"
#include "GameManager.h"
#include "SFML-manager.h"

#include <fstream>

const std::map<StateType, std::string> State::StateStringMap
{
	STATE_STRING_MAP_ITEM(StateMainMenu),
	STATE_STRING_MAP_ITEM(StateFactionCreation),
	STATE_STRING_MAP_ITEM(StateFactionOverview),
	STATE_STRING_MAP_ITEM(StateCharacterCreation),
	STATE_STRING_MAP_ITEM(StateCharacterOverview),
	STATE_STRING_MAP_ITEM(StateLoadGame),
	STATE_STRING_MAP_ITEM(StateSaveGame),
	STATE_STRING_MAP_ITEM(StateWorldOverview),
	STATE_STRING_MAP_ITEM(StateDiplomacy),
	STATE_STRING_MAP_ITEM(StateCombat),
	STATE_STRING_MAP_ITEM(StateInventory),
	STATE_STRING_MAP_ITEM(StateCityUpgrades),
	STATE_STRING_MAP_ITEM(StateBuildingUpgrades),
	STATE_STRING_MAP_ITEM(StateUnitUpgrades)
};

State::State(StateType stateType, const std::string &lua_source)
{
	State::mStateType = stateType;
	State::mCurrentRenderMode = State::RenderMode::NONE;
	State::LUA_SOURCE = lua_source;
	State::mHash = 0;
	State::mRebuild = true;

	HashFile();

	lua_State* L = LuaManager::GetLuaState();
	LuaManager::LuaOkay(L, luaL_dofile(L, State::LUA_SOURCE.c_str()));
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
		LuaManager::LuaOkay(L, luaL_dofile(L, State::LUA_SOURCE.c_str()));
	}
}

void State::ForceRebuild()
{
	lua_State* L = LuaManager::GetLuaState();
	LuaManager::LuaOkay(L, luaL_dofile(L, State::LUA_SOURCE.c_str()));
	mRebuild = true;
}

void State::Build()
{
	State::mCurrentRenderMode = State::RenderMode::Build;

	if (mRebuild)
	{
		lua_State* L = LuaManager::GetLuaState();
		mimguiBuild.clear();

		if (LuaManager::LuaOkay(L, luaL_loadfile(L, LUA_SOURCE.c_str())))
		{
			lua_getglobal(L, "Build");
			if (lua_isfunction(L, -1))
			{
				LuaManager::LuaOkay(L, lua_pcall(L, 0, 0, 0));
			}
		}
	}

	for (auto const &f : mimguiBuild)
	{
		f();
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

		if (LuaManager::LuaOkay(L, luaL_loadfile(L, LUA_SOURCE.c_str())))
		{
			lua_getglobal(L, "Render");
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
	if (SFML_Manager::GetInstance()->WindowWasResized)
	{
		mRebuild = true;
	}

	for (auto const& b : mAllButtons)
	{
		b->ProcessEvents(sfEvent);
	}
}

void State::AddText(std::string text, int fontSize, float locx, float locy)
{
	if (mCurrentRenderMode != RenderMode::Render)
	{
		return;
	}

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
	if (mCurrentRenderMode != RenderMode::Render)
	{
		return;
	}

	auto localizedText = LocalizationManager::GetInstance()->GetLocByKey(text);

	sf_ext::SFML_Button b(*localizedText, rect,
		[=]() {
		LuaManager::CallbackFunction(callbackName, LUA_SOURCE.c_str());
		}
	);

	mAllButtons.push_back(std::make_shared<sf_ext::SFML_Button>(b));
}

void State::imguiBegin(const char * text)
{
	if (mCurrentRenderMode != RenderMode::Build)
	{
		return;
	}

	mimguiBuild.push_back([text]() {ImGui::Begin(text); });
}

void State::imguiEnd()
{
	if (mCurrentRenderMode != RenderMode::Build)
	{
		return;
	}

	mimguiBuild.push_back([]() {ImGui::End(); });
}

StateFactory::~StateFactory() {}