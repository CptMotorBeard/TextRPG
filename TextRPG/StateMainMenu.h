#pragma once
#include "BaseIncludes.h"
#include "State.h"

class StateMainMenu : public State
{
public:
	StateMainMenu() : State(StateType::StateMainMenu) {};

	void Build() override;
	void ProcessEvents(const sf::Event &sfEvent) override;
	void PostRender(sf::RenderTarget &target) override;
	void PreRender(sf::RenderTarget &target) override;
};