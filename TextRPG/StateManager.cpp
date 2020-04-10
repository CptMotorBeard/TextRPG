#include "StateManager.h"

StateManager* StateManager::mInstance = nullptr;

bool StateManager::StateExists(StateType stateType)
{
	for (auto const& state : mStates)
	{
		if (state->GetStateType() == stateType)
		{
			return true;
		}
	}

	return false;
}

StateManager::StateManager(State initialState)
{
	mStates.push_back(std::make_unique<State>(initialState));
}

State* StateManager::GetCurrentState()
{	
	return mStates.back().get();
}

void StateManager::PushState(State newState)
{
	State* stateExists = PopToState(newState.GetStateType());
	if (stateExists != nullptr)
	{
		PopState();
	}

	mStates.push_back(std::make_unique<State>(newState));
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

State* StateManager::PopToState(StateType stateType)
{
	if (StateExists(stateType))
	{
		while (GetCurrentState()->GetStateType() != stateType)
		{
			auto state = PopState();
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
		auto state = PopState();
	}

	return GetCurrentState();
}

StateManager* StateManager::Init(State initialState)
{
	assert(mInstance == nullptr && "Cannot initialize the state manager :: It is already initilized");
	mInstance = new StateManager(initialState);
	return mInstance;
}

StateManager* StateManager::GetInstance()
{
	return mInstance;
};

void StateManager::Shutdown()
{
	mInstance->mStates.clear();

	delete mInstance;
};