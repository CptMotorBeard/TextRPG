#include "StateMainMenu.h"

void StateMainMenu::Build()
{
	
}

void StateMainMenu::ProcessEvents(const sf::Event &sfEvent)
{

}

void StateMainMenu::PreRender(sf::RenderTarget& target)
{
	sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(100, 100));
	target.draw(shape);
}

void StateMainMenu::PostRender(sf::RenderTarget& target)
{

}