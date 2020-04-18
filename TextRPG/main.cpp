#include "BaseIncludes.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include "LocalizationManager.h"
#include "LUA.h"

#include "SFML/Graphics.hpp"
#include "SFML/System/Clock.hpp"

#include "GameStates.h"
#include "GameManager.h"

#include "SFML-extensions.h"

int main()
{
	GameManager* gameManager = GameManager::GetInstance();
	LocalizationManager* locManager = LocalizationManager::GetInstance();
	StateManager* stateManager = StateManager::Init(StateMainMenu());	
	
	bool debugWindow = false;

	auto p = locManager->GetLocByKey("ENTRY_TITLE");
	const char* windowTitle = p->c_str();

	sf::RenderWindow window(sf::VideoMode(640, 480), windowTitle);
	ImGui::SFML::Init(window);	

	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };

	window.resetGLStates();
	sf::Clock deltaClock;

	ImGuiIO& io = ImGui::GetIO();

	ImFont* pImguiRoboto = ImGui::GetIO().Fonts->AddFontFromFileTTF("Resources/Roboto Font/Roboto-Regular.ttf", 18);
	ImGui::SFML::UpdateFontTexture();

	window.setFramerateLimit(24);

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
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Main Menu"))
				{
					stateManager->PopToBottom();
				}
				if (ImGui::MenuItem("Save Game"))
				{
					stateManager->PushState(StateSaveGame());
				}
				if (ImGui::MenuItem("Load Game"))
				{
					stateManager->PushState(StateLoadGame());
				}

				if (ImGui::MenuItem("Quit"))
				{
					window.close();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
		
		stateManager->GetCurrentState()->Build();
		
		if (debugWindow)
		{
			ImGui::ShowMetricsWindow();
		}

		window.clear(bgColor);
		ImGui::ShowDemoWindow();
		stateManager->GetCurrentState()->Render(window);
		ImGui::SFML::Render(window);
		window.display();

		stateManager->GetCurrentState()->RecalculateHash();
	}

	ImGui::SFML::Shutdown();
	LocalizationManager::Shutdown();
	LuaManager::Shutdown();
}