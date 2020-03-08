#include "SFML/Graphics.hpp"
#include "SFML/System/Clock.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

int main()
{
	bool debugWindow = false;

	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
	ImGui::SFML::Init(window);

	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };
	char windowTitle[255] = "ImGui + SFML = <3";
	window.setTitle(windowTitle);

	window.resetGLStates();
	sf::Clock deltaClock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Tilde)
				{
					debugWindow = !debugWindow;
				}
			}
		}

		// All widgets must be created between update and render
		ImGui::SFML::Update(window, deltaClock.restart());

		if (debugWindow)
		{
			ImGui::ShowMetricsWindow();
		}		

		window.clear(bgColor);
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}