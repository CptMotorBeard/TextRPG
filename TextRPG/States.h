#pragma once
#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Graphics.hpp"

#include <vector>

class StateManager
{
private:
	std::vector<State *> mStates;

	bool StateExists(State::StateType stateType)
	{
		for (std::vector<State>::iterator iter = mStates.begin; iter != mStates.end; ++iter)
		{
			if (iter->GetStateType() == stateType)
			{
				return true;
			}
		}

		return false;
	}

public:
	State* GetCurrentState()
	{
		return mStates[mStates.size() - 1];
	}

	void PushState(State *newState)
	{
		if (StateExists(newState->GetStateType()))
		{

		}
		mStates.push_back(newState);
	}

	State* PopState()
	{
		State* topState = GetCurrentState();
		if (mStates.size > 1)
		{
			mStates.pop_back();
		}
		return topState;
	}

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

	State* PopToState(State state)
	{
		return PopToState(state.GetStateType());
	}

	State* PopToBottom()
	{
		while (mStates.size > 1)
		{
			mStates.pop_back();
		}			

		return GetCurrentState();
	}
};

class State
{
public:
	enum StateType
	{

	};

	State();	
	StateType GetStateType();

	virtual ~State() {};
	virtual void RenderCurrentState(sf::RenderWindow window) {};

private:
	StateType mStateType;
};