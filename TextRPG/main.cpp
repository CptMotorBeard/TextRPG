#include "BaseIncludes.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include "LocalizationManager.h"
#include "LUA.h"

#include "SFML/Graphics.hpp"
#include "SFML/System/Clock.hpp"

#include "GameStates.h"

int main()
{
	LocalizationManager* locManager = LocalizationManager::GetInstance();
	StateManager* stateManager = StateManager::Init(new StateMainMenu());

	bool debugWindow = false;

	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
	ImGui::SFML::Init(window);	

	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };

	auto p = locManager->GetLocByKey("ENTRY_TITLE");

	const char* windowTitle = p->c_str();
	window.setTitle(windowTitle);

	window.resetGLStates();
	sf::Clock deltaClock;

	while (window.isOpen())
	{
		sf::Event sfEvent;
		while (window.pollEvent(sfEvent))
		{
			ImGui::SFML::ProcessEvent(sfEvent);
			stateManager->GetCurrentState()->ProcessEvents(sfEvent);

			if (sfEvent.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (sfEvent.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, (float)sfEvent.size.width, (float)sfEvent.size.height);
				window.setView(sf::View(visibleArea));
			}
			else if (sfEvent.type == sf::Event::KeyReleased)
			{
				if (sfEvent.key.code == sf::Keyboard::Tilde)
				{
					debugWindow = !debugWindow;
				}
			}
		}
		
		// All widgets must be created between update and render
		ImGui::SFML::Update(window, deltaClock.restart());
		stateManager->GetCurrentState()->Build();

		if (debugWindow)
		{
			ImGui::ShowMetricsWindow();
		}

		window.clear(bgColor);

		stateManager->GetCurrentState()->PreRender(window);
		ImGui::SFML::Render(window);
		stateManager->GetCurrentState()->PostRender(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	StateManager::Shutdown();
	LocalizationManager::Shutdown();
	LuaManager::Shutdown();
}