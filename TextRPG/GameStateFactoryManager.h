#pragma once
#include "BaseIncludes.h"

#include "State.h"

#define REGISTER_FACTORY(FactoryString) mInstance->RegisterFactory(#FactoryString, new State##FactoryString##Factory())

class GameStateFactoryManager
{
private:
	static std::unique_ptr<GameStateFactoryManager> mInstance;
	std::unordered_map<std::string, std::unique_ptr<StateFactory>> mFactories;
public:
	static GameStateFactoryManager* GetInstance();

	void RegisterFactory(const std::string &stateType, StateFactory* stateFactory);
	State* Create(const std::string &stateType);
};