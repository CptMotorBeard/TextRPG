#include "State.h"

State::State(StateType stateType)
{
	State::mStateType = stateType;
}

const StateType& State::GetStateType()
{
	return mStateType;
}