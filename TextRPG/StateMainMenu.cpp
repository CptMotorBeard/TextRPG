#include "StateMainMenu.h"

void StateMainMenu::Build(lua_State* L)
{
	
}

void StateMainMenu::ProcessEvents(const sf::Event &sfEvent)
{

}

void StateMainMenu::PreRender(sf::RenderTarget& target, lua_State* L)
{
	sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(100, 100));
	target.draw(shape);
}

void StateMainMenu::PostRender(sf::RenderTarget& target, lua_State* L)
{

}