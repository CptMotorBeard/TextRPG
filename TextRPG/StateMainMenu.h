#pragma once
#include "BaseIncludes.h"
#include "State.h"

#define LUA_SOURCE "StateMainMenu.lua"

class StateMainMenu : public State
{
public:
	StateMainMenu() : State(StateType::StateMainMenu)
	{
		lua_State* L = LuaManager::GetLuaState();
		LuaManager::LuaOkay(L, luaL_dofile(L, LUA_SOURCE));

		// register C++ functions
	};

	void Build() override;
	void ProcessEvents(const sf::Event &sfEvent) override;
	void PostRender(sf::RenderTarget &target) override;
	void PreRender(sf::RenderTarget &target) override;
};