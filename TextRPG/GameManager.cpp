#include "GameManager.h"
std::unique_ptr<GameManager> GameManager::mInstance = nullptr;

GameManager* GameManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = std::make_unique<GameManager>();

		mInstance->mGlobalFont = std::make_unique<sf::Font>();
		mInstance->mGlobalFont->loadFromFile("Resources/Roboto Font/Roboto-Regular.ttf");
	}

	return mInstance.get();
}

sf::Font* GameManager::GetGlobalFont()
{
	return mGlobalFont.get();
}