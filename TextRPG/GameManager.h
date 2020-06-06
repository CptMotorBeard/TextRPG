#pragma once

#include "BaseIncludes.h"
#include "SFML/Graphics.hpp"

class GameManager
{
private:	
	sf::Font* mGlobalFont;

	GameManager();
	GameManager(const GameManager& other) = delete;

public:
	static GameManager& GetInstance();
	void Shutdown();

	sf::Font* GetGlobalFont();
};