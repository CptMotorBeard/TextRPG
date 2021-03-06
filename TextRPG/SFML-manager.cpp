#include "SFML-manager.h"

SFML_Manager* SFML_Manager::mInstance = nullptr;

SFML_Manager& SFML_Manager::Initialize(const sf::VideoMode &mode, const sf::String& title)
{
	mInstance = new SFML_Manager(mode, title);

	return *mInstance;
}

SFML_Manager& SFML_Manager::GetInstance()
{
	assert(mInstance != nullptr && "SFML_Manager was never initialized");
	return *mInstance;
}

void SFML_Manager::Shutdown()
{
	delete this;
}

SFML_Manager::SFML_Manager(const sf::VideoMode &mode, const sf::String& title)
{
	WindowWasResized = false;
	Window.create(mode, title);
}

bool SFML_Manager::ProcessEvents(sf::Event& sfEvent)
{
	bool r = Window.pollEvent(sfEvent);
	WindowWasResized = false;

	if (sfEvent.type == sf::Event::Closed)
	{
		Window.close();
	}
	else if (sfEvent.type == sf::Event::Resized)
	{
		sf::FloatRect visibleArea(0, 0, (float)sfEvent.size.width, (float)sfEvent.size.height);
		Window.setView(sf::View(visibleArea));

		WindowWasResized = true;
	}

	return r;
}