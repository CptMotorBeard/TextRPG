#pragma once

#include <functional>

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
	StateMainMenu,
	StateFactionCreation,
	StateFactionOverview,
	StateCharacterCreation,
	StateCharacterOverview,
	StateLoadGame,
	StateSaveGame,
	StateWorldOverview,
	StateDiplomacy,
	StateCombat,
	StateInventory,
	StateCityUpgrades,
	StateBuildingUpgrades,
	StateUnitUpgrades,
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
	
	void HashFile();

	std::vector< std::function<void(void)>> mimguiBuild;
	std::vector<std::shared_ptr<sf::Drawable>> mAllDrawables;
	std::vector<std::shared_ptr<sf_ext::SFML_Button>> mAllButtons;

	RenderMode mCurrentRenderMode;
	const char* LUA_SOURCE;
	uint64 mHash;
	bool mRebuild;

public:	
	State(StateType stateType, const char* lua_source);
	State() : State(StateType::DEFAULT, "") {};	
	const StateType& GetStateType();

	virtual ~State() {};

	virtual void RecalculateHash();
	virtual void ForceRebuild();
	/// <summary>Builds the imGui state. All widgets must be created between update and render</summary>
	virtual void Build();
	/// <summary>Process SFML events</summary>
	virtual void ProcessEvents(const sf::Event& sfEvent);

	/// <summary>Renders prior to imGui, all elements are designed to be BEHIND imGui elements</summary>
	virtual void Render(sf::RenderTarget &target);

#pragma region LUA Blocks
	void AddText(std::string text, int fontSize, float locX, float locY);
	void AddButton(std::string text, sf::FloatRect rect, std::string callbackName);
	void imguiBegin(const char * text);
	void imguiEnd();
#pragma endregion

};

class StateFactory
{
public:
	virtual State* Create() = 0;
	virtual std::unique_ptr<StateFactory> make_unique() = 0;
	virtual ~StateFactory() = 0;
};

#define MAKE_STATE(stateName)	\
class stateName : public State	\
{	\
public:	\
	stateName() : State(StateType:: stateName, "Resources/LUA/"#stateName".lua") { };	\
};	\
\
class stateName##Factory : public StateFactory	\
{	\
public:	\
	virtual stateName* Create() override	\
	{	\
		return new stateName();	\
	};	\
\
	virtual std::unique_ptr<StateFactory> make_unique() override	\
	{	\
		return std::make_unique<stateName##Factory>(*this);	\
	}	\
\
	virtual ~stateName##Factory() override	\
	{	\
		return;	\
	}	\
};