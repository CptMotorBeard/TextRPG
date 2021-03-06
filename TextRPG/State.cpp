#include "State.h"

#include "GameManager.h"
#include "imguiWindows.h"
#include "imgui.h"
#include "LocalizationManager.h"
#include "LUA.h"
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

State::State(const StateType& stateType, const std::string &lua_source)
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

const StateType& State::GetStateType() const
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

	lua_State* L = LuaManager::GetLuaState();

	if (LuaManager::LuaOkay(L, luaL_loadfile(L, LUA_SOURCE.c_str())))
	{
		lua_getglobal(L, "Build");
		if (lua_isfunction(L, -1))
		{
			LuaManager::LuaOkay(L, lua_pcall(L, 0, 0, 0));
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
	if (SFML_Manager::GetInstance().WindowWasResized)
	{
		mRebuild = true;
	}

	for (auto const& b : mAllButtons)
	{
		b->ProcessEvents(sfEvent);
	}
}

void State::AddText(const std::string& text, const int& fontSize, const float& locx, const float& locy)
{
	if (mCurrentRenderMode != RenderMode::Render)
	{
		return;
	}

	sf::Text* t = new sf::Text();

	auto localizedText = LocalizationManager::GetInstance().GetLocByKey(text);
	t->setString(*localizedText);	
	t->setFont(*GameManager::GetInstance().GetGlobalFont());
	t->setFillColor(sf::Color::Red);
	t->setCharacterSize(fontSize);
	t->setPosition(locx, locy);

	mAllDrawables.emplace_back(t);
}

void State::AddButton(const std::string& text, const sf::FloatRect& rect, const std::string& callbackName, const std::string callbackSource)
{
	if (mCurrentRenderMode != RenderMode::Render)
	{
		return;
	}

	auto localizedText = LocalizationManager::GetInstance().GetLocByKey(text);

	sf_ext::SFML_Button *b = new sf_ext::SFML_Button(*localizedText, rect,
		[=]() {
		LuaManager::CallbackFunction(callbackName, LUA_SOURCE.c_str(), callbackSource);
		}
	);

	mAllButtons.emplace_back(b);
}

void State::imguiBegin(const char * text)
{
	if (mCurrentRenderMode != RenderMode::Build)
	{
		return;
	}

	ImGui::Begin(text);
}

bool State::PushCharacterCreationWindow(Unit* character)
{
	if (mCurrentRenderMode != RenderMode::Build)
	{
		return false;
	}

	return imguiWindow::PushNewCharacterCreationWindow(character);
}

void State::imguiEnd()
{
	if (mCurrentRenderMode != RenderMode::Build)
	{
		return;
	}

	ImGui::End();
}

StateFactory::~StateFactory() {}