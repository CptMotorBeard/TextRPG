#pragma once
#include "imgui.h"
#include "imgui-SFML.h"

/*
	All states must be declared as a StateType. All states must be declared as friend classes. We want the states to be able to initialize what state type they are
	but after that we don't want anything to be able to touch that value. defines keep things in one place.
*/

#define STATEMAINMENU StateMainMenu

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
	virtual void Build() {};
};