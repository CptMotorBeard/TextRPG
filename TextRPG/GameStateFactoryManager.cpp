#include "GameStateFactoryManager.h"
#include "GameStates.h"

std::unique_ptr<GameStateFactoryManager> GameStateFactoryManager::mInstance = nullptr;

GameStateFactoryManager* GameStateFactoryManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = std::make_unique<GameStateFactoryManager>();

		// Initialize all of the factories
		mInstance->RegisterFactory("BuildingUpgrades", new StateBuildingUpgradesFactory());
		mInstance->RegisterFactory("CharacterCreation", new StateCharacterCreationFactory());
		mInstance->RegisterFactory("CharacterOverview", new StateCharacterOverviewFactory());
		mInstance->RegisterFactory("CityUpgrades", new StateCityUpgradesFactory());
		mInstance->RegisterFactory("Combat", new StateCombatFactory());
		mInstance->RegisterFactory("Diplomacy(", new StateDiplomacyFactory());
		mInstance->RegisterFactory("FactionCreation", new StateFactionCreationFactory());
		mInstance->RegisterFactory("FactionOverview", new StateFactionOverviewFactory());
		mInstance->RegisterFactory("Inventory(", new StateInventoryFactory());
		mInstance->RegisterFactory("LoadGame", new StateLoadGameFactory());
		mInstance->RegisterFactory("MainMenu", new StateMainMenuFactory());
		mInstance->RegisterFactory("SaveGame", new StateSaveGameFactory());
		mInstance->RegisterFactory("UnitUpgrades", new StateUnitUpgradesFactory());
		mInstance->RegisterFactory("WorldOverview", new StateWorldOverviewFactory());
	}

	return mInstance.get();
}

void GameStateFactoryManager::RegisterFactory(std::string stateType, StateFactory* stateFactory)
{
	mFactories.insert(std::pair<std::string, std::unique_ptr<StateFactory>>(stateType, stateFactory->Clone()));
}

State* GameStateFactoryManager::Create(std::string stateType)
{
	auto factory = mFactories.find(stateType);
	if (factory != mFactories.end())
	{
		return factory->second->Create();
	}

	return nullptr;
}