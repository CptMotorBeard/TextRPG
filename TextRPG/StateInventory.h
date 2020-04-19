#pragma once
#include "State.h"

class StateInventory : public State
{
public:
	StateInventory() : State(StateType::STATEINVENTORY, "Resources/LUA/StateInventory.lua") { };
};

class StateInventoryFactory : public StateFactory
{
public:
	virtual StateInventory* Create() override
	{
		return new StateInventory();
	};

	virtual std::unique_ptr<StateFactory> Clone() override
	{
		return std::make_unique<StateInventoryFactory>(*this);
	}
};