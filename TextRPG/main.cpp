#include "BaseIncludes.h"
#include "DebugLogger.h"

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

#include "UiManager.h"

void CreateFrameDebugWindow(int32 dt)
{
	const float DISTANCE = 10.0f;
	static int corner = 2;
	ImGuiIO& io = ImGui::GetIO();

	ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
	ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

	ImGui::SetNextWindowBgAlpha(0.35f);
	if (!ImGui::Begin("Frame Debug Window", (bool *)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		ImGui::End();
		return;
	}

	static float values[90] = {};
	static int values_offset = 0;

	values[values_offset] = dt;
	values_offset = (values_offset + 1) % 90;

	ImGui::PlotLines("", values, IM_ARRAYSIZE(values), values_offset);

	std::string fps = "FPS: " + std::to_string(1.0f / (dt / 1000.0f));
	ImGui::Text(fps.c_str());

	ImGui::SameLine();
	std::string delta = "MS per Frame: " + std::to_string(dt);
	ImGui::Text(delta.c_str());

	ImGui::End();
}

void CreateStateManagerDebugWindow(StateManager& stateManager)
{
	ImGui::Begin("State Manager");
	std::vector<std::string> allStates = stateManager.AllStatesAsStrings();

	ImGui::BeginChild("All States", ImVec2(0, 100));
	for (auto state = allStates.rbegin(); state != allStates.rend(); ++state)
	{
		const char* stateString = state->c_str();
		if (state == allStates.rbegin())
		{
			ImGui::TextColored(ImVec4(0, 60, 255, 255), stateString);
		}
		else
		{
			if (ImGui::Selectable(stateString))
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

				stateManager.PopToState(type);
				DebugLogger::GetInstance().LogMessage("Pop to state %s", stateString);
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
			stateManager.PushState(new State(statePair.first, luafile.c_str()));

			DebugLogger::GetInstance().LogMessage("Push state %s", statePair.second.c_str());
		}
		ImGui::NextColumn();
	}
	ImGui::EndChild();

	ImGui::End();
}

int main()
{
	DebugLogger& debugLogger = DebugLogger::GetInstance();
	GameManager& gameManager = GameManager::GetInstance();
	LocalizationManager& locManager = LocalizationManager::GetInstance();
	UiManager& uiManager = UiManager::GetInstance();

	StateManager& stateManager = StateManager::Init(new StateMainMenu());
	
	auto p = locManager.GetLocByKey(LocalizationKey::ENTRY::TITLE);
	const char* windowTitle = p->c_str();

	SFML_Manager& sfmlManager = SFML_Manager::Initialize(sf::VideoMode(640, 480), windowTitle);
	ImGui::SFML::Init(sfmlManager.Window);

	bool debugWindow = false;

	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };

	sfmlManager.Window.resetGLStates();

	ImGuiIO& io = ImGui::GetIO();

	ImFont* pImguiRoboto = ImGui::GetIO().Fonts->AddFontFromFileTTF("Resources/Roboto Font/Roboto-Regular.ttf", 18);
	ImGui::SFML::UpdateFontTexture();

	sfmlManager.Window.setFramerateLimit(24);

	io.FontDefault = pImguiRoboto;

	while (sfmlManager.Window.isOpen())
	{
		sf::Event sfEvent;
		while (sfmlManager.ProcessEvents(sfEvent))
		{
			ImGui::SFML::ProcessEvent(sfEvent);
			stateManager.GetCurrentState()->ProcessEvents(sfEvent);			
			if (sfEvent.type == sf::Event::KeyReleased)
			{
				if (sfEvent.key.code == sf::Keyboard::Tilde)
				{
					debugWindow = !debugWindow;
				}
			}
		}

		// All widgets must be created between update and render
		int32 deltaTime = sfmlManager.DeltaClock.getElapsedTime().asMilliseconds();
		ImGui::SFML::Update(sfmlManager.Window, sfmlManager.DeltaClock.restart());
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Main Menu"))
				{
					stateManager.PopToBottom();
				}
				if (ImGui::MenuItem("Save Game"))
				{
					stateManager.PushState(new StateSaveGame());
				}
				if (ImGui::MenuItem("Load Game"))
				{
					stateManager.PushState(new StateLoadGame());
				}
				if (ImGui::MenuItem("Quit"))
				{
					sfmlManager.Window.close();
				}

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
		
		stateManager.GetCurrentState()->Build();
		
		if (debugWindow)
		{
			CreateStateManagerDebugWindow(stateManager);
			CreateFrameDebugWindow(deltaTime);
			debugLogger.Draw();
		}

		uiManager.Update();

		sfmlManager.Window.clear(bgColor);
		ImGui::ShowDemoWindow();
		stateManager.GetCurrentState()->Render(sfmlManager.Window);
		ImGui::SFML::Render(sfmlManager.Window);
		uiManager.Draw(sfmlManager.Window);
		sfmlManager.Window.display();

		stateManager.GetCurrentState()->RecalculateHash();
	}

	ImGui::SFML::Shutdown();	

	debugLogger.Shutdown();
	gameManager.Shutdown();
	locManager.Shutdown();
	stateManager.Shutdown();

	LuaManager::Shutdown();
}