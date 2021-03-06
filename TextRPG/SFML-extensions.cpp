#include "SFML-extensions.h"

#include "GameManager.h"

namespace sf_ext
{
	void SFML_Button::SetupButton(const sf::Text &text, const sf::FloatRect &rect, std::function<void(void)> callback, const sf::Color &backColour)
	{
		mButtonHitbox = rect;
		mButtonColour = backColour;

		mButtonRectangle.setFillColor(backColour);
		mButtonRectangle.setSize(sf::Vector2f(rect.width, rect.height));
		mButtonRectangle.setPosition(rect.left, rect.top);

		mButtonText = text;

		sf::FloatRect textBounds = mButtonText.getGlobalBounds();
		float verticalOffset = (rect.height / 2) - (textBounds.height / 2);
		float horizontalOffset = (rect.width / 2) - (textBounds.width / 2);

		mButtonText.setPosition(rect.left + horizontalOffset, rect.top + verticalOffset);

		mCallback = callback;
	}

	SFML_Button::SFML_Button(const std::string &string, const sf::FloatRect &rect, std::function<void(void)> callback, const sf::Color &backColour)
	{
		unsigned int fontSize = 12;
		sf::Color fontColor = sf::Color::Black;

		sf::Text t(string, *GameManager::GetInstance().GetGlobalFont());
		t.setCharacterSize(fontSize);
		t.setFillColor(fontColor);

		SetupButton(t, rect, callback, backColour);
	};

	SFML_Button::SFML_Button(const sf::Text &text, const sf::FloatRect &rect, std::function<void(void)> callback, const sf::Color &backColour)
	{
		SetupButton(text, rect, callback, backColour);
	};

	void SFML_Button::Draw(sf::RenderTarget& target) const
	{
		target.draw(mButtonRectangle);
		target.draw(mButtonText);
	}

	void SFML_Button::ProcessEvents(sf::Event const& sfEvent)
	{
		bool didLeftClick = sfEvent.mouseButton.button == sf::Mouse::Button::Left;
		bool isClickingButton = false;

		if (sfEvent.type == sf::Event::MouseButtonPressed)
		{
			isClickingButton = mButtonHitbox.intersects(sf::FloatRect(sfEvent.mouseButton.x, sfEvent.mouseButton.y, 1, 1));

			if (didLeftClick && isClickingButton && !mHolding)
			{
				sf::Color shaded = mButtonColour;
				shaded.r /= 2;
				shaded.g /= 2;
				shaded.b /= 2;

				mButtonRectangle.setFillColor(shaded);
				mHolding = true;
			}
		}
		else if (sfEvent.type == sf::Event::MouseButtonReleased)
		{
			isClickingButton = mButtonHitbox.intersects(sf::FloatRect(sfEvent.mouseButton.x, sfEvent.mouseButton.y, 1, 1));

			if (didLeftClick && isClickingButton)
			{
				mButtonRectangle.setFillColor(mButtonColour);
				mHolding = false;

				if (mCallback)
				{
					mCallback();
				}				
			}
		}
		else if (sfEvent.type == sf::Event::MouseMoved)
		{
			isClickingButton = mButtonHitbox.intersects(sf::FloatRect(sfEvent.mouseMove.x, sfEvent.mouseMove.y, 1, 1));

			if (!isClickingButton && mHolding)
			{
				mButtonRectangle.setFillColor(mButtonColour);
				mHolding = false;
			}
		}
	}
}