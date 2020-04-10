#pragma once
#include "BaseIncludes.h"
#include "SFML/Graphics.hpp"

class GameManager
{
private:
	static GameManager *mInstance;	
	std::unique_ptr<sf::Font> mGlobalFont;

public:	
	static GameManager* Init();
	static void Shutdown();
	static GameManager* GetInstance();

	sf::Font* GetGlobalFont();
};