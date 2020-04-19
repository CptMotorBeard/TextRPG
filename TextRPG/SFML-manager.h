#pragma once
#include "BaseIncludes.h"
#include "SFML/Graphics.hpp"
#include "SFML/System/Clock.hpp"

class SFML_Manager
{
private:
	static std::unique_ptr<SFML_Manager> mInstance;
public:
	static SFML_Manager* Initialize(sf::VideoMode mode, const sf::String &title);
	static SFML_Manager* GetInstance();

	sf::RenderWindow Window;
	sf::Clock DeltaClock;
	bool WindowWasResized;

	SFML_Manager(sf::VideoMode mode, const sf::String& title);
	bool ProcessEvents(sf::Event& sfEvent);
};