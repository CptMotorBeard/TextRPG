#include "StateManager.h"

StateManager* StateManager::mInstance = nullptr;

bool StateManager::StateExists(const StateType &stateType) const
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

StateManager::StateManager(State* initialState)
{
	mStates.emplace_back(initialState);
}

std::shared_ptr<State> StateManager::GetCurrentState() const
{	
	return mStates.back();
}

void StateManager::PushState(State* newState)
{
	std::shared_ptr<State> stateExists = PopToState(newState->GetStateType());
	if (stateExists != nullptr)
	{
		PopState();
	}

	if (newState->GetStateType() != GetCurrentState()->GetStateType())
	{
		mStates.emplace_back(newState);
		GetCurrentState()->ForceRebuild();
	}
}

std::shared_ptr<State> StateManager::PopState(bool rebuild)
{
	std::shared_ptr<State> topState = GetCurrentState();
	if (mStates.size() > 1)
	{
		mStates.pop_back();
	}

	if (rebuild)
	{
		GetCurrentState()->ForceRebuild();
	}

	return topState;
}

std::shared_ptr<State> StateManager::PopToState(const StateType& stateType)
{
	if (StateExists(stateType))
	{
		while (GetCurrentState()->GetStateType() != stateType)
		{
			auto state = PopState(false);
		}

		GetCurrentState()->ForceRebuild();
		return GetCurrentState();
	}

	return nullptr;
}

std::shared_ptr<State> StateManager::PopToState(const State &state)
{
	return PopToState(state.GetStateType());
}

std::shared_ptr<State> StateManager::PopToBottom()
{
	while (mStates.size() > 1)
	{
		auto state = PopState();
	}

	return GetCurrentState();
}

std::vector<std::string> StateManager::AllStatesAsStrings() const
{
	std::vector<std::string> ret;
	ret.resize(mStates.size());

	int index = 0;

	for (auto const &state : mStates)
	{
		auto stateType = state->GetStateType();
		auto stateString = State::StateStringMap.find(stateType);

		if (stateString != State::StateStringMap.end())
		{
			ret[index] = stateString->second;
			++index;
		}
	}

	return ret;
}

StateManager& StateManager::Init(State* initialState)
{
	assert(mInstance == nullptr && "Cannot initialize the state manager :: It is already initilized");
	mInstance = new StateManager(initialState);
	return *mInstance;
}

StateManager& StateManager::GetInstance()
{
	assert(mInstance != nullptr && "Need to initialize the state manager");
	return *mInstance;
};

void StateManager::Shutdown()
{
	for (auto const& state : mStates)
	{
		assert(state.use_count() == 1);
	}

	delete this;
}