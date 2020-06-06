#include "imguiWindows.h"
#include "imgui.h"
#include "Unit.h"

bool imguiWindow::PushNewCharacterCreationWindow(Unit* character)
{
	ImGuiWindowFlags window_flags = 0;

	window_flags |= ImGuiWindowFlags_NoResize;

	bool showBorders = false;
	int height = 200;

	if (!ImGui::Begin("Character Creation Window", (bool*)0, window_flags))
	{
		ImGui::End();
		return false;
	}

#pragma region Begin("Character Creation Window")
	ImGui::Text("Character Creation");

	static char buff[32];
	ImGui::Columns(2, "ccOV2", showBorders);
	ImGui::InputTextWithHint("", "Enter a name...", buff, 32);

	ImGui::Separator();

	static int totalStats = 5;
	const static int totalStatCap = 5;

	std::string totalAttributePointsAvailable = "Remaining Points: " + std::to_string(totalStats) + " / " + std::to_string(totalStatCap);
	ImGui::Text(totalAttributePointsAvailable.c_str());

	ImGui::BeginChild("Attributes", ImVec2(0, height));
#pragma region BeginChild("Attributes", ImVec2(0, 200)
	ImGui::Columns(3, "ccST3", showBorders);

	ImGui::SetColumnWidth(0, 110);
	ImGui::SetColumnWidth(1, 30);
	ImGui::SetColumnWidth(2, 65);

	for (const auto& stat : Attribute::AllAttributes)
	{
		ImGui::Text(stat.second.LongValue);
		ImGui::NextColumn();
		uint16 statValue = character->Status.UnitAttributes[stat.first].GetValue();
		ImGui::Text(std::to_string(statValue).c_str());
		ImGui::NextColumn();

		std::string leftID = stat.second.ShortValue;
		std::string rightID = stat.second.ShortValue;
		leftID += "left";
		rightID += "right";

		if (ImGui::ArrowButton(leftID.c_str(), ImGuiDir_Left))
		{
			if (totalStats != totalStatCap)
			{
				++totalStats;
				character->Status.UnitAttributes[stat.first].RemoveModifier(1);
			}
		}
		ImGui::SameLine();
		if (ImGui::ArrowButton(rightID.c_str(), ImGuiDir_Right))
		{
			if (totalStats > 0)
			{
				--totalStats;
				character->Status.UnitAttributes[stat.first].AddModifier(1);
			}
		}

		ImGui::NextColumn();
	}
#pragma endregion
	ImGui::EndChild();

	ImGui::NextColumn();

	static int totalSkillPoints = 5;
	static int totalSkillPointsCap = 5;

	std::string totalSkillPointsAvailable = "Skill Points: " + std::to_string(totalSkillPoints);
	ImGui::Text(totalSkillPointsAvailable.c_str());

	ImGui::BeginChild("Skills", ImVec2(0, height));
#pragma region BeginChild("Skills", ImVec2(0, 200)
	ImGui::Columns(3, "ccSK3", showBorders);

	ImGui::SetColumnWidth(0, 150);
	ImGui::SetColumnWidth(1, 30);
	ImGui::SetColumnWidth(2, 65);

	static std::vector<bool*> skillsSelected;
	for (auto& skill : Skill::AllSkills)
	{
		bool* b = new bool;
		skillsSelected.push_back(b);
	}

	int index = 0;
	for (const auto& skill : Skill::AllSkills)
	{
		ImGui::Text(skill.second.ShortValue);
		ImGui::NextColumn();
		uint16 skillValue = character->Status.UnitSkills[skill.first].GetValue();
		ImGui::Text(std::to_string(skillValue).c_str());
		ImGui::NextColumn();

		++index;
		ImGui::NextColumn();
	}
#pragma endregion
	ImGui::EndChild();

	ImGui::Dummy(ImVec2(0, 20.0f));
	if (ImGui::Button("GO"))
	{
		character->Name = std::string(buff);
		memcpy(buff, "", 32);

		totalStats = 5;
		totalSkillPoints = 5;

		ImGui::End();
		return true;
	}

#pragma endregion
	ImGui::End();

	return false;
}