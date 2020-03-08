#pragma once
#include "SFML/Graphics.hpp"

class Panel
{
	sf::RectangleShape parent;
	sf::RectangleShape child;

public:

	Panel(float width, float height)
	{
		parent = sf::RectangleShape(sf::Vector2f(width, 25));
		child = sf::RectangleShape(sf::Vector2f(width, height));

		parent.setFillColor(sf::Color::Blue);
		child.setFillColor(sf::Color::Cyan);
	}

	sf::Vector2f getPosition()
	{
		return parent.getPosition();
	}

	void setPosition(const sf::Vector2f& position)
	{
		parent.setPosition(position);
		child.setPosition(position);
	}

	void setPosition(float x, float y)
	{
		parent.setPosition(x, y);
		child.setPosition(x, y);
	}

	void setHeaderColor(sf::Color color)
	{
		parent.setFillColor(color);
	}

	void setPanelColor(sf::Color color)
	{
		child.setFillColor(color);
	}

	void draw(sf::RenderWindow* window)
	{
		window->draw(child);
		window->draw(parent);
	}

	sf::FloatRect getParentGlobalBounds()
	{
		return parent.getGlobalBounds();
	}

	sf::FloatRect getGlobalBounds()
	{
		return child.getGlobalBounds();
	}
};