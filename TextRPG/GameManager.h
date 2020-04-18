#pragma once
#include "BaseIncludes.h"
#include "SFML/Graphics.hpp"

class GameManager
{
private:
	static std::unique_ptr<GameManager> mInstance;
	std::unique_ptr<sf::Font> mGlobalFont;

public:
	static GameManager* GetInstance();

	sf::Font* GetGlobalFont();
};