#pragma once
#include "BaseIncludes.h"
#include "State.h"

class StateManager
{
private:
	static std::unique_ptr<StateManager> mInstance;
	std::vector<std::shared_ptr<State>> mStates;

	bool StateExists(const StateType &stateType);

public:
	StateManager(State initialState);
	~StateManager();

	std::shared_ptr<State> GetCurrentState();

	/// <summary>Push a new state onto the stack. If the state already exists on the stack, pop to it to avoid loops</summary>
	void PushState(State newState);

	/// <summary>Pop and return the current state. Cannot have an empty state so returns the bottom state without popping if only 1 state</summary>
	std::shared_ptr<State> PopState(bool rebuild=true);

	/// <summary>If the state exists, pop and return it, otherwise returns nullptr</summary>
	std::shared_ptr<State> PopToState(StateType stateType);

	/// <summary>If the state exists, pop and return it, otherwise returns nullptr</summary>
	std::shared_ptr<State> PopToState(State state);

	/// <summary>Pops to the bottom state and returns it</summary>
	std::shared_ptr<State> PopToBottom();

	std::vector<std::string> AllStatesAsStrings();

	// Singleton
	static StateManager* Init(State initialState);

	static StateManager* GetInstance();
};