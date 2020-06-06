#include "GameStateFactoryManager.h"

#include "GameStates.h"

GameStateFactoryManager& GameStateFactoryManager::GetInstance()
{
	static GameStateFactoryManager* mInstance = nullptr;

	if (mInstance == nullptr)
	{
		mInstance = new GameStateFactoryManager();

		// Initialize all of the factories
		REGISTER_FACTORY(BuildingUpgrades);
		REGISTER_FACTORY(CharacterCreation);
		REGISTER_FACTORY(CharacterOverview);
		REGISTER_FACTORY(CityUpgrades);
		REGISTER_FACTORY(Combat);
		REGISTER_FACTORY(Diplomacy);
		REGISTER_FACTORY(FactionCreation);
		REGISTER_FACTORY(FactionOverview);
		REGISTER_FACTORY(Inventory);
		REGISTER_FACTORY(LoadGame);
		REGISTER_FACTORY(MainMenu);
		REGISTER_FACTORY(SaveGame);
		REGISTER_FACTORY(UnitUpgrades);
		REGISTER_FACTORY(WorldOverview);
	}

	return *mInstance;
}

void GameStateFactoryManager::RegisterFactory(const std::string &stateType, StateFactory* stateFactory)
{
	mFactories.insert(std::pair<std::string, StateFactory*>(stateType, stateFactory));
}

State* GameStateFactoryManager::Create(const std::string &stateType)
{
	auto factory = mFactories.find(stateType);
	if (factory != mFactories.end())
	{
		return factory->second->Create();
	}

	return nullptr;
}

void GameStateFactoryManager::Shutdown()
{
	for (const auto& pair : mFactories)
	{
		delete pair.second;
	}

	mFactories.clear();
	delete this;
}