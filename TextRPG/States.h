#pragma once
#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Graphics.hpp"

#include <vector>

class State
{
public:
	enum class StateType
	{

	};

	State() {};
	StateType GetStateType();

	virtual ~State() {};
	virtual void Build() {};

private:
	StateType mStateType;
};

class StateManager
{
private:
	static StateManager* mInstance;
	std::vector<State *> mStates;

	bool StateExists(State::StateType stateType)
	{
		for (std::vector<State *>::iterator iter = mStates.begin(); iter != mStates.end(); ++iter)
		{
			if ((*iter)->GetStateType() == stateType)
			{
				return true;
			}
		}

		return false;
	}

public:
	StateManager(State* initialState)
	{
		mStates = std::vector<State *>();
		mStates.push_back(initialState);
	}

	State* GetCurrentState()
	{
		return mStates[mStates.size() - 1];
	}

	/// <summary>Push a new state onto the stack. If the state already exists on the stack, pop to it to avoid loops</summary>
	void PushState(State *newState)
	{
		State* stateExists = PopToState(newState->GetStateType());
		if (stateExists != nullptr)
		{
			PopState();
		}

		mStates.push_back(newState);
	}

	/// <summary>Pop and return the current state. Cannot have an empty state so returns the bottom state without popping if only 1 state</summary>
	State* PopState()
	{
		State* topState = GetCurrentState();
		if (mStates.size() > 1)
		{
			mStates.pop_back();
		}
		return topState;
	}

	/// <summary>If the state exists, pop to it, otherwise returns nullptr</summary>
	State* PopToState(State::StateType stateType)
	{
		if (StateExists(stateType))
		{
			while (GetCurrentState()->GetStateType() != stateType)
			{
				PopState();
			}

			return GetCurrentState();
		}

		return nullptr;
	}

	/// <summary>If the state exists, pop to it, otherwise returns nullptr</summary>
	State* PopToState(State state)
	{
		return PopToState(state.GetStateType());
	}

	/// <summary>Pops to the bottom state and returns it</summary>
	State* PopToBottom()
	{
		while (mStates.size() > 1)
		{
			mStates.pop_back();
		}			

		return GetCurrentState();
	}

	// Singleton
	static StateManager* Init(State* initialState)
	{
		delete mInstance;
		mInstance = new StateManager(initialState);
		return mInstance;
	};

	static StateManager *GetInstance()
	{
		return mInstance;
	};

	static void Shutdown()
	{
		delete mInstance;
	};
};