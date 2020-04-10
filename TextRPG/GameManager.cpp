#include "GameManager.h"
GameManager* GameManager::mInstance = nullptr;

GameManager* GameManager::Init()
{
	mInstance = new GameManager();

	mInstance->mGlobalFont = std::make_unique<sf::Font>();
	mInstance->mGlobalFont->loadFromFile("Resources/Roboto Font/Roboto-Regular.ttf");

	return mInstance;
}

void GameManager::Shutdown()
{
	delete mInstance;
}

GameManager* GameManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		Init();
	}

	return mInstance;
}

sf::Font* GameManager::GetGlobalFont()
{
	return mGlobalFont.get();
}