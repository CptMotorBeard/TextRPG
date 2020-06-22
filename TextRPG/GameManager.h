#pragma once

#include "BaseIncludes.h"
#include "SFML/Graphics.hpp"
#include "World.h"

class GameManager
{
private:	
	sf::Font* mGlobalFont;

	GameManager();
	GameManager(const GameManager& other) = delete;

public:
	World GameWorld;

	static GameManager& GetInstance();
	void Shutdown();

	void SaveGame(uint8 fileNumber);
	void LoadGame(uint8 fileNumber);

	sf::Font* GetGlobalFont();
};