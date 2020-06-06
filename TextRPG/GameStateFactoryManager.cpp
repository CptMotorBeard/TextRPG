#include "GameStateFactoryManager.h"

#include "GameStates.h"

std::unique_ptr<GameStateFactoryManager> GameStateFactoryManager::mInstance = nullptr;

GameStateFactoryManager* GameStateFactoryManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = std::make_unique<GameStateFactoryManager>();

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

	return mInstance.get();
}

void GameStateFactoryManager::RegisterFactory(const std::string &stateType, StateFactory* stateFactory)
{
	mFactories.insert(std::pair<std::string, std::unique_ptr<StateFactory>>(stateType, stateFactory->make_unique()));
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