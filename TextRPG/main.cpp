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
#include "SFML-manager.h"

int main()
{
	GameManager* gameManager = GameManager::GetInstance();
	LocalizationManager* locManager = LocalizationManager::GetInstance();
	StateManager* stateManager = StateManager::Init(StateMainMenu());	
	SFML_Manager* sfmlManager;
	
	auto p = locManager->GetLocByKey("ENTRY_TITLE");
	const char* windowTitle = p->c_str();

	sfmlManager = SFML_Manager::Initialize(sf::VideoMode(640, 480), windowTitle);
	ImGui::SFML::Init(sfmlManager->Window);

	bool debugWindow = false;

	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };

	sfmlManager->Window.resetGLStates();

	ImGuiIO& io = ImGui::GetIO();

	ImFont* pImguiRoboto = ImGui::GetIO().Fonts->AddFontFromFileTTF("Resources/Roboto Font/Roboto-Regular.ttf", 18);
	ImGui::SFML::UpdateFontTexture();

	sfmlManager->Window.setFramerateLimit(24);

	while (sfmlManager->Window.isOpen())
	{
		sf::Event sfEvent;
		while (sfmlManager->ProcessEvents(sfEvent))
		{
			ImGui::SFML::ProcessEvent(sfEvent);
			stateManager->GetCurrentState()->ProcessEvents(sfEvent);			
			if (sfEvent.type == sf::Event::KeyReleased)
			{
				if (sfEvent.key.code == sf::Keyboard::Tilde)
				{
					debugWindow = !debugWindow;
				}
			}
		}

		// All widgets must be created between update and render
		ImGui::SFML::Update(sfmlManager->Window, sfmlManager->DeltaClock.restart());
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
					sfmlManager->Window.close();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
		
		stateManager->GetCurrentState()->Build();
		
		if (debugWindow)
		{
			ImGui::Begin("State Manager");
			std::vector<std::string> allStates = stateManager->AllStatesAsStrings();

			ImGui::BeginChild("All States", ImVec2(0, 100));
			for (auto state = allStates.rbegin(); state != allStates.rend(); ++state)
			{
				if (state == allStates.rbegin())
				{
					ImGui::TextColored(ImVec4(0, 60, 255, 255), state->c_str());
				}
				else
				{
					if (ImGui::Selectable(state->c_str()))
					{
						StateType type = StateType::StateMainMenu;

						for (auto const& statePair : State::StateStringMap)
						{
							if (statePair.second == *state)
							{
								type = statePair.first;
								break;
							}
						}

						stateManager->PopToState(type);
					}
				}				
			}

			ImGui::EndChild();

			ImGui::BeginChild("Add New State");
			ImGui::Columns(3, "mycolumns3", false);
			ImGui::Separator();

			for (auto const& statePair : State::StateStringMap)
			{
				if (ImGui::Selectable(statePair.second.c_str()))
				{
					std::string luafile = "Resources/LUA/" + statePair.second + ".lua";
					stateManager->PushState(State(statePair.first, luafile.c_str()));					
				}
				ImGui::NextColumn();
			}
			ImGui::EndChild();

			ImGui::End();
		}

		sfmlManager->Window.clear(bgColor);
		ImGui::ShowDemoWindow();
		stateManager->GetCurrentState()->Render(sfmlManager->Window);
		ImGui::SFML::Render(sfmlManager->Window);
		sfmlManager->Window.display();

		stateManager->GetCurrentState()->RecalculateHash();
	}

	ImGui::SFML::Shutdown();
	LocalizationManager::Shutdown();
	LuaManager::Shutdown();
}