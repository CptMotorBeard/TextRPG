#pragma once
#include "BaseIncludes.h"
#include "LUA.h"

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
#define STATESAVEGAME StateSaveGame

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
	StateType mStateType;	
	State(StateType stateType, const char* lua_source);

	sf::Font* mCurrentFont;
	std::vector<std::unique_ptr<sf::Drawable>> mAllDrawables;

	enum class RenderMode
	{
		NONE,
		Build,
		PreRender,
		PostRender,
		LENGTH
	};

	RenderMode mCurrentRenderMode;
	const char* LUA_SOURCE;

#pragma region AllStates
	friend class STATEMAINMENU;
	friend class STATEFACTIONCREATION;
	friend class STATEFACTIONOVERVIEW;
	friend class STATECHARACTERCREATION;
	friend class STATECHARACTEROVERVIEW;
	friend class STATELOADGAME;
	friend class STATESAVEGAME;
#pragma endregion

public:	
	State() : State(StateType::DEFAULT, "") {};	
	const StateType& GetStateType();

	virtual ~State() {};

	/// <summary>Builds the imGui state. All widgets must be created between update and render</summary>
	virtual void Build();
	/// <summary>Process SFML events</summary>
	virtual void ProcessEvents(const sf::Event& sfEvent) {};

	/// <summary>Renders prior to imGui, all elements are designed to be BEHIND imGui elements</summary>
	virtual void PreRender(sf::RenderTarget &target, sf::Font* font);
	/// <summary>Renders after imGui, all elements are designed to be ABOVE imGui elements</summary>
	virtual void PostRender(sf::RenderTarget &target, sf::Font* font);

#pragma region LUA Blocks
	void AddText(std::string text, int fontSize, float locX, float locY);
#pragma endregion

};