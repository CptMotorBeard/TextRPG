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

StateManager::StateManager(std::shared_ptr<State> initialState)
{
	mStates = std::vector<std::shared_ptr<State>>();
	mStates.push_back(initialState);
}

std::shared_ptr<State> StateManager::GetCurrentState()
{	
	return mStates.back();
}

void StateManager::PushState(std::shared_ptr<State> newState)
{
	std::shared_ptr<State> stateExists = PopToState(newState->GetStateType());
	if (stateExists != nullptr)
	{
		PopState();
	}

	mStates.push_back(newState);
}

std::shared_ptr<State> StateManager::PopState()
{
	std::shared_ptr<State> topState = GetCurrentState();
	if (mStates.size() > 1)
	{
		mStates.pop_back();
	}
	return topState;
}

std::shared_ptr<State> StateManager::PopToState(StateType stateType)
{
	if (StateExists(stateType))
	{
		while (GetCurrentState()->GetStateType() != stateType)
		{
			auto state = PopState();
			const bool unique = state.unique();
			assert(unique && "Shouldn't be holding on to states after they are popped");
		}

		return GetCurrentState();
	}

	return nullptr;
}

std::shared_ptr<State> StateManager::PopToState(State state)
{
	return PopToState(state.GetStateType());
}

std::shared_ptr<State> StateManager::PopToBottom()
{
	while (mStates.size() > 1)
	{
		auto state = PopState();
		const bool unique = state.unique();
		assert(unique && "Shouldn't be holding on to states after they are popped");
	}

	return GetCurrentState();
}

StateManager* StateManager::Init(std::shared_ptr<State> initialState)
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
	for (auto const& state : mInstance->mStates)
	{
		const bool unique = state.unique();
		assert(unique && "A state was still being held after shutdown");
	}

	mInstance->mStates.clear();

	delete mInstance;
};