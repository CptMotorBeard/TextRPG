#pragma once
#include "BaseIncludes.h"
#include "LUA.h"
#include "State.h"

class StateMainMenu : public State
{
public:
	StateMainMenu() : State(StateType::StateMainMenu) {};

	void Build(lua_State* L) override;
	void ProcessEvents(const sf::Event &sfEvent) override;
	void PostRender(sf::RenderTarget &target, lua_State* L) override;
	void PreRender(sf::RenderTarget &target, lua_State* L) override;
};