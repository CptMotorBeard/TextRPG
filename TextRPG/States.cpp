#include "States.h"

StateManager* StateManager::mInstance = nullptr;

State::StateType State::GetStateType()
{
	return mStateType;
}

bool StateManager::StateExists(State::StateType stateType)
{
	for (std::vector<State*>::iterator iter = mStates.begin(); iter != mStates.end(); ++iter)
	{
		if ((*iter)->GetStateType() == stateType)
		{
			return true;
		}
	}

	return false;
}

StateManager::StateManager(State* initialState)
{
	mStates = std::vector<State*>();
	mStates.push_back(initialState);
}

State* StateManager::GetCurrentState()
{
	return mStates[mStates.size() - 1];
}

void StateManager::PushState(State* newState)
{
	State* stateExists = PopToState(newState->GetStateType());
	if (stateExists != nullptr)
	{
		PopState();
	}

	mStates.push_back(newState);
}

State* StateManager::PopState()
{
	State* topState = GetCurrentState();
	if (mStates.size() > 1)
	{
		mStates.pop_back();
	}
	return topState;
}

State* StateManager::PopToState(State::StateType stateType)
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

State* StateManager::PopToState(State state)
{
	return PopToState(state.GetStateType());
}

State* StateManager::PopToBottom()
{
	while (mStates.size() > 1)
	{
		mStates.pop_back();
	}

	return GetCurrentState();
}

StateManager* StateManager::Init(State* initialState)
{
	delete mInstance;
	mInstance = new StateManager(initialState);
	return mInstance;
}

StateManager* StateManager::GetInstance()
{
	return mInstance;
};

void StateManager::Shutdown()
{
	delete mInstance;
};