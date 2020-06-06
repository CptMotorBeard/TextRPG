#pragma once
#include "BaseIncludes.h"

#include "SFML/Graphics.hpp"
#include <functional>

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

		std::function<void(void)> mCallback;

		void SetupButton(const sf::Text &text, const sf::FloatRect &rect, std::function<void(void)>& callback, const sf::Color &backColour = sf::Color::White);

	public:
		SFML_Button(const std::string &string, const sf::FloatRect &rect, std::function<void(void)>& callback, const sf::Color &backColour = sf::Color::White);
		SFML_Button(const sf::Text &text, const sf::FloatRect &rect, std::function<void(void)>& callback, const sf::Color &backColour = sf::Color::White);

		void Draw(sf::RenderTarget& target) const;

		void ProcessEvents(sf::Event const& sfEvent);
	};
}