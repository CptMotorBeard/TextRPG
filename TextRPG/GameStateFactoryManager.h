#pragma once
#include "BaseIncludes.h"

#include "State.h"

#define REGISTER_FACTORY(FactoryString) mInstance->RegisterFactory(#FactoryString, new State##FactoryString##Factory())

class GameStateFactoryManager
{
private:
	std::unordered_map<std::string, StateFactory*> mFactories;
public:
	static GameStateFactoryManager& GetInstance();
	void Shutdown();

	void RegisterFactory(const std::string &stateType, StateFactory* stateFactory);
	State* Create(const std::string &stateType);
};