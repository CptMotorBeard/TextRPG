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
	StateManager* stateManager = StateManager::Init(std::make_shared<StateMainMenu>());
	
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

	sf::Font sfRoboto = sf::Font();
	sfRoboto.loadFromFile("Resources/Roboto Font/Roboto-Regular.ttf");
	ImFont* pImguiRoboto = ImGui::GetIO().Fonts->AddFontFromFileTTF("Resources/Roboto Font/Roboto-Regular.ttf", 18);
	ImGui::SFML::UpdateFontTexture();

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
					stateManager->PushState(std::make_shared<StateSaveGame>());
				}
				if (ImGui::MenuItem("Load Game"))
				{
					stateManager->PushState(std::make_shared<StateLoadGame>());
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
		stateManager->GetCurrentState()->PreRender(window, &sfRoboto);
		ImGui::SFML::Render(window);
		stateManager->GetCurrentState()->PostRender(window, &sfRoboto);
		window.display();
	}

	ImGui::SFML::Shutdown();
	StateManager::Shutdown();
	LocalizationManager::Shutdown();
	LuaManager::Shutdown();
}