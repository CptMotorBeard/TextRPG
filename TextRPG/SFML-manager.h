#pragma once
#include "BaseIncludes.h"
#include "SFML/Graphics.hpp"

class SFML_Manager
{
private:
	
	SFML_Manager() = delete;
	SFML_Manager(const SFML_Manager& other) = delete;
	SFML_Manager(const sf::VideoMode& mode, const sf::String& title);

	static SFML_Manager* mInstance;

public:
	static SFML_Manager& Initialize(const sf::VideoMode &mode, const sf::String &title);
	static SFML_Manager& GetInstance();

	void Shutdown();

	sf::RenderWindow Window;
	sf::Clock DeltaClock;
	bool WindowWasResized;
	
	bool ProcessEvents(sf::Event& sfEvent);
};