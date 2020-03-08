#include "States.h"

StateManager* StateManager::mInstance = nullptr;

State::StateType State::GetStateType()
{
	return mStateType;
}