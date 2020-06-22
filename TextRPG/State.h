#pragma once

#include "BaseIncludes.h"

#include "SFML-extensions.h"

class Unit;

/*
	All states must be declared as a StateType. All states must be declared as friend classes. We want the states to be able to initialize what state type they are
	but after that we don't want anything to be able to touch that value. defines keep things in one place.
*/

enum class StateType
{
#define STATE_STRING_MAP_ITEM(state) { StateType :: state, std::string(#state) }

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

	std::vector<std::shared_ptr<sf::Drawable>> mAllDrawables;
	std::vector<std::shared_ptr<sf_ext::SFML_Button>> mAllButtons;

	RenderMode mCurrentRenderMode;
	std::string LUA_SOURCE;
	uint64 mHash;
	bool mRebuild;

public:	
	static const std::map<StateType, std::string> StateStringMap;

	State(const StateType& stateType, const std::string &lua_source);
	State() : State(StateType::DEFAULT, "") {};
	const StateType& GetStateType() const;

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
	void AddText(const std::string& text, const int& fontSize, const float& locX, const float& locY);
	void AddButton(const std::string& text, const sf::FloatRect& rect, const std::string& callbackName, const std::string callbackSource);
	void imguiBegin(const char * text);
	bool PushCharacterCreationWindow(Unit* character);
	void imguiEnd();
#pragma endregion

};

class StateFactory
{
public:
	virtual State* Create() = 0;
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
	virtual ~stateName##Factory() override	\
	{	\
		return;	\
	}	\
};