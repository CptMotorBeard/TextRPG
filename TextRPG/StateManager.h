#pragma once
#include "BaseIncludes.h"
#include "State.h"

class StateManager
{
private:
	static std::unique_ptr<StateManager> mInstance;
	std::vector<std::unique_ptr<State>> mStates;

	bool StateExists(const StateType &stateType);

public:
	StateManager(State initialState);
	State* GetCurrentState();

	/// <summary>Push a new state onto the stack. If the state already exists on the stack, pop to it to avoid loops</summary>
	void PushState(State newState);

	/// <summary>Pop and return the current state. Cannot have an empty state so returns the bottom state without popping if only 1 state</summary>
	State* PopState();

	/// <summary>If the state exists, pop to it, otherwise returns nullptr</summary>
	State* PopToState(StateType stateType);

	/// <summary>If the state exists, pop to it, otherwise returns nullptr</summary>
	State* PopToState(State state);

	/// <summary>Pops to the bottom state and returns it</summary>
	State* PopToBottom();

	// Singleton
	static StateManager* Init(State initialState);

	static StateManager* GetInstance();
};