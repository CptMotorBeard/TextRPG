#pragma once
#include "BaseIncludes.h"
#include "State.h"

class State;
enum class StateType;

class StateManager
{
private:
	static StateManager* mInstance;
	std::vector<std::shared_ptr<State>> mStates;

	bool StateExists(StateType stateType);

public:
	StateManager(std::shared_ptr<State> initialState);
	std::shared_ptr<State> GetCurrentState();

	/// <summary>Push a new state onto the stack. If the state already exists on the stack, pop to it to avoid loops</summary>
	void PushState(std::shared_ptr<State> newState);

	/// <summary>Pop and return the current state. Cannot have an empty state so returns the bottom state without popping if only 1 state</summary>
	std::shared_ptr<State> PopState();

	/// <summary>If the state exists, pop to it, otherwise returns nullptr</summary>
	std::shared_ptr<State> PopToState(StateType stateType);

	/// <summary>If the state exists, pop to it, otherwise returns nullptr</summary>
	std::shared_ptr<State> PopToState(State state);

	/// <summary>Pops to the bottom state and returns it</summary>
	std::shared_ptr<State> PopToBottom();

	// Singleton
	static StateManager* Init(std::shared_ptr<State> initialState);

	static StateManager* GetInstance();

	static void Shutdown();
};