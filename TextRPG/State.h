#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include "LUA.h"
#include "SFML/Graphics.hpp"

/*
	All states must be declared as a StateType. All states must be declared as friend classes. We want the states to be able to initialize what state type they are
	but after that we don't want anything to be able to touch that value. defines keep things in one place.
*/

#define STATEMAINMENU StateMainMenu
#define STATEFACTIONCREATION StateFactionCreation
#define STATEFACTIONOVERVIEW StateFactionOverview
#define STATECHARACTERCREATION StateCharacterCreation
#define STATECHARACTEROVERVIEW StateCharacterOverview
#define STATELOADGAME StateLoadGame

enum class StateType
{
	DEFAULT,
	STATEMAINMENU,
	LENGTH
};

class State
{
private:
	StateType mStateType;	
	State(StateType stateType);

#pragma region AllStates
	friend class STATEMAINMENU;
#pragma endregion

public:	
	State() : State(StateType::DEFAULT) {};	
	const StateType& GetStateType();

	virtual ~State() {};

	/// <summary>Builds the imGui state. All widgets must be created between update and render</summary>
	virtual void Build() {};
	/// <summary>Process SFML events</summary>
	virtual void ProcessEvents(const sf::Event &sfEvent) {};

	/// <summary>Renders prior to imGui, all elements are designed to be BEHIND imGui elements</summary>
	virtual void PreRender(sf::RenderTarget &target) {};
	/// <summary>Renders after imGui, all elements are designed to be ABOVE imGui elements</summary>
	virtual void PostRender(sf::RenderTarget &target) {};
};