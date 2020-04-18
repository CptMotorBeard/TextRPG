#pragma once

#include "BaseIncludes.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include "LUA.h"
#include "SFML/Graphics.hpp"
#include "SFML-extensions.h"

/*
	All states must be declared as a StateType. All states must be declared as friend classes. We want the states to be able to initialize what state type they are
	but after that we don't want anything to be able to touch that value. defines keep things in one place.
*/

enum class StateType
{
	DEFAULT,
	STATEMAINMENU,
	STATEFACTIONCREATION,
	STATEFACTIONOVERVIEW,
	STATECHARACTERCREATION,
	STATECHARACTEROVERVIEW,
	STATELOADGAME,
	STATESAVEGAME,
	LENGTH
};

class State
{
private:
	enum class RenderMode
	{
		NONE,
		Build,
		Render,
		LENGTH
	};

	StateType mStateType;	
	State(StateType stateType, const char* lua_source);
	void HashFile();

	std::vector<std::shared_ptr<sf::Drawable>> mAllDrawables;
	std::vector<std::shared_ptr<sf_ext::SFML_Button>> mAllButtons;

	RenderMode mCurrentRenderMode;
	const char* LUA_SOURCE;
	uint64 mHash;
	bool mRebuild;

#pragma region AllStates
	friend class StateMainMenu;
	friend class StateFactionCreation;
	friend class StateFactionOverview;
	friend class StateCharacterCreation;
	friend class StateCharacterOverview;
	friend class StateLoadGame;
	friend class StateSaveGame;
#pragma endregion

public:	
	State() : State(StateType::DEFAULT, "") {};	
	const StateType& GetStateType();

	virtual ~State() {};

	virtual void RecalculateHash();
	/// <summary>Builds the imGui state. All widgets must be created between update and render</summary>
	virtual void Build();
	/// <summary>Process SFML events</summary>
	virtual void ProcessEvents(const sf::Event& sfEvent);

	/// <summary>Renders prior to imGui, all elements are designed to be BEHIND imGui elements</summary>
	virtual void Render(sf::RenderTarget &target);

#pragma region LUA Blocks
	void AddText(std::string text, int fontSize, float locX, float locY);
	void AddButton(std::string text, sf::FloatRect rect, std::string callbackName);
#pragma endregion

};

class StateFactory
{
public:
	virtual State* Create() = 0;
	virtual std::unique_ptr<StateFactory> Clone() = 0;
};