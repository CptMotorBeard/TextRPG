#pragma once
#include "BaseIncludes.h"
#include "State.h"

class GameStateFactoryManager
{
private:
	static std::unique_ptr<GameStateFactoryManager> mInstance;
	std::unordered_map<std::string, std::unique_ptr<StateFactory>> mFactories;
public:
	static GameStateFactoryManager* GetInstance();

	void RegisterFactory(std::string stateType, StateFactory* stateFactory);
	State* Create(std::string stateType);
};