#pragma once

#include "BaseIncludes.h"
#include "GameManager.h"
#include "SFML/Graphics.hpp"

namespace sf_ext
{
	class SFML_Button
	{
	private:
		sf::RectangleShape mButtonRectangle;
		sf::Color mButtonColour;

		sf::FloatRect mButtonHitbox;
		sf::Text mButtonText;

		bool mHolding = false;		

		void(*mCallback)();

		void SetupButton(sf::Text text, sf::FloatRect rect, void(*callback)(), sf::Color backColour = sf::Color::White);

	public:
		SFML_Button(std::string string, sf::FloatRect rect, void(*callback)(), sf::Color backColour = sf::Color::White);
		SFML_Button(sf::Text text, sf::FloatRect rect, void(*callback)(), sf::Color backColour = sf::Color::White);

		void Draw(sf::RenderTarget& target);

		void ProcessEvents(sf::Event const& sfEvent);
	};
}