#include "GameManager.h"

GameManager& GameManager::GetInstance()
{
	static GameManager* mInstance = nullptr;
	if (mInstance == nullptr)
	{
		mInstance = new GameManager();

		mInstance->mGlobalFont = new sf::Font();
		mInstance->mGlobalFont->loadFromFile("Resources/Roboto Font/Roboto-Regular.ttf");
	}

	return *mInstance;
}

void GameManager::Shutdown()
{
	delete mGlobalFont;
	delete this;
}

GameManager::GameManager()
{
	mGlobalFont = nullptr;
}

sf::Font* GameManager::GetGlobalFont()
{
	return mGlobalFont;
}