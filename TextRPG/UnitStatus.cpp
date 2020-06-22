#include "UnitStatus.h"

const char* kHealthStatus	= "unitstatus_hlt";
const char* kAttributes		= "unitstatus_atr";
const char* kSkills			= "unitstatus_skl";

json UnitStatus::SerializeData() const
{
	json data;

	data[kHealthStatus] = UnitHealth.SerializeData();

	for (const auto& attr : UnitAttributes)
	{
		data[kAttributes][(int)attr.first] = std::move(attr.second.SerializeData());
	}

	for (const auto& skill: UnitSkills)
	{
		data[kSkills][(int)skill.first] = std::move(skill.second.SerializeData());
	}

	return data;
}

void UnitStatus::DeserializeData(json data)
{
	if (!data.is_object())
	{
		return;
	}

	if (data.contains(kHealthStatus))
	{
		HealthStats tmpHealth;
		tmpHealth.DeserializeData(data[kHealthStatus]);

		UnitHealth = std::move(tmpHealth);
	}

	if (data.contains(kAttributes) && data.is_object())
	{
		UnitAttributes.clear();
		for (const auto& attr : data[kAttributes].items())
		{
			try
			{
				int index = std::stoi(attr.key());
				AttributeType t = (AttributeType)index;

				Attribute tmpAttr;
				tmpAttr.DeserializeData(attr.value());

				UnitAttributes.emplace(t, std::move(tmpAttr));
			}
			catch (std::exception const &e)
			{

			}
		}
	}

	if (data.contains(kSkills) && data.is_object())
	{
		UnitSkills.clear();
		for (const auto& skill : data[kSkills].items())
		{
			try
			{
				int index = std::stoi(skill.key());
				SkillType t = (SkillType)index;

				Skill tmpSkill;
				tmpSkill.DeserializeData(skill.value());

				UnitSkills.emplace(t, std::move(tmpSkill));
			}
			catch (std::exception const& e)
			{

			}
		}
	}
}

UnitStatus::UnitStatus(const uint16& startingAge)
{
	UnitStatus::UnitHealth = HealthStats(startingAge);

	for (auto const &iter: Attribute::AllAttributes)
	{
		AttributeType att = iter.first;
		UnitStatus::UnitAttributes.insert(std::pair<AttributeType, Attribute> (att, Attribute(att)));		
	}

	for (auto const &iter: Skill::AllSkills)
	{
		SkillType skill = iter.first;
		UnitStatus::UnitSkills.insert(std::pair<SkillType, Skill>(skill, Skill(skill)));
	}
}